# ARCANJOS · NFC ACCESS

Projeto Integrador 6 · Primeira entrega N1

**Instituição:** PREENCHER · **Curso/turma:** PREENCHER
**Integrantes / RAs:** PREENCHER · **Professor:** PREENCHER · **Data:** PREENCHER

## Problema e objetivo

Organizar a identificação de usuários e a consulta de eventos em um protótipo de
controle de acesso. Integrar leitura por aproximação, decisão local e registro IoT.

## Metodologia

O RFID2 lê o UID de uma tag compatível. O AtomS3 Lite compara o identificador com
uma lista local. Se autorizado, aciona o módulo M5Stack Relay por tempo configurável.
O evento é publicado por MQTT no EMQX e encaminhado ao MySQL pelo Rule Engine.

## Arquitetura

Tag → RFID2 → AtomS3 Lite → relé; AtomS3 Lite → Wi-Fi/MQTT → EMQX → Rule Engine
→ MySQL → consulta/exportação → aplicação web.

## Entregas desta versão

GitPage com quatro seções; firmware configurável; diagrama completo; circuito
funcional documentado; visualizador de exportações JSON; banner acadêmico.

## Validação e próximos passos

Conferir conexões reais, compilar e testar o firmware na montagem; registrar
evidências de autorização, negação, mensagem MQTT e inserção no banco.
Pinagem e nível ativo do relé: CONFIRMAR NA MONTAGEM.
Consulta automática por API e melhorias de autenticação são evoluções futuras.

## Limites

Protótipo acadêmico: UID não é autenticação criptográfica; o status não comprova
passagem física. Exemplos da página são fictícios. Não há medição de desempenho
nem validação física desta versão declarada.

## Referências

M5Stack: documentação AtomS3 Lite, RFID2 e Unit Relay.
EMQX: documentação de integração com MySQL. Ver docs/fontes.md no repositório.
