/* Arcanjos NFC Access - N1
 * Base inicial: não validada na montagem física.
 * Bibliotecas: MFRC522_I2C, PubSubClient, ArduinoJson 7; core ESP32.
 * O firmware controla o módulo M5Stack por GPIO SOMENTE após confirmar o modelo.
 */
#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <MFRC522_I2C.h>
#include <time.h>
#if __has_include("config.h")
#include "config.h"
#else
#include "config.example.h"
#endif

MFRC522_I2C rfid(RFID_ENDERECO, -1);
WiFiClient tcp;
WiFiClientSecure tls;
PubSubClient mqtt;
bool pronto = false, releAtivo = false, pendente = false;
unsigned long inicioRele = 0, ultimaLeitura = 0, tentativaWiFi = 0, tentativaMQTT = 0;
char evento[320];

bool preenchido(const char* s) { return s[0] && strncmp(s, "PREENCHER", 9) != 0; }
void desligarRele() { digitalWrite(RELE_GPIO, !RELE_NIVEL_ATIVO); releAtivo = false; }
bool autorizado(const String& uid) {
  for (const char* item : UIDS_AUTORIZADOS) if (item[0] && uid == item) return true;
  return false;
}
bool validarConfiguracao() {
  if (!MONTAGEM_CONFIRMADA || !RELE_GPIO_CONFIRMADO) return false;
  if (RFID_SDA < 0 || RFID_SCL < 0 || RELE_GPIO < 0) return false;
  if (RFID_SDA == RFID_SCL || RELE_GPIO == RFID_SDA || RELE_GPIO == RFID_SCL) return false;
  if (RELE_NIVEL_ATIVO != 0 && RELE_NIVEL_ATIVO != 1) return false;
  if (!RELE_TEMPO_MS || RELE_TEMPO_MS > 10000) return false;
  if (!preenchido(WIFI_SSID) || !preenchido(WIFI_SENHA) || !preenchido(MQTT_HOST) || !MQTT_PORTA) return false;
  if (!preenchido(MQTT_USUARIO) || !preenchido(MQTT_SENHA) || !preenchido(DEVICE_ID)) return false;
  if (MQTT_TLS && (!preenchido(MQTT_CA) || !preenchido(NTP_SERVIDOR))) return false;
  if (!MQTT_TLS && !MQTT_SEM_TLS_LAB_CONFIRMADO) return false;
  return true;
}
void conectarRede() {
  unsigned long agora = millis();
  if (WiFi.status() != WL_CONNECTED) {
    if (agora - tentativaWiFi >= 15000) {
      tentativaWiFi = agora;
      WiFi.disconnect(); WiFi.begin(WIFI_SSID, WIFI_SENHA);
    }
    return;
  }
  if (MQTT_TLS && time(nullptr) < 1700000000) return; // aguarda relógio válido
  if (!mqtt.connected() && agora - tentativaMQTT >= 5000) {
    tentativaMQTT = agora;
    String clientId = String(DEVICE_ID) + "-" + WiFi.macAddress();
    if (mqtt.connect(clientId.c_str(), MQTT_USUARIO, MQTT_SENHA)) Serial.println("MQTT conectado.");
    else Serial.printf("MQTT indisponivel: %d\n", mqtt.state());
  }
}
void setup() {
  Serial.begin(115200);
  delay(500);
  if (!validarConfiguracao()) {
    Serial.println("BLOQUEADO: preencher config.h e CONFIRMAR NA MONTAGEM. Nenhuma saida configurada.");
    return;
  }
  // Configurar o nível inativo antes de habilitar a saída reduz pulsos na inicialização.
  digitalWrite(RELE_GPIO, !RELE_NIVEL_ATIVO);
  pinMode(RELE_GPIO, OUTPUT); desligarRele();
  if (!Wire.begin(RFID_SDA, RFID_SCL, 100000)) {
    Serial.println("Falha ao iniciar I2C."); return;
  }
  Wire.setTimeOut(50);
  Wire.beginTransmission(RFID_ENDERECO);
  if (Wire.endTransmission() != 0) {
    Serial.println("RFID2 ausente no I2C. Verifique montagem e endereco."); return;
  }
  rfid.PCD_Init();
  if (MQTT_TLS) { tls.setCACert(MQTT_CA); mqtt.setClient(tls); }
  else mqtt.setClient(tcp);
  mqtt.setServer(MQTT_HOST, MQTT_PORTA);
  mqtt.setBufferSize(512); mqtt.setSocketTimeout(2); mqtt.setKeepAlive(30);
  WiFi.mode(WIFI_STA); WiFi.begin(WIFI_SSID, WIFI_SENHA);
  if (MQTT_TLS) configTime(0, 0, NTP_SERVIDOR);
  tentativaMQTT = millis() - 5000;
  ultimaLeitura = millis() - INTERVALO_LEITURA_MS;
  pronto = true;
  Serial.println("Inicializado. Lista local decide; retirada da tag permite nova leitura.");
}
void loop() {
  if (!pronto) { delay(20); return; }
  // Durante o pulso, não chamar rede nem leitor: reconexões podem bloquear.
  if (releAtivo) {
    if (millis() - inicioRele >= RELE_TEMPO_MS) desligarRele();
    else { delay(1); return; }
  }
  // Publicação após desativar o relé. QoS 0: retorno true não comprova INSERT no banco.
  if (pendente) {
    bool enviado = mqtt.connected() && mqtt.publish(MQTT_TOPICO, evento, false);
    Serial.println(enviado ? "Evento enviado ao cliente MQTT (QoS 0)." : "EVENTO NAO ENVIADO: sem fila persistente nesta N1.");
    pendente = false;
  }
  conectarRede();
  if (mqtt.connected()) mqtt.loop();
  if (millis() - ultimaLeitura < INTERVALO_LEITURA_MS) return;
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;
  ultimaLeitura = millis();
  String uid;
  for (byte i = 0; i < rfid.uid.size; i++) {
    char hex[3]; snprintf(hex, sizeof(hex), "%02X", rfid.uid.uidByte[i]);
    if (i) uid += ':';
    uid += hex;
  }
  rfid.PICC_HaltA(); rfid.PCD_StopCrypto1();
  bool permitido = autorizado(uid);
  JsonDocument doc;
  doc["device"] = DEVICE_ID; doc["uid"] = uid;
  doc["status"] = permitido ? "autorizado" : "negado";
  if (measureJson(doc) >= sizeof(evento)) { Serial.println("Evento excedeu buffer; acesso cancelado."); return; }
  serializeJson(doc, evento, sizeof(evento)); Serial.println(evento); pendente = true;
  if (permitido) {
    digitalWrite(RELE_GPIO, RELE_NIVEL_ATIVO);
    inicioRele = millis(); releAtivo = true;
  }
}
