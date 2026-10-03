# Verificações realizadas nesta entrega

## Página web

- JavaScript passou na verificação de sintaxe.
- Página aberta em navegador local; menu obrigatório presente.
- Demonstração: 3 registros, sendo 2 autorizados e 1 negado.
- Filtro Negados: exibiu somente o registro negado.
- Importação do JSON de exemplo: reconhecida e exibida.
- JSON com estrutura inválida: rejeitado com mensagem, preservando os dados anteriores.
- Limpar registros: removeu os eventos da lista.
- Layout conferido em computador e viewport de celular de 390 px;
  sem transbordamento horizontal da página.
- Não foram observados avisos ou erros no console durante esses testes.
- Todos os links locais e âncoras do HTML apontam para arquivos/seções existentes.

## Materiais gráficos

- Banner, arquitetura e circuito gerados em PDF e SVG.
- Os três PDFs têm uma página e foram renderizados e inspecionados visualmente.
- SVGs passaram na leitura XML; JSON de exemplo passou na leitura de estrutura.

## Não verificado neste ambiente

- Compilação do sketch com toolchain Arduino/ESP32 e bibliotecas reais.
- Gravação na placa, leitura RFID2, acionamento elétrico e comportamento no reset.
- Listener MQTT, regra EMQX, conector MySQL e persistência no banco do usuário.
- GitHub Pages remoto: arquivos preparados, sem publicação realizada.

Os testes da interface usam dados fictícios. Não constituem evidência de bancada.
