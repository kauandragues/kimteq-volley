#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

// ==============================================================================
// 1. CONFIGURAÇÃO DO TERMINAL (Windows Moderno / Windows Terminal)
// ==============================================================================
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

void configurar_terminal() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    
    // 1. Ativa as cores ANSI e caracteres UTF-8
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
    SetConsoleOutputCP(CP_UTF8);

    // 2. Força o redimensionamento da janela usando sequência ANSI
    printf("\x1b[8;30;80t");

    // 3. Trava o Buffer interno (Remove barras de rolagem e fixa a matriz)
    COORD tamanho_buffer = {80, 30};
    SMALL_RECT tamanho_janela = {0, 0, 79, 29};
    
    SetConsoleWindowInfo(hOut, TRUE, &tamanho_janela);
    SetConsoleScreenBufferSize(hOut, tamanho_buffer);
}

// ==============================================================================
// 2. CONSTANTES E ESTRUTURAS DE DADOS (O "Backend")
// ==============================================================================
#define TECLA_ESPECIAL 224
#define SETA_CIMA 72
#define SETA_BAIXO 80
#define SETA_ESQUERDA 75
#define SETA_DIREITA 77
#define ENTER 13
#define ESC 27

typedef enum { ESTADO_MENU, ESTADO_TATICA, ESTADO_POSSE, ESTADO_QUADRA } EstadoPrograma;
typedef enum { RECEPCAO, ATAQUE, DEFESA } EstadoQuadra;
typedef enum { LEVANTADOR, OPOSTO, PONTEIRO, CENTRAL } FuncaoTatica;

struct Jogador {
    char sigla[5];
    FuncaoTatica funcao;
};

// ==============================================================================
// 3. LÓGICA DO VÔLEI (Array Circular)
// ==============================================================================
void inicializar_time(struct Jogador time[6]) {
    strcpy(time[0].sigla, "[L ]"); time[0].funcao = LEVANTADOR; 
    strcpy(time[1].sigla, "[C2]"); time[1].funcao = CENTRAL;    
    strcpy(time[2].sigla, "[P2]"); time[2].funcao = PONTEIRO;   
    strcpy(time[3].sigla, "[P1]"); time[3].funcao = PONTEIRO;   
    strcpy(time[4].sigla, "[C1]"); time[4].funcao = CENTRAL;    
    strcpy(time[5].sigla, "[O ]"); time[5].funcao = OPOSTO;     
}

void avancar_rodizio(struct Jogador time[6]) {
    struct Jogador temp = time[5];
    for (int i = 5; i > 0; i--) time[i] = time[i - 1];
    time[0] = temp;
}

void voltar_rodizio(struct Jogador time[6]) {
    struct Jogador temp = time[0];
    for (int i = 0; i < 5; i++) time[i] = time[i + 1];
    time[5] = temp;
}

// ==============================================================================
// 4. MOTOR DE RENDERIZAÇÃO E MATRIZ (O "Frontend")
// ==============================================================================
void limpar_tela() {
    printf("\033[2J\033[3J\033[H");
}

void desenhar_menu(int selecao) {
    limpar_tela();
    printf("\n\n");
    printf("\033[36m===================================================\033[0m\n");
    printf("           \033[1mSIMULADOR TATICO DE VOLEI\033[0m\n");
    printf("\033[36m===================================================\033[0m\n\n");
    const char* opcoes[] = {"Iniciar Nova Simulacao", "Sair do Programa"};
    for (int i = 0; i < 2; i++) {
        if (i == selecao) printf("    \033[7m > %s \033[0m\n", opcoes[i]);
        else printf("       %s \n", opcoes[i]);
    }
    printf("\n\033[90m(Use Setas UP/DOWN para navegar e ENTER para confirmar)\033[0m\n");
}

