#include "volei.h"

EstadoJogo estado;

int capturarTecla() {
    int tecla = _getch();
    if (tecla == 0 || tecla == 224) {
        int ext = _getch();
        switch (ext) {
            case 72:    return CIMA;
            case 80:   return BAIXO;
            case 77: return DIREITA;
            case 75: return ESQUERDA;
        }
    }
    return tecla;
}

int main() {
    estado.sistema = 1;
    estado.rodizio = 1;
    estado.fase = 0;
    estado.telaAtual = TELA_MENU;
    estado.opcaoSelecionada = 0;

    int tecla;
    int rodando = 1;

    habilitarANSI();

    while (rodando) {
        switch (estado.telaAtual) {
            case TELA_MENU:
                exibirMenuInicial();
                tecla = capturarTecla();

                if (tecla == CIMA || tecla == BAIXO) {
                    estado.opcaoSelecionada = !estado.opcaoSelecionada;
                } else if (tecla == ENTER) {
                    if (estado.opcaoSelecionada == 1) {
                        rodando = 0;
                    } else {
                        estado.sistema = 1;
                        estado.rodizio = 1;
                        estado.fase = 0;
                        estado.telaAtual = TELA_SELECAO;
                    }
                }
                break;

            case TELA_SELECAO:
                estado.sistema = exibirSelecaoSistema();
                estado.rodizio = 1;
                estado.fase = 0;
                estado.telaAtual = TELA_QUADRA;
                break;

            case TELA_QUADRA:
                exibirQuadra();
                tecla = capturarTecla();

                switch (tecla) {
                    case DIREITA:
                        if (estado.fase < NUM_FASES - 1) estado.fase++;
                        break;
                    case ESQUERDA:
                        if (estado.fase > 0) estado.fase--;
                        break;
                    case CIMA:
                        if (++estado.rodizio > NUM_RODIZIOS) estado.rodizio = 1;
                        break;
                    case BAIXO:
                        if (--estado.rodizio < 1) estado.rodizio = NUM_RODIZIOS;
                        break;
                    case 'S': case 's':
                        estado.telaAtual = TELA_SELECAO;
                        break;
                    case ESC:
                        estado.telaAtual = TELA_MENU;
                        estado.opcaoSelecionada = 0;
                        break;
                }
                break;
        }
    }

    limparTela();
    centralizarTextoCor(12, "Obrigado por usar o Simulador Tatico de Volei!", VERDE_B);
    printf("\033[13;1H");
    return 0;
}

