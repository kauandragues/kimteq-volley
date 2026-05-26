# Planejamento — Simulador Tático de Vôlei (Terminal Windows)

## Visão geral

Programa interativo para terminal Windows que simula sistemas táticos de vôlei (5x1 e 4x2), com navegação por teclado entre fases do jogo organizadas como slides. Desenvolvido em C utilizando apenas `conio.h` e `windows.h`, sem bibliotecas externas.

**Simplificações adotadas para nível iniciante/intermediário:**
- Saída no terminal com `printf` padrão (sem `MultiByteToWideChar`/`WriteConsoleW`)
- Variável global `EstadoJogo estado` — evita passagem de struct como parâmetro
- Buffer global `caminho_global[TAM_CAMINHO]` — evita ponteiro `char *buffer`
- `enum Tela` para estados da tela (em vez de números mágicos 0, 1, 2)
- `scanf` para entrada de dados (em vez de `fgets` + `atoi`)
- Captura de teclas com `_getch()` do `conio.h`
- Zero `malloc`/`free` — apenas buffers fixos na pilha

---

## Telas do programa

### 1. Menu inicial

- Opção: Entrar em quadra
- Opção: Sair do programa
- Navegação por setas (cima/baixo), Enter para confirmar (captura com `_getch()`)

### 2. Seleção do sistema tático

- Opção 1: Sistema 5x1
- Opção 2: Sistema 4x2
- Navegação por setas (cima/baixo), Enter para confirmar (captura com `_getch()`) — igual ao menu

### 3. Tela de quadra — modo slides

Navegação responsiva por teclas entre as 6 fases e 6 rodízios, em tempo real.

Após selecionar o sistema, o usuário vai direto para a quadra sem escolha de rodízio.

|Fase|Arquivo|Descrição|
|---|---|---|
|1|01_base.txt|Posição base do rodízio|
|2|02_passe.txt|Posição após o saque adversário|
|3|03_levantamento.txt|Posição no levantamento|
|4|04_corte.txt|Posição dos jogadores no ataque|
|5|05_defesa.txt|Posição de defesa|
|6|06_bloqueio.txt|Posição de bloqueio|

**Controles na tela de quadra:**

|Tecla|Ação|
|---|---|---|
|`→` (direita)|Próxima fase|
|`←` (esquerda)|Fase anterior|
|`↑` (cima)|Rodízio seguinte (1→2→3→4→5→6→1...)|
|`↓` (baixo)|Rodízio anterior (6→5→4→3→2→1→6...)|
|`S`|Trocar sistema tático|
|`ESC`|Voltar ao menu principal|

> **Todas as interações usam `_getch()`** — nenhuma tecla requer Enter para confirmar.

---

## Estrutura de arquivos

```
volei_simulator/
├── include/
│   └── volei.h
├── src/
│   ├── main.c
│   ├── telas.c
│   └── arquivos.c
├── slides/
│   ├── 5x1/
│   │   ├── rod1/
│   │   │   ├── 01_base.txt
│   │   │   ├── 02_passe.txt
│   │   │   ├── 03_levantamento.txt
│   │   │   ├── 04_corte.txt
│   │   │   ├── 05_defesa.txt
│   │   │   └── 06_bloqueio.txt
│   │   ├── rod2/
│   │   ├── rod3/
│   │   ├── rod4/
│   │   ├── rod5/
│   │   └── rod6/
│   └── 4x2/
│       ├── rod1/
│       ├── rod2/
│       ├── rod3/
│       ├── rod4/
│       ├── rod5/
│       └── rod6/
└── gerar_slides.ps1
```

> Total de slides: 2 sistemas × 6 rodízios × 6 fases = **72 arquivos .txt**

---

## Responsabilidade de cada arquivo

### `volei.h`

- Structs do projeto (`EstadoJogo`, `Jogador`)
- `enum Tela` para os estados da navegação (`TELA_MENU`, `TELA_SELECAO`, `TELA_QUADRA`)
- `#define`s de cores ANSI
- Constantes do jogo (número de fases, rodízios, nomes dos sistemas)
- Variável global `extern EstadoJogo estado;`
- Buffer global `extern char caminho_global[TAM_CAMINHO];`
- Protótipos de todas as funções (sem parâmetros de EstadoJogo)

