# Roteiro de testes e apresentação

## Verificações de bancada (a executar pela equipe)

1. **Configuração incompleta:** firmware deve informar bloqueio no Serial.
2. **Inicialização:** relé em repouso, leitor detectado, sem pulso inesperado no reset.
3. **Leitura:** UID no Serial deve ser estável e ter dois dígitos por byte.
4. **Cartão negado:** lista vazia ou UID ausente; relé não aciona; evento `negado`.
5. **Cartão autorizado:** cadastrar UID real, reapresentar; pulso de duração configurada.
6. **Repetição:** manter tag próxima, retirar e reapresentar; observar duplicações.
7. **MQTT:** verificar tópico, payload e identidade do cliente no EMQX.
8. **MySQL:** verificar nova linha por evento recebido e testar a ação da regra.
9. **Falha de rede:** autorização continua local; relé desliga; Serial informa evento
   não enviado. Confirmar reconexão. Eventos perdidos não reaparecem automaticamente.
10. **Visualizador:** exportar JSON, importar, filtrar; comparar totais com a consulta.
11. **Energização/reset:** conferir comportamento elétrico real do relé sem carga.

Não marcar como aprovado sem executar. O aceite físico inclui verificar o estado
real do relé; a mensagem Serial não substitui essa observação.

## Evidências sugeridas

- Foto geral e foto dos conectores da montagem atual.
- Captura de compilação com placa e bibliotecas identificadas.
- Captura do Serial e do EMQX para cartão autorizado e negado.
- Consulta MySQL mostrando esses mesmos eventos.
- Captura da página e do visualizador com origem dos dados identificada.

Oculte senhas e identifique os UIDs nas evidências públicas com pseudônimos.
Registre data, versão do firmware, resultado e observações no arquivo de evidências.

## Apresentação em 3 minutos

1. Mostre Home: objetivo e fluxo de identificação, decisão e registro.
2. Mostre Dispositivos e a montagem: destaque RFID2, AtomS3 Lite e módulo Relay.
3. Demonstre tag autorizada e negada, se a bancada já estiver validada.
4. Mostre o evento no EMQX e a linha correspondente no MySQL.
5. Mostre Aplicativo com exportação real. Se usar exemplos, diga que são fictícios.
6. Encerre com arquitetura, circuito e banner; indique pendências ainda abertas.
