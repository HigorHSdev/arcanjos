# Plataforma EMQX + MySQL

Este roteiro adapta a plataforma existente; não cria outra instalação Docker.
Host, versão, edição, portas e credenciais não foram fornecidos.

## Banco

1. No seu MySQL, examine `../platform/schema.sql` e execute para criar o modelo N1.
   Se já houver tabela de acessos, compare a estrutura antes de usar este modelo.
2. Configure uma conta dedicada para o conector com permissão de INSERT na tabela;
   use outra conta de leitura para consultas. Não coloque essas senhas no GitHub.
3. Confirme que o EMQX alcança o host/porta MySQL. Em contêineres diferentes,
   `localhost` não aponta automaticamente para o outro serviço.

## EMQX

1. Confirme que a edição/versão instalada oferece conector ou ação MySQL.
   A documentação de integração consultada é da edição Enterprise; disponibilidade
   e licença precisam ser verificadas na sua instalação. Não afirme que qualquer
   edição gratuita fornece esse recurso.
2. Crie/configure o conector MySQL com host, porta, banco `arcanjos` e conta dedicada.
   Teste a conexão pelo painel.
3. Crie regra para o tópico `arcanjos/acesso`, usando `../platform/emqx-rule.sql`.
4. Vincule uma ação MySQL à regra. Cole `../platform/emqx-mysql-template.sql` no
   campo de template SQL. `${device}` e outros são placeholders do EMQX, não SQL
   para executar diretamente no DBeaver. Use o modo de parâmetros da ação.
5. Teste a regra com JSON que contenha `device`, `uid` e `status`. Veja se os três
   campos são extraídos. Depois teste a ação e consulte o MySQL.
6. Configure autenticação MQTT e permissão de publicar somente no tópico do projeto.
   Ajuste o firmware ao listener efetivamente habilitado (TCP ou TLS).

Se não houver ação MySQL, a integração direta permanece pendente. Um consumidor MQTT
externo seria outra arquitetura; não está apresentado como componente atual deste pacote.

## Contrato de dados

```json
{"device":"arcanjos-01","uid":"00:11:22:33","status":"negado"}
```

Exemplo fictício, não é evidência. O status é `autorizado` ou `negado`. O tópico é
`arcanjos/acesso`, publicação sem retain. A tabela adiciona `id` e `created_at`;
o horário é o recebimento no banco, não o instante exato de aproximação do cartão.

## Aplicativo / visualização

1. Execute `../platform/consulta-exportacao.sql` no DBeaver.
2. Exporte o resultado em JSON como **array de objetos**, com as colunas selecionadas.
3. Abra a GitPage, acesse Aplicativo e clique **Importar JSON**.
4. O arquivo é lido localmente no navegador, sem upload. Limite: 2 MB / 10.000 linhas.
5. Use o filtro de status. Os totais correspondem ao arquivo inteiro; o filtro muda a lista.

O caminho implementado é MySQL → DBeaver/exportação JSON → visualizador web.
Uma API autenticada para consulta automática é evolução futura, não entregue como pronta.