### `main.c`

- `#include "volei.h"`
- Declaração da variável global `EstadoJogo estado`
- Implementação de `capturarTecla()` com `_getch()`
- Loop principal com máquina de estados usando `enum Tela`
- Nenhuma lógica de interface — apenas chamadas de função

### `telas.c`

- `habilitarANSI()` — ativa VT processing e UTF-8 no console
- `limparTela()` — `system("cls")`
- `centralizarTexto()`, `centralizarTextoCor()` — posicionamento com `printf`
- `exibirMenuInicial()` — menu com destaque na opção selecionada
- `exibirSelecaoSistema()` — tela de seleção com `_getch()` (tecla direta, sem Enter)
- `exibirCabecalho()` — cabeçalho da quadra (sistema / rodízio / fase)
- `exibirBarraControles()` — barra de comandos na parte inferior
- `exibirQuadra()` — monta a tela completa (cabeçalho + slide + controles)
- Toda saída usa `printf` (sem `escrever`/`escreverf`)

### `arquivos.c`

- Buffer global `char caminho_global[TAM_CAMINHO]`
- Arrays globais `NOMES_FASES[6]`, `NOMES_SISTEMAS[2]`, `NOMES_ARQUIVOS_FASE[6]`
- `montarCaminho()` — monta caminho em `caminho_global` a partir do estado global
- `carregarSlide()` — abre/ler/fecha arquivo com `fopen`/`fgets`/`fclose`
- Tratamento de erro se arquivo não existir

---

## Cores ANSI no terminal Windows

Para usar ANSI é necessário habilitar o modo virtual no início do programa via `windows.h`:

```c
void habilitarANSI() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD modoAtual;
    GetConsoleMode(hConsole, &modoAtual);
    SetConsoleMode(hConsole, modoAtual | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    SetConsoleOutputCP(CP_UTF8);
}
```

Após `habilitarANSI()`, usa-se `printf` diretamente com os códigos ANSI:

```c
printf(VERDE_B "texto verde brilhante" RESET);
printf("\033[%d;%dH%s", linha, coluna, texto);  // posicionamento
```

**Definições de cores sugeridas:**

```c
// Reset
#define RESET       "\033[0m"

// Texto
#define VERMELHO    "\033[31m"
#define VERDE       "\033[32m"
#define AMARELO     "\033[33m"
#define AZUL        "\033[34m"
#define CIANO       "\033[36m"
#define BRANCO      "\033[37m"

// Texto brilhante
#define VERMELHO_B  "\033[91m"
#define VERDE_B     "\033[92m"
#define AMARELO_B   "\033[93m"
#define AZUL_B      "\033[94m"
#define CIANO_B     "\033[96m"
#define BRANCO_B    "\033[97m"

// Fundo
#define BG_PRETA    "\033[40m"
#define BG_VERDE    "\033[42m"
#define BG_AZUL     "\033[44m"
#define BG_BRANCA   "\033[47m"

// Estilos
#define NEGRITO     "\033[1m"
#define SUBLINHADO  "\033[4m"
```

**Sugestão de cores por função de jogador:**

|Jogador|Cor sugerida|
|---|---|
|Levantador|`VERDE_B`|
|Ponteiro|`AMARELO`|
|Central|`CIANO_B`|
|Oposto|`VERMELHO`|
|Líbero|`BRANCO`|

---

## Requisitos acadêmicos — onde cada um aparece

