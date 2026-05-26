#ifndef VOLEI_H
#define VOLEI_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define NUM_SISTEMAS 2
#define NUM_RODIZIOS 6
#define NUM_FASES 6
#define TAM_CAMINHO 120

#define KEY_CIMA    300
#define KEY_BAIXO   301
#define KEY_DIREITA 302
#define KEY_ESQUERDA 303

typedef enum {
    TELA_MENU,
    TELA_SELECAO,
    TELA_QUADRA
} Tela;

typedef struct {
    int numero;
    char funcao[15];
} Jogador;

typedef struct {
    int sistema;
    int rodizio;
    int fase;
    Tela telaAtual;
    int opcaoSelecionada;
} EstadoGlobal;

extern EstadoGlobal estado;

#endif
