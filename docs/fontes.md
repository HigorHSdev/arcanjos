# Referências e origem das informações

## Contexto fornecido

Conversa “Projeto identificador NFC”: nome Arcanjos NFC Access, requisitos N1,
AtomS3 Lite, RFID2, M5Stack Actuator/Unit Relay, MQTT, EMQX, Rule Engine, MySQL,
DBeaver e menção a Docker. A conversa relata funcionamento anterior; não fornece
evidências, pinagem, credenciais ou código integral da montagem.

## Referências oficiais consultadas

- M5Stack, exemplo Arduino Unit RFID/RFID2:
  https://docs.m5stack.com/en/arduino/projects/unit/unit_rfid
- M5Stack, Unit RFID2:
  https://docs.m5stack.com/en/unit/rfid2
- M5Stack, Unit Relay (referência; conferir se coincide com o modelo presente):
  https://docs.m5stack.com/en/unit/Unit_Relay
- M5Stack, exemplo público do driver I²C:
  https://github.com/m5stack/M5StickC/tree/master/examples/Unit/RFID
- EMQX, integração MySQL (Enterprise):
  https://docs.emqx.com/en/emqx/latest/develop/data-integration/data-bridge-mysql.html

As referências sustentam interfaces e APIs, não provam as conexões da montagem do usuário.
Nenhuma pinagem de exemplos de outra placa foi transplantada para este projeto.

## Propostas desta entrega

Tabela `arcanjos.acessos`, pulso de 2 segundos, lista local de UIDs, visualizador por
importação JSON, composição do banner e organização de arquivos são propostas N1.
O código respeita o payload anterior (device, uid, status) e o tópico `arcanjos/acesso`.