|Requisito|Onde é implementado|
|---|---|
|Estrutura condicional|Validação de menu, seleção de sistema e fase|
|Estrutura de repetição|Loop principal do menu, loop de navegação, leitura de arquivo|
|Vetor e/ou Matriz|Array com nomes dos arquivos de fase (`NOMES_ARQUIVOS_FASE[6]`)|
|Struct|`EstadoJogo` (sistema, rodízio, fase, tela, opcao) e `Jogador`|
|Funções com parâmetro e retorno|`exibirSelecaoSistema()` retorna `int`, `carregarSlide()` retorna `int`|
|Manipulação de arquivos|`fopen`, `fgets`, `fclose` em `arquivos.c`|
|Validação de entrada|Loop `do/while` com `_getch()` na seleção de sistema|
|Código indentado|Padrão em todos os arquivos|
|Nomes representativos|`estado.sistema`, `estado.rodizio`, `estado.fase`, `caminho_global`|

---

## Tasks (Trello/Kanban)

### Task 1 — Setup do Ambiente e Estrutura do Projeto

**Contexto:** Antes de escrever código, é preciso preparar o compilador C e criar a estrutura de diretórios.

**Objetivo:** Instalar/configurar compilador, criar pastas do projeto e Makefile para compilação.

**Critérios de Aceite:**
- Compilador C (MinGW/gcc) instalado e funcional
- Terminal Windows configurado para UTF-8
- Estrutura de diretórios criada
- Makefile compila `gcc src/*.c -I include -o volei_simulator.exe -Wall`
- `printf` com cores ANSI funciona no terminal

**Regras de Negócio:**
- Apenas bibliotecas padrão C + `windows.h` + `conio.h`
- Executável deve rodar em cmd, PowerShell e Windows Terminal

**Descrição Técnica - TODO:**
- [ ] Verificar/instalar compilador C
- [ ] Criar diretórios: `include/`, `src/`, `slides/5x1/rod1..rod6`, `slides/4x2/rod1..rod6`
- [ ] Criar `Makefile` com regras `all`, `clean`, `run`
- [ ] Testar `printf` com cores ANSI

**Entregável:** Ambiente funcional, pastas criadas, Makefile pronto.

---

### Task 2 — Header `volei.h` com Enum e Global

**Contexto:** Arquivo central de definições incluído por todos os módulos.

**Objetivo:** Criar `include/volei.h` com structs, enum de telas, cores ANSI, constantes e protótipos.

**Critérios de Aceite:**
- Struct `Jogador`: `int numero`, `char funcao[15]`
- Enum `Tela`: `TELA_MENU=0, TELA_SELECAO=1, TELA_QUADRA=2`
- Struct `EstadoJogo`: `int sistema`, `int rodizio`, `int fase`, `Tela telaAtual`, `int opcaoSelecionada`
- Macros de cores ANSI completas (texto, brilhante, fundo, estilo)
- Constantes: `NUM_SISTEMAS=2`, `NUM_RODIZIOS=6`, `NUM_FASES=6`, `TAM_CAMINHO=120`
- Códigos de teclas: `KEY_CIMA=300`, `KEY_BAIXO=301`, `KEY_DIREITA=302`, `KEY_ESQUERDA=303`
- Variável global: `extern EstadoJogo estado;`
- Buffer global: `extern char caminho_global[TAM_CAMINHO];`
- Arrays globais `extern`: `NOMES_FASES[6]`, `NOMES_SISTEMAS[2]`, `NOMES_ARQUIVOS_FASE[6]`
- Protótipos de todas as funções (sem parâmetros de EstadoJogo)
- Include guards + includes: `windows.h`, `stdio.h`, `stdlib.h`, `string.h`, `conio.h`

**Regras de Negócio:**
- Nomes representativos em português
- Sem `stdarg.h` (não usamos `escreverf`)

**Descrição Técnica - TODO:**
- [ ] Include guards + headers do sistema
- [ ] Macros de cores ANSI
- [ ] Constantes do jogo
- [ ] `typedef enum Tela { TELA_MENU, TELA_SELECAO, TELA_QUADRA } Tela;`
- [ ] `typedef struct` `Jogador` e `EstadoJogo`
- [ ] Variável global `extern EstadoJogo estado;`
- [ ] Buffer global `extern char caminho_global[TAM_CAMINHO];`
- [ ] Arrays globais `extern`
- [ ] Protótipos de funções

**Entregável:** `include/volei.h` completo.

---

