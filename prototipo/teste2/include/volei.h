#ifndef VOLEI_H
#define VOLEI_H

// 1. Configurações de ambiente para o Windows antes de qualquer include
#ifdef _WIN32
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0600 // Define alvo como Windows Vista/7/10+ para liberar constantes modernas
    #endif
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN    // Exclui APIs antigas e raramente usadas para acelerar a compilação
    #endif
    #include <windows.h>
    
    // Fallback de segurança para compiladores antigos
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#endif

// 2. Bibliotecas padrão do C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// 3. Definições de cores e estilos ANSI para o terminal
#define RESET       "\033[0m"
#define VERMELHO    "\033[31m"
#define VERDE       "\033[32m"
#define AMARELO     "\033[33m"
#define AZUL        "\033[34m"
#define CIANO       "\033[36m"
#define BRANCO      "\033[37m"
#define VERMELHO_B  "\033[91m"
#define VERDE_B     "\033[92m"
#define AMARELO_B   "\033[93m"
#define AZUL_B      "\033[94m"
#define CIANO_B     "\033[96m"
#define BRANCO_B    "\033[97m"
#define BG_PRETA    "\033[40m"
#define BG_VERDE    "\033[42m"
#define BG_AZUL     "\033[44m"
#define BG_BRANCA   "\033[47m"
#define NEGRITO     "\033[1m"
#define SUBLINHADO  "\033[4m"

// 4. Constantes do simulador
#define NUM_SISTEMAS 2
#define NUM_RODIZIOS 6
#define NUM_FASES    6
#define TAM_CAMINHO  120

#define KEY_CIMA     300
#define KEY_BAIXO    301
#define KEY_DIREITA  302
#define KEY_ESQUERDA 303

// 5. Tipos de dados e Enums
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
} EstadoJogo;

// 6. Declarações de variáveis globais (extern)
extern EstadoJogo estado;
extern char caminho_global[TAM_CAMINHO];

extern const char *NOMES_FASES[];
extern const char *NOMES_SISTEMAS[];
extern const char *NOMES_ARQUIVOS_FASE[];

// 7. Protótipos das funções
void habilitarANSI(void);
void limparTela(void);
void centralizarTexto(int y, const char *texto);
void centralizarTextoCor(int y, const char *texto, const char *cor);

void exibirMenuInicial(void);
int exibirSelecaoSistema(void);
void exibirCabecalho(void);
void exibirBarraControles(void);
void exibirQuadra(void);

void montarCaminho(void);
int carregarSlide(void);

int capturarTecla(void);

#endif // VOLEI_H