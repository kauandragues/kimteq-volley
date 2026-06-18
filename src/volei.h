#ifndef VOLEI_H
#define VOLEI_H

// configurações para o include do windows.h
#ifdef _WIN32 // se for windows 32 ou 64 bits
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0600 // define que o windows precisa ser 7+
    #endif
    #include <windows.h> // incluir a biblioteca com a configuração acima
    
    // garante que o ANSI funcione mesmo quando o include o windows.h não definir
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004 // define as sequências de escape ANSI, caso não esteja definida
    #endif
#endif

// bibliotecas do C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// constanstes para usar cores e reset ANSI para o terminal
#define RESET       "\033[0m"
#define VERMELHO    "\033[31m"
#define AMARELO     "\033[33m"
#define CIANO       "\033[36m"
#define BRANCO      "\033[37m"
#define VERMELHO_B  "\033[91m"
#define VERDE_B     "\033[92m"
#define AMARELO_B   "\033[93m"
#define AZUL_B      "\033[94m"
#define NEGRITO     "\033[1m"

// constantes para usar no sistema
#define NUM_SISTEMAS 2
#define NUM_RODIZIOS_5x1 6
#define NUM_RODIZIOS_4x2 3
#define NUM_FASES_5x1    5
#define NUM_FASES_4x2    2
#define TAM_CAMINHO  120

#define CIMA    72
#define BAIXO   80
#define DIREITA 77
#define ESQUERDA 75
#define ENTER   13
#define ESC     27

// struct
typedef struct {
    int sistema;    // 0 = "5x1"  1 = "4x2"
    int rodizio;    // Posições em ordem de 1 a 6
    int fase;       // "5x1" --> Rotações de 1 a 5; "4x2" -->  Rotações de 1 a 2
    int telaAtual;  // 0 = Tela Menu  1 = Tela Seleção  2 = Tela Quadra
    int opcaoSelecionada; // 0 = Opção de cima  1 = Opção de baixo (Tela Menu e Tela Seleção)
} EstadoJogo;

// variáveis globais 
extern EstadoJogo estado;
extern char caminho_global[TAM_CAMINHO];

extern const char *NOMES_FASES[];
extern const char *NOMES_SISTEMAS[];
extern const char *NOMES_ARQUIVOS_FASE[];

// protótipos das funções
void habilitarANSI(void);
void limparTela(void);
void centralizarTexto(int y, const char *texto);
void centralizarTextoCor(int y, const char *texto, const char *cor);

void exibirMenuInicial(void);
void exibirSelecaoSistema(int opcao);
void exibirCabecalho(void);
void exibirBarraControles(void);
void exibirQuadra(void);

void montarCaminho(void);
void carregarSlide(void);

int capturarTecla(void);

#endif