### Task 3 — Funções de Terminal e UI (`telas.c`)

**Contexto:** Funções de baixo nível para controle do terminal e utilidades de tela.

**Objetivo:** Implementar em `src/telas.c`: `habilitarANSI()`, `limparTela()`, `centralizarTexto()`, `centralizarTextoCor()`.

**Critérios de Aceite:**
- `habilitarANSI()`: `GetStdHandle` + `GetConsoleMode` + `SetConsoleMode(ENABLE_VIRTUAL_TERMINAL_PROCESSING)` + `SetConsoleOutputCP(CP_UTF8)`
- `limparTela()`: `system("cls")`
- `centralizarTexto(int y, const char *texto)`: posiciona cursor em y e coluna `(80 - strlen(texto)) / 2`
- `centralizarTextoCor(int y, const char *texto, const char *cor)`: igual anterior com cor + RESET
- Tudo com `printf` — sem `escrever`, `escreverf`, `malloc` ou `MultiByteToWideChar`

**Regras de Negócio:**
- Largura fixa do terminal = 80 colunas

**Descrição Técnica - TODO:**
- [ ] `habilitarANSI()` — modo VT + UTF-8
- [ ] `limparTela()` — `system("cls")`
- [ ] `centralizarTexto(int y, const char *texto)`
- [ ] `centralizarTextoCor(int y, const char *texto, const char *cor)`

**Entregável:** `src/telas.c` com utilidades de terminal.

---

### Task 4 — Módulo de Arquivos (`arquivos.c`)

**Contexto:** O programa lê slides de formação tática de arquivos `.txt`.

**Objetivo:** Implementar arrays de nomes, `montarCaminho()` e `carregarSlide()` em `src/arquivos.c`.

**Critérios de Aceite:**
- Arrays globais: `NOMES_FASES[6]`, `NOMES_SISTEMAS[2]`, `NOMES_ARQUIVOS_FASE[6]`
- Buffer global: `char caminho_global[TAM_CAMINHO]`
- `montarCaminho()` (sem parâmetros): monta `"slides/{5x1|4x2}/rod{N}/{arquivo}"` em `caminho_global` usando `sprintf`
- `carregarSlide()` (sem parâmetros): abre `caminho_global` com `fopen`, lê com `fgets`, imprime com `printf`, fecha com `fclose`
- Se arquivo não existir: exibe erro em VERMELHO_B, `_getch()`, retorna 0
- Sucesso: retorna 1

**Regras de Negócio:**
- Acessa variável global `estado` diretamente
- Sem ponteiros explícitos (buffer global em vez de `char *buffer`)

**Descrição Técnica - TODO:**
- [ ] Declarar `char caminho_global[TAM_CAMINHO]`
- [ ] Definir arrays globais de nomes
- [ ] `montarCaminho()`
- [ ] `carregarSlide()` com fopen/fgets/printf/fclose
- [ ] Tratamento de erro

**Entregável:** `src/arquivos.c` funcional.

---

### Task 5 — Menu Inicial

**Contexto:** Primeira tela que o usuário vê — duas opções navegáveis por setas.

**Objetivo:** Implementar `exibirMenuInicial()` em `src/telas.c`.

**Critérios de Aceite:**
- Título "SIMULADOR TATICO DE VOLEI" centralizado com moldura CIANO
- Opção "ENTRAR EM QUADRA": se `estado.opcaoSelecionada == 0`, destaca em VERDE_B com `>>` e `<<`; senão, BRANCO
- Opção "SAIR DO PROGRAMA": se `estado.opcaoSelecionada == 1`, destaca em VERMELHO_B com `>>` e `<<`; senão, BRANCO
- Rodapé: "Use as setas ↑↓ para navegar e ENTER para selecionar" em AMARELO
- Sem parâmetros — acessa variável global `estado`

**Regras de Negócio:**
- Função apenas de renderização — não modifica `estado`

**Descrição Técnica - TODO:**
- [ ] limparTela() + moldura superior
- [ ] Título centralizado e colorido
- [ ] Condicional para cada opção (selecionada vs não selecionada)
- [ ] Rodapé com instruções de navegação

