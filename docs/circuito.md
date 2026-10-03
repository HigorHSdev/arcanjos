# Circuito eletrônico / elétrico · versão funcional N1

**CONFIRMAR NA MONTAGEM:** nenhum número de GPIO ou porta física foi confirmado.
O desenho registra redes funcionais para conferência; não autoriza ligação por posição
ou cor de cabo. Usar somente os módulos atuais: AtomS3 Lite, RFID2 e M5Stack Actuator/Unit Relay.

## Ligações de sinal

- RFID2 SDA ↔ AtomS3 Lite GPIO SDA: **CONFIRMAR NA MONTAGEM**.
- RFID2 SCL ← AtomS3 Lite GPIO SCL: **CONFIRMAR NA MONTAGEM**.
- Controle do M5Stack Relay ← GPIO exclusivo do AtomS3: **CONFIRMAR NA MONTAGEM**,
  incluindo se o modelo exato realmente usa entrada digital.
- GND de referência dos módulos e controlador: **CONFIRMAR NA MONTAGEM**.
- Alimentação do RFID2 e Relay a partir dos pontos adequados do conjunto:
  **CONFIRMAR NA MONTAGEM** (tensão, corrente disponível e conectores).
- Entrada de alimentação do AtomS3 Lite / cabo usado: **CONFIRMAR NA MONTAGEM**.

## Relé e contatos

O módulo M5Stack já contém o circuito de acionamento; não acrescentar transistor,
diodo ou relé genérico de uma solução anterior. Identifique COM/NO/NC somente se
esses bornes estiverem no seu modelo e conforme a serigrafia/manual dele.
Não foi informada carga ligada aos contatos. Eles aparecem no diagrama como
terminais sem carga documentada, não como fechadura instalada.

## Conferência antes de energizar

1. Identificar o código do produto e fotografar o módulo Relay.
2. Anotar porta/cabo de cada módulo e verificar continuidade com o sistema desligado.
3. Mapear SDA, SCL, GND, alimentação e sinal do relé aos GPIOs reais.
4. Verificar que relé e RFID2 não disputam os mesmos sinais. Um divisor de cabo
   não cria GPIOs independentes.
5. Conferir tensão, polaridade e corrente com os manuais das revisões presentes.
6. Verificar repouso e pulso do relé inicialmente sem carga externa.
7. Preencher `config.h`, registrar a foto e atualizar este desenho com os valores reais.

Protoboard: não incluída, pois o uso não foi confirmado. Caso exista, registrar
explicitamente quais redes ela distribui antes de acrescentá-la ao desenho.
