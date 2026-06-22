# KIMTEQ - Volleyball

## Visão geral

Programa interativo para terminal Windows que simula sistemas táticos de vôlei (5x1 e 4x2), com navegação por teclado entre fases do jogo organizadas como "slides". Desenvolvido em C utilizando `conio.h` e `windows.h`.

---

## Telas do programa

### 1. Menu inicial

- **Entrar em quadra** — inicia a simulação
- **Sair do programa** — encerra o programa
- Navegação por setas (cima/baixo), Enter para confirmar

### 2. Seleção do sistema tático

- **Sistema 5x1** (1 levantador, 5 atacantes)
- **Sistema 4x2** (2 levantadores, 4 atacantes)
- **Voltar** — retorna ao menu inicial
- Navegação por setas (cima/baixo), Enter para confirmar

### 3. Tela de quadra

Exibe a formação tática na quadra com base no sistema e rodízio selecionados.

| Tecla | Ação |
|---|---|
| `→` (direita) | Próxima fase |
| `←` (esquerda) | Fase anterior |
| `↑` (cima) | Rodízio seguinte (1→2→3→...→6→1) |
| `↓` (baixo) | Rodízio anterior (6→5→4→3→...→1→6) |
| `S` | Voltar à seleção de sistema tático |
| `ESC` | Voltar ao menu principal |

#### Fases do 5x1

| Fase | Arquivo | Descrição |
|---|---|---|
| 1 | `01_base.txt` | Posição base do rodízio |
| 2 | `02_Saque.txt` | Posição de saque |
| 3 | `03_defesa.txt` | Posição de defesa |
| 4 | `04_Ataque.txt` | Posição de ataque |
| 5 | `05_Recpcao.txt` | Posição de recepção |

#### Fases do 4x2

| Fase | Arquivo | Descrição |
|---|---|---|
| 1 | `01_Saque.txt` | Posição de saque |
| 2 | `02_Recepcao.txt` | Posição de recepção |

> O sistema 5x1 possui 6 rodízios (rod1 a rod6); o 4x2 possui 3 rodízios (rod1 a rod3).

---

## Estrutura de arquivos

```
kimteq-volley/
├── Makefile
├── pintor.py
├── src/
│   ├── main.c          # Loop principal e máquina de estados
│   ├── volei.h         # Structs, constantes e protótipos
│   ├── telas.c         # Renderização das telas
│   ├── teclado.c       # Captura de teclas (setas, Enter, ESC)
│   └── arquivos.c      # Leitura dos arquivos de quadra
└── quadras/
    ├── 5x1/
    │   ├── rod1/       # 01_base, 02_Saque, 03_defesa, 04_Ataque, 05_Recpcao
    │   ├── rod2/       # (mesmos 5 arquivos)
    │   ├── rod3/
    │   ├── rod4/
    │   ├── rod5/
    │   └── rod6/
    └── 4x2/
        ├── rod1/       # 01_Saque, 02_Recepcao
        ├── rod2/       # (mesmos 2 arquivos)
        └── rod3/
```

---

## Como compilar e executar

### Requisitos

- Sistema operacional Windows
- Compilador GCC (MinGW ou equivalente)
- Python 3.x (opcional, para colorir as quadras)

### Compilar

No diretório raiz do projeto, execute:

```
make
```

Isso gera o executável `volei_simulator.exe`.

Para compilar manualmente sem o Makefile:

```
gcc -Wall -I src src/main.c src/telas.c src/arquivos.c src/teclado.c -o volei_simulator.exe
```

### Executar

Após compilar, execute:

```
make run
```

Ou diretamente:

```
volei_simulator.exe
```

### Limpar

Remove o executável gerado:

```
make clean
```

### Colorir as quadras (opcional)

As marcações de jogadores nos arquivos de quadra podem ser coloridas automaticamente:

```
python pintor.py
```

Isso percorre todos os arquivos `.txt` em `quadras/` e aplica cores ANSI aos marcadores de posição dos jogadores.

---

## Legenda dos jogadores

| Marcação | Cor | Posição |
|---|---|---|
| `[O]` | Vermelho | Oposto |
| `[Li]` | Azul | Líbero |
| `[P1]` | Amarelo | Ponta 1 |
| `[P2]` | Amarelo | Ponta 2 |
| `[LV]` | Verde | Levantador |
| `[C1]` | Ciano | Central 1 |
| `[C2]` | Ciano | Central 2 |

---

## Licença

MIT — veja o arquivo [LICENSE](LICENSE) para detalhes.