void desenhar_tatica(int selecao) {
    limpar_tela();
    printf("\n\n");
    printf("\033[33m===================================================\033[0m\n");
    printf("             \033[1mPASSO 1: SISTEMA TATICO\033[0m\n");
    printf("\033[33m===================================================\033[0m\n\n");
    const char* opcoes[] = {"[ 5-1 ] Avancado (Infiltracao)", "[ 4-2 ] Intermediario", "[ 6-0 ] Iniciante"};
    for (int i = 0; i < 3; i++) {
        if (i == selecao) printf("    \033[7m > %s \033[0m\n", opcoes[i]);
        else printf("       %s \n", opcoes[i]);
    }
    printf("\n\033[90m[ESC] Voltar  |  [ENTER] Confirmar\033[0m\n");
}

void desenhar_posse(int selecao) {
    limpar_tela();
    printf("\n\n");
    printf("\033[35m===================================================\033[0m\n");
    printf("             \033[1mPASSO 2: CENARIO DE JOGO\033[0m\n");
    printf("\033[35m===================================================\033[0m\n\n");
    printf("  Quem vai realizar o saque nesta jogada?\n\n");
    const char* opcoes[] = {"[ Adversario ] Foco em Recepcao e Ataque", "[ Nosso Time ] Foco em Saque e Bloqueio"};
    for (int i = 0; i < 2; i++) {
        if (i == selecao) printf("    \033[7m > %s \033[0m\n", opcoes[i]);
        else printf("       %s \n", opcoes[i]);
    }
    printf("\n\033[90m[ESC] Voltar  |  [ENTER] Confirmar\033[0m\n");
}

void desenhar_quadra(struct Jogador time[6], EstadoQuadra est_quadra, int rodizio, int posse) {
    limpar_tela();
    printf("\n");
    
    char tela[12][52];
    for (int i = 0; i < 12; i++) {
        strcpy(tela[i], "                                                  |");
        tela[i][0] = '|';
    }
    
    strcpy(tela[5], "|------------------- Linha de 3m -----------------|");

    // Coordenadas Base (Recepção)
    int coord_x[6] = {38, 22, 6, 6, 22, 38};
    int coord_y[6] = {8, 8, 8, 2, 2, 2};

    // Infiltração simples do Levantador
    if (est_quadra == ATAQUE) {
        for (int i = 0; i < 6; i++) {
            if (time[i].funcao == LEVANTADOR) {
                coord_y[i] = 1; 
                coord_x[i] = 28; 
            }
        }
    }

    // Renderiza jogadores na matriz
    for (int i = 0; i < 6; i++) {
        int x = coord_x[i];
        int y = coord_y[i];
        
        // Regra do Líbero
        if (time[i].funcao == CENTRAL && (i >= 0 && i <= 2)) {
            strncpy(&tela[y][x], "\033[31m[Li]\033[0m", 13); // Líbero em vermelho
        } else {
            strncpy(&tela[y][x], time[i].sigla, 4);
        }
    }

    // Imprime a matriz no terminal
    printf("\033[32m===================================================\033[0m\n");
    printf("             REDE (Lado do Adversario)      \n");
    printf("\033[32m===================================================\033[0m\n");
    for (int i = 0; i < 12; i++) {
        printf("%s\n", tela[i]);
    }
    printf("\033[32m===================================================\033[0m\n");
    
    printf(" STATUS: ");
    if (est_quadra == RECEPCAO) printf("Recepcao Base ");
    else if (est_quadra == ATAQUE) printf("\033[31mInfiltracao de Ataque\033[0m");
    else printf("\033[34mDefesa/Bloqueio\033[0m");
    printf(" | Rodizio: Pos %d\n", rodizio);
    printf("---------------------------------------------------\n");
    
    if (posse == 0) { 
        printf(" \033[90m[A] Ataque  [ESPACO] Voltar Base  [ESQ/DIR] Rodizio\033[0m\n");
    } else { 
        printf(" \033[90m[D] Defesa  [ESPACO] Voltar Base  [ESQ/DIR] Rodizio\033[0m\n");
    }
    printf(" \033[90m[ESC] Abortar e Voltar ao Menu Principal\033[0m\n");
}