**Entregável:** `exibirMenuInicial()` em `telas.c`.

---

### Task 6 — Seleção de Sistema Tático

**Contexto:** Tela onde o usuário escolhe entre Sistema 5x1 ou 4x2, com o mesmo padrão de navegação do menu.

**Objetivo:** Implementar `exibirSelecaoSistema()` em `src/telas.c` com setas + Enter (igual ao menu).

**Critérios de Aceite:**
- Título "SELECIONE O SISTEMA TATICO" centralizado
- Opção "Sistema 5x1 (1 Levantador, 5 Atacantes)" — se selecionada, destaca em VERDE_B com `>>` e `<<`; senão, BRANCO
- Opção "Sistema 4x2 (2 Levantadores, 4 Atacantes)" — se selecionada, destaca em VERDE_B com `>>` e `<<`; senão, BRANCO
- Rodapé: "Use as setas ↑↓ para navegar e ENTER para selecionar" em AMARELO
- Seta cima/baixo alterna opção selecionada
- Enter confirma e retorna 1 (5x1) ou 2 (4x2)
- `limparTela()` a cada iteração do `do/while`

**Regras de Negócio:**
- Captura de teclas com `_getch()` e tratamento de teclas extendidas (72/80)

**Descrição Técnica - TODO:**
- [ ] limparTela + título
- [ ] Condicional para cada opção (selecionada vs não selecionada)
- [ ] Rodapé com instruções
- [ ] `do/while` com `_getch()` + detecção de setas extendidas
- [ ] Enter confirma e retorna `opcao + 1`

**Entregável:** `exibirSelecaoSistema()` funcional.

---

### Task 7 — Cabeçalho e Barra de Controles

**Contexto:** Durante a visualização da quadra, o usuário precisa de informações do estado e dos comandos.

**Objetivo:** Implementar `exibirCabecalho()` e `exibirBarraControles()` em `src/telas.c`.

**Critérios de Aceite:**
- `exibirCabecalho()`: moldura CIANO, sistema em VERDE_B, rodízio+fase em AMARELO_B
- `exibirBarraControles()`: `▶` Prox, `◀` Ant, `▲` Rod+, `▼` Rod-, `S` Sistema, `ESC` Menu com cores
- Sem parâmetros — usam variável global `estado`

**Descrição Técnica - TODO:**
- [ ] `exibirCabecalho()` com estado.sistema, estado.rodizio, estado.fase
- [ ] `exibirBarraControles()` com todos os comandos

**Entregável:** Funções de cabeçalho e controles.

---

### Task 8 — Tela da Quadra

**Contexto:** Tela principal que integra cabeçalho, slide e controles.

**Objetivo:** Implementar `exibirQuadra()` em `src/telas.c`.

**Critérios de Aceite:**
- `limparTela()` + `exibirCabecalho()` + `carregarSlide()` + `exibirBarraControles()`
- Tela completa e responsiva

**Descrição Técnica - TODO:**
- [ ] limparTela()
- [ ] exibirCabecalho()
- [ ] carregarSlide()
- [ ] exibirBarraControles()

**Entregável:** `exibirQuadra()` funcional.

---

### Task 9 — Captura de Teclas

**Contexto:** O programa precisa interpretar setas (teclas extendidas) e teclas comuns.

**Objetivo:** Implementar `capturarTecla()` em `src/main.c`.

**Critérios de Aceite:**
- `_getch()` para captura sem eco
- Se 0 ou 224 (prefixo extendido): segundo `_getch()` mapeia 72→KEY_CIMA, 80→KEY_BAIXO, 77→KEY_DIREITA, 75→KEY_ESQUERDA
- Teclas normais: Enter=13, ESC=27, 'S'=83, 's'=115 — retorna o código

**Descrição Técnica - TODO:**
- [ ] Detecção de tecla extendida (0 ou 224)
- [ ] Switch para mapear setas
- [ ] Retorno de teclas normais

**Entregável:** `capturarTecla()` em `main.c`.

