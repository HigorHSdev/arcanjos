# Arcanjos NFC Access

**Projeto Integrador 6 · Primeira entrega N1**

Protótipo acadêmico de identificação por RFID/NFC com AtomS3 Lite, RFID2,
M5Stack Actuator/Unit Relay e registro de acessos via MQTT, EMQX e MySQL.

## Comece aqui

1. Abra `index.html` no navegador: a página funciona localmente, sem instalação.
2. Veja `assets/banner.pdf`, `assets/arquitetura.pdf` e `assets/circuito.pdf`.
3. Preencha os itens de `docs/pendencias.md` antes da demonstração física.
4. Para programar a placa, siga `firmware/README.md`.
5. Para conectar ao seu EMQX/MySQL, siga `docs/plataforma.md`.

## Os cinco itens da entrega

- **GitPage:** `index.html`, `style.css`, `script.js`, com menu Home | Plataforma | Dispositivos | Aplicativo.
- **Firmware:** `firmware/arcanjos_nfc/`, com configuração separada e bloqueio inicial.
- **Diagrama completo:** `assets/arquitetura.svg` e `.pdf`; fonte Mermaid em `docs/arquitetura.mmd`.
- **Banner:** `assets/banner.svg` e `.pdf`; texto editável em `docs/banner.md`. Formato A1 vertical, uma proposta pois o tamanho não foi fornecido.
- **Circuito:** `assets/circuito.svg` e `.pdf`, detalhado em `docs/circuito.md`.

## O que esta versão faz

O firmware lê o UID, aplica uma lista local e pulsa o relé se autorizado. Gera o JSON
`{"device":"arcanjos-01","uid":"UID_LIDO","status":"autorizado"}`
ou `negado`, publicado em `arcanjos/acesso`. O identificador do dispositivo é configurável.
O EMQX encaminha eventos a uma ação MySQL. O horário salvo é o recebimento no banco.

O aplicativo web importa JSON exportado do banco e filtra por status. Seus exemplos
são fictícios e só aparecem ao clicar em **Carregar demonstração**. A aplicação
não faz consultas diretas ao banco e não armazena credenciais no navegador.

## Estado real da entrega

Arquivos e documentação preparados como primeira versão. A conversa anterior relata
integração EMQX/MySQL, mas não disponibiliza configurações, fotos nem registros que
permitam reproduzi-la. Este pacote não declara essa integração novamente testada.
Pinagem, modelo exato do relé e alimentação: **CONFIRMAR NA MONTAGEM**.
O firmware entregue não foi compilado com o core Arduino nem testado na placa neste ambiente.
O bloqueio inicial é intencional; preencher a configuração é obrigatório.

## Publicar no GitHub Pages

1. Crie um repositório, por exemplo `arcanjos-nfc-access`.
2. Envie o conteúdo desta pasta para a raiz do repositório, preservando subpastas.
3. Não envie `config.h`, senhas, exportações reais de acesso ou fotos com credenciais.
4. Nas configurações do repositório, abra **Pages**, selecione publicação pela branch,
   a branch com os arquivos e a pasta raiz (`/root`). Salve.
5. Aguarde a publicação e teste o endereço informado pelo GitHub.

Não há dependências externas nem etapa de build para a página. Os links são relativos,
compatíveis com páginas de projeto do GitHub. Esta entrega não publicou um repositório remoto.

## Estrutura

```text
index.html / style.css / script.js
assets/           banner, arquitetura, circuito e JSON fictício
firmware/         sketch Arduino e instruções
platform/         tabela, regra EMQX, INSERT e consulta de exportação
docs/             circuito, plataforma, fontes, validação e pendências
evidencias/        instruções para inserir evidências reais
```

## Limites do protótipo

A lista de UIDs não é autenticação criptográfica. Não há comprovação de passagem,
sensor de porta, aplicativo em tempo real, cadastro remoto ou fila persistente.
O acesso é decidido localmente mesmo sem rede. Um evento sem MQTT é registrado
no Serial e descartado; QoS 0 não garante persistência. Teste a queda de rede.
Nenhuma carga externa foi incluída sem confirmação da montagem.

Referências oficiais e distinção entre fatos e propostas: [docs/fontes.md](docs/fontes.md).
Roteiro de apresentação: [docs/validacao.md](docs/validacao.md).
# arcanjos
