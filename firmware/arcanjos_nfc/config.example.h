#pragma once
// Copie como config.h e personalize. Nunca publique config.h.
// GPIOs, porta física, tensão e nível ativo: CONFIRMAR NA MONTAGEM.
constexpr bool MONTAGEM_CONFIRMADA = false;
constexpr bool RELE_GPIO_CONFIRMADO = false; // confirmar modelo de controle digital
constexpr int RFID_SDA = -1;
constexpr int RFID_SCL = -1;
constexpr int RELE_GPIO = -1;
constexpr int RELE_NIVEL_ATIVO = -1; // 0 ou 1, somente após confirmar
constexpr uint8_t RFID_ENDERECO = 0x28; // referência do fabricante; conferir no barramento
constexpr unsigned long RELE_TEMPO_MS = 2000; // proposta N1; ajustar com a equipe
constexpr unsigned long INTERVALO_LEITURA_MS = 1500;
constexpr char WIFI_SSID[] = "PREENCHER";
constexpr char WIFI_SENHA[] = "PREENCHER";
constexpr char MQTT_HOST[] = "PREENCHER";
constexpr uint16_t MQTT_PORTA = 0; // preencher conforme listener do seu EMQX
constexpr char MQTT_USUARIO[] = "PREENCHER";
constexpr char MQTT_SENHA[] = "PREENCHER";
constexpr bool MQTT_TLS = true; // ajustar conforme listener confirmado
constexpr bool MQTT_SEM_TLS_LAB_CONFIRMADO = false;
constexpr char MQTT_CA[] = R"CERT(PREENCHER_CERTIFICADO_CA_PEM)CERT";
constexpr char NTP_SERVIDOR[] = "PREENCHER"; // necessário para validar datas do certificado TLS
constexpr char DEVICE_ID[] = "arcanjos-01"; // identificador proposto; deve ser único
constexpr char MQTT_TOPICO[] = "arcanjos/acesso";
// Nenhum UID real foi confirmado como autorizado. Lista vazia nega todos.
// Substitua "" por UID confirmado, maiúsculo e com dois dígitos por byte.
// Para mais tags: {"UID_REAL_1", "UID_REAL_2"}.
constexpr const char* UIDS_AUTORIZADOS[] = {""};
