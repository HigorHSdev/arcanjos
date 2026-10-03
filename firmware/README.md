# Firmware Arduino · primeira versão N1

## Preparar

1. Instale Arduino IDE e suporte de placas ESP32/M5Stack seguindo o guia oficial
   listado em `../docs/fontes.md`. Selecione **M5Stack AtomS3** conforme o pacote
   instalado e confira as opções de USB para o AtomS3 Lite.
2. Instale **PubSubClient** (Nick O'Leary), **ArduinoJson 7** e **MFRC522_I2C**
   compatível com a API do exemplo oficial M5Stack. Não use a biblioteca MFRC522
   somente SPI. A classe necessária é `MFRC522_I2C`, com construtor `(endereco, reset)`.
   O guia oficial RFID/RFID2 indica MFRC522_I2C >= 1.0; o exemplo público M5StickC
   também fornece os arquivos `.h` e `.cpp` se a biblioteca não aparecer no gerenciador.
3. Abra `arcanjos_nfc/arcanjos_nfc.ino` mantendo o nome da pasta e do sketch iguais.
4. Copie `config.example.h` para `config.h`, na mesma pasta.
5. Preencha SSID, senha, host, porta, usuário, senha MQTT e identificador único.
6. Confirme fisicamente SDA, SCL, GPIO do relé, tensão, GND, modelo e nível ativo.
   Somente depois altere os dois indicadores de confirmação para `true`.
7. Com TLS, forneça certificado CA PEM e servidor NTP acessível. Não há `setInsecure`.
   Se o EMQX usar TCP sem TLS em laboratório, ajuste `MQTT_TLS=false` e confirme
   `MQTT_SEM_TLS_LAB_CONFIRMADO=true`. Não confunda a porta do painel com o listener MQTT.
8. Confira a lista local de UIDs. Ela inicia vazia e todos os cartões serão negados.
   Leia o UID no Serial e cadastre apenas o cartão autorizado pela equipe.
9. Compile, grave e abra o monitor Serial a 115200 baud.

## Comportamento

- Sem configuração completa: bloqueia no início e não configura GPIOs.
- Com configuração válida: coloca o relé em repouso e verifica resposta I²C do RFID2.
- Lê UID em hexadecimal maiúsculo, com dois dígitos e `:` entre os bytes.
- Tag autorizada: aciona por 2 segundos (parâmetro proposto e ajustável).
- Tag negada: mantém o estado de repouso.
- Durante o pulso não executa chamadas de rede nem de leitura; a publicação ocorre depois.
- Repetição: intervalo mínimo de 1,5 s, além do Halt do cartão; retire e reapresente a tag.
- Reconexão Wi-Fi/MQTT periódica. O ciclo de conexão pode atrasar a próxima leitura,
  mas só é chamado com relé desligado.
- Sem rede: a decisão continua local; não há armazenamento persistente dos eventos.
- `status=autorizado` significa autorização lógica, não feedback de abertura física.

## Cuidados específicos da montagem

Não dividir um sinal GPIO do relé com SDA/SCL. O código recusa pinos repetidos.
Essa validação não identifica GPIOs reservados ou não expostos: conferir o pinout
da revisão real da placa. Se o módulo for comandado por I²C ou outra interface,
não habilite `RELE_GPIO_CONFIRMADO`; esse modelo exige adaptar o driver.
O software não garante o estado elétrico antes de `setup()` ou durante reset.
Verifique o comportamento do módulo na energização, sem carga conectada.

## Validação ainda necessária

As versões exatas instaladas devem ser anotadas após compilar. Nenhuma combinação
de placa/bibliotecas foi declarada validada aqui. Execute o roteiro de `../docs/validacao.md`.
