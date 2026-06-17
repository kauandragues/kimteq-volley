#include "volei.h"

void habilitarANSI()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                        // inicializa o manipulador do terminal windows
    DWORD modoAtual;                                                          // variavel para guardar as configs atuais do terminal
    GetConsoleMode(hConsole, &modoAtual);                                     // recebe as configs atuais do terminal
    SetConsoleMode(hConsole, modoAtual | ENABLE_VIRTUAL_TERMINAL_PROCESSING); // ativa o ANSI do terminal ou fica com a config atual
    SetConsoleOutputCP(CP_UTF8);                                              // faz o terminal reconhecer UTF-8
}

void limparTela()
{
    system("cls");
}

void centralizarTexto(int y, const char *texto)
{
    printf("\033[%d;%dH%s", y, (80 - (int)strlen(texto)) / 2, texto);
    // centralizar um texto horizontalemente em uma determinada linha y
}

void centralizarTextoCor(int y, const char *texto, const char *cor)
{
    printf("\033[%d;%dH%s%s%s", y, (80 - (int)strlen(texto)) / 2, cor, texto, RESET);
    // centralizar um texto horizontalemente em uma determinada linha y, com uma cor das constantes do volei.h
}

void exibirMenuInicial()
{
    limparTela();

    printf("\n\n\n");
    centralizarTextoCor(4, "========================================", CIANO);
    centralizarTextoCor(5, "   SIMULADOR TATICO DE VOLEI", VERDE_B);
    centralizarTextoCor(6, "========================================", CIANO);
    printf("\n\n\n");

    if (estado.opcaoSelecionada == 0)
    {
        centralizarTextoCor(10, ">> ENTRAR EM QUADRA <<", VERDE_B);
    }
    else
    {
        centralizarTextoCor(10, "   ENTRAR EM QUADRA", BRANCO);
    }

    if (estado.opcaoSelecionada == 1)
    {
        centralizarTextoCor(12, ">> SAIR DO PROGRAMA <<", VERDE_B);
    }
    else
    {
        centralizarTextoCor(12, "   SAIR DO PROGRAMA", BRANCO);
    }

    printf("\n\n\n\n\n\n\n\n");
    centralizarTextoCor(22, "Use as setas \033[1;32m\u2191\u2193\033[0m para navegar e ENTER para selecionar", AMARELO);
}

void exibirSelecaoSistema(int opcao) // 0 = 5x1  1 = 4x2
{

    limparTela();
    printf("\n\n\n");
    centralizarTextoCor(4, "========================================", CIANO);
    centralizarTextoCor(5, "      SELECIONE O SISTEMA TATICO", VERDE_B);
    centralizarTextoCor(6, "========================================", CIANO);
    printf("\n\n\n\n");

    if (opcao == 0)
    {
        centralizarTextoCor(10, ">> Sistema 5x1 (1 Levantador, 5 Atacantes) <<", VERDE_B);
    }
     else
    {
        centralizarTextoCor(10, "   Sistema 5x1 (1 Levantador, 5 Atacantes)", BRANCO);
    }
    printf("\n");
    if (opcao == 1)
    {
        centralizarTextoCor(12, ">> Sistema 4x2 (2 Levantadores, 4 Atacantes) <<", VERDE_B);
    }
    else
    {
        centralizarTextoCor(12, "   Sistema 4x2 (2 Levantadores, 4 Atacantes)", BRANCO);
    }

    printf("\n\n\n\n\n\n\n\n");
    centralizarTextoCor(21, "Use as setas \033[1;32m\u2191\u2193\033[0m para navegar e ENTER para selecionar", AMARELO);

}

void exibirCabecalho()
{
    printf("%s%s===========================================%s\n", NEGRITO, CIANO, RESET);
    printf("%s%s  %s - Rodizio %d%s", NEGRITO, VERDE_B,
           NOMES_SISTEMAS[estado.sistema - 1], estado.rodizio, RESET);
    printf("%s  %s%s\n", AMARELO_B,
           NOMES_FASES[estado.fase], RESET);
    printf("%s%s===========================================%s", NEGRITO, CIANO, RESET);
}

void exibirBarraControles()
{
    printf("\n%s%s----------------------------------------%s\n", CIANO, NEGRITO, RESET);
    printf("%s%s\u25B6%sProx  %s%s\u25C0%sAnt  "
           "%s%s\u25B2%sRod+  %s%s\u25BC%sRod-  "
           "%s%sS%sSistema  %s%sESC%sMenu%s\n",
           NEGRITO, VERDE_B, RESET,
           NEGRITO, VERDE_B, RESET,
           NEGRITO, AMARELO_B, RESET,
           NEGRITO, AMARELO_B, RESET,
           NEGRITO, AZUL_B, RESET,
           NEGRITO, VERMELHO_B, RESET, RESET);
    printf("%s%s----------------------------------------%s\n", CIANO, NEGRITO, RESET);
}

void exibirQuadra()
{
    limparTela();
    exibirCabecalho();
    printf("\n");
    carregarSlide();
    exibirBarraControles();
}