// ==============================================================================
// 5. LOOP PRINCIPAL (A Máquina de Estados)
// ==============================================================================
int main() {
    configurar_terminal();

    EstadoPrograma estado_atual = ESTADO_MENU;
    EstadoQuadra estado_quadra = RECEPCAO;
    
    struct Jogador meu_time[6];
    inicializar_time(meu_time);

    int menu_sel = 0, tatica_sel = 0, posse_sel = 0;
    int rodizio_atual = 1;
    int executando = 1;

    while (executando) {
        // 1. RENDERIZA
        if (estado_atual == ESTADO_MENU) desenhar_menu(menu_sel);
        else if (estado_atual == ESTADO_TATICA) desenhar_tatica(tatica_sel);
        else if (estado_atual == ESTADO_POSSE) desenhar_posse(posse_sel);
        else if (estado_atual == ESTADO_QUADRA) desenhar_quadra(meu_time, estado_quadra, rodizio_atual, posse_sel);

        // 2. CAPTURA
        int tecla = _getch();

        // 3. ATUALIZA ESTADO
        if (estado_atual == ESTADO_MENU) {
            if (tecla == TECLA_ESPECIAL) {
                tecla = _getch();
                if (tecla == SETA_CIMA && menu_sel > 0) menu_sel--;
                if (tecla == SETA_BAIXO && menu_sel < 1) menu_sel++;
            } else if (tecla == ENTER) {
                if (menu_sel == 0) estado_atual = ESTADO_TATICA;
                if (menu_sel == 1) executando = 0;
            }
        } 
        else if (estado_atual == ESTADO_TATICA) {
            if (tecla == TECLA_ESPECIAL) {
                tecla = _getch();
                if (tecla == SETA_CIMA && tatica_sel > 0) tatica_sel--;
                if (tecla == SETA_BAIXO && tatica_sel < 2) tatica_sel++;
            } else if (tecla == ENTER) {
                estado_atual = ESTADO_POSSE; 
            } else if (tecla == ESC) {
                estado_atual = ESTADO_MENU;
            }
        }
        else if (estado_atual == ESTADO_POSSE) {
            if (tecla == TECLA_ESPECIAL) {
                tecla = _getch();
                if (tecla == SETA_CIMA && posse_sel > 0) posse_sel--;
                if (tecla == SETA_BAIXO && posse_sel < 1) posse_sel++;
            } else if (tecla == ENTER) {
                estado_quadra = RECEPCAO;
                estado_atual = ESTADO_QUADRA; 
            } else if (tecla == ESC) {
                estado_atual = ESTADO_TATICA;
            }
        }
        else if (estado_atual == ESTADO_QUADRA) {
            if (tecla == TECLA_ESPECIAL) {
                tecla = _getch();
                if (tecla == SETA_DIREITA) {
                    avancar_rodizio(meu_time);
                    estado_quadra = RECEPCAO; 
                    rodizio_atual = (rodizio_atual % 6) + 1;
                }
                if (tecla == SETA_ESQUERDA) {
                    voltar_rodizio(meu_time);
                    estado_quadra = RECEPCAO;
                    rodizio_atual = (rodizio_atual == 1) ? 6 : rodizio_atual - 1;
                }
            }
            else if ((tecla == 'a' || tecla == 'A') && posse_sel == 0) {
                estado_quadra = ATAQUE;
            }
            else if ((tecla == 'd' || tecla == 'D') && posse_sel == 1) {
                estado_quadra = DEFESA;
            }
            else if (tecla == ' ') { 
                estado_quadra = RECEPCAO;
            }
            else if (tecla == ESC) {
                estado_atual = ESTADO_MENU; 
            }
        }
    }

    limpar_tela();
    printf("\033[0mSimulador encerrado com sucesso.\n");
    return 0;
}