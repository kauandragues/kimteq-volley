# KIMTEQ - Volleyball

## Visão geral

Programa interativo para terminal Windows que simula sistemas táticos de vôlei (5x1 e 4x2), com navegação por teclado entre fases do jogo organizadas como "slides". Desenvolvido em C utilizando apenas `conio.h` e `windows.h`.

---

## Telas do programa

### 1. Menu inicial

- Opção: Entrar em quadra
- Opção: Sair do programa
- Navegação por setas (cima/baixo), Enter para confirmar

### 2. Seleção do sistema tático

- Opção 1: Sistema 5x1
- Opção 2: Sistema 4x2
- Navegação por setas (cima/baixo), Enter para confirmar

### 3. Tela de quadra

Navegação responsiva por teclas entre as 5 fases e 6 rodízios, em tempo real.

Após selecionar o sistema, o usuário vai direto para a quadra sem escolha de rodízio.

|Fase|Arquivo|Descrição|
|---|---|---|
|1|01_base.txt|Posição base do rodízio|
|2|02_passe.txt|Posição após o saque adversário|
|3|03_levantamento.txt|Posição no levantamento|
|4|04_corte.txt|Posição dos jogadores no ataque|
|5|05_defesa.txt|Posição de defesa|

**Controles na tela de quadra:**

| Tecla| Ação|
| ---|---|
| `→` (direita)| Próxima fase|
| `←` (esquerda)| Fase anterior|
| `↑` (cima)| Rodízio seguinte (1→2→3→4→5→6→1...)|
| `↓` (baixo)| Rodízio anterior (6→5→4→3→2→1→6...)|
| `S`| Trocar sistema tático|
| `ESC`| Voltar ao menu principal|

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
└── quadras/
   ├── 5x1/
   │   ├── rod1/
   │   │   ├── 01_base.txt
   │   │   ├── 02_passe.txt
   │   │   ├── 03_levantamento.txt
   │   │   ├── 04_corte.txt
   │   │   ├── 05_defesa.txt
   │   │   └── 06_bloqueio.txt
   │   ├── rod2/
   │   ├── rod3/
   │   ├── rod4/
   │   ├── rod5/
   │   └── rod6/
   └── 4x2/
       ├── rod1/
       ├── rod2/
       ├── rod3/
       ├── rod4/
       ├── rod5/
       └── rod6/
```
---

## Como compilar o programa
- Vá até a pasta src
- Execute o comando:
``gcc main.c -o ../simulador.exe``
- Um simulador.exe deve ter sido criado na pasta principal do projeto