---

### Task 10 — Loop Principal

**Contexto:** Orquestrador do programa com máquina de estados.

**Objetivo:** Implementar `main()` em `src/main.c` com loop e `switch (estado.telaAtual)`.

**Critérios de Aceite:**
- Declara `EstadoJogo estado = {1, 1, 0, TELA_MENU, 0}` (variável global)
- `habilitarANSI()` no início
- `switch (estado.telaAtual)`:
  - `TELA_MENU`: exibe menu, setas alternam opcao, Enter confirma
  - `TELA_SELECAO`: chama `exibirSelecaoSistema()`, avança para quadra
  - `TELA_QUADRA`: exibe quadra, setas navegam fases/rodízios, S troca sistema, ESC volta
- Mensagem de saída ao encerrar

**Regras de Negócio:**
- Rodízio cicla: 1→2→...6→1
- Fase NÃO cicla: 0..5
- Usa `enum Tela` em vez de números mágicos

**Descrição Técnica - TODO:**
- [ ] Declarar variável global `EstadoJogo estado`
- [ ] habilitarANSI()
- [ ] Case TELA_MENU com navegação
- [ ] Case TELA_SELECAO
- [ ] Case TELA_QUADRA com navegação completa
- [ ] Mensagem de saída

**Entregável:** `src/main.c` completo.

---

### Task 11 — Criação dos 72 Slides (Script PowerShell)

**Contexto:** Os slides de formação são arquivos `.txt` com diagrama ASCII da quadra.

**Objetivo:** Criar `gerar_slides.ps1` que gere todos os 72 arquivos com posições táticas corretas.

**Critérios de Aceite:**
- Função `CriaSlide` que gera arquivo com diagrama de 42 caracteres:
  - Cabeçalho: sistema, rodízio, fase
  - Rede: `========= REDE =========`
  - Linha de jogadores: `P4(Cargo) P3(Cargo) P2(Cargo)`
  - Linha de jogadores: `P5(Cargo) P6(Cargo) P1(Cargo)`
  - Descrição tática + observação
- 36 slides para sistema 5x1 (6 fases × 6 rodízios)
- 36 slides para sistema 4x2 (6 fases × 6 rodízios)
- Posições variam por rodízio (rotação)

**Regras de Negócio:**
- Sistema 5x1: 1 Lev, 1 Opo, 2 Pon, 2 Cen
- Sistema 4x2: 2 Lev, 2 Pon, 2 Cen
- Arquivos em: `slides/{5x1|4x2}/rod{N}/{01_base|...|06_bloqueio}.txt`

**Descrição Técnica - TODO:**
- [ ] Função CriaSlide() com here-string
- [ ] Dados dos 6 rodízios do 5x1
- [ ] Dados dos 6 rodízios do 4x2
- [ ] Executar script

**Entregável:** `gerar_slides.ps1` + 72 arquivos `.txt`.

---

### Task 12 — Testes Integrados e Validação Final

**Contexto:** O programa completo precisa ser compilado e testado em todos os fluxos.

**Objetivo:** Compilar, testar navegação completa e corrigir bugs.

**Critérios de Aceite:**
- `gcc src/*.c -I include -o volei_simulator.exe -Wall` sem warnings
- Menu: setas alternam opções, Enter confirma
- Seleção: "1" ou "2" funciona; inválido repete sem travar
- Quadra: 6 fases × 6 rodízios × 2 sistemas carregam
- Navegação completa: →/← fases, ↑/↓ rodízios (cíclico), S sistema, ESC menu
- "Sair" encerra sem crash
- Cores ANSI visíveis no terminal

**Descrição Técnica - TODO:**
- [ ] Compilar sem warnings
- [ ] Testar fluxo completo: Menu → 5x1 → navegar → S → 4x2 → ESC → Sair
- [ ] Testar entradas inválidas
- [ ] Verificar todos os 72 slides
- [ ] Testar em cmd e Windows Terminal
- [ ] Corrigir bugs

**Entregável:** `volei_simulator.exe` compilado e testado.
