#include "volei.h"

EstadoJogo estado;

int main() {
    estado.sistema = 0; // inicializa com 5x1
    estado.rodizio = 1; // inicializa com rod1
    estado.fase = 0;    // inicializa com fase 1
    estado.telaAtual = 0; // inicializar com tela menu
    estado.opcaoSelecionada = 0; // inicializa com opção 1

    int tecla;
    int rodando = 1;

    habilitarANSI();

    while (rodando) {
        switch (estado.telaAtual) {
            case 0: // TELA DE MENU
                exibirMenuInicial();
                tecla = capturarTecla();

                switch(tecla){
                    case CIMA:
                    case BAIXO: 
                        estado.opcaoSelecionada = !estado.opcaoSelecionada; // troca as opções do menu
                        break;
                    case ENTER:
                        if (estado.opcaoSelecionada == 1) {
                            rodando = 0; // para o programa
                        } else {
                            estado.sistema = 0; // reinicia para 5x1
                            estado.rodizio = 1; // reinicia para rod1
                            estado.fase = 0; // reinicia para fase 1
                            estado.telaAtual = 1; // tela de seleção do sistema
                            estado.opcaoSelecionada = 0;
                        }
                        break;
                }
                break;

            case 1: // TELA DE SELEÇÃO DO SISTEMA
                exibirSelecaoSistema(estado.opcaoSelecionada);
                tecla = capturarTecla();

                switch(tecla){
                    case CIMA:
                    case BAIXO:
                        estado.opcaoSelecionada = !estado.opcaoSelecionada;
                        break;
                    case ENTER:
                        if (estado.opcaoSelecionada == 0) { // 5x1
                            estado.sistema = 0; // reinicia para 5x1
                            estado.rodizio = 1; // reinicia para rod1
                            estado.fase = 0; // reinicia para fase 1
                            estado.telaAtual = 2; // tela de quadra
                        } else {// 4x2
                            estado.sistema = 1; // sistema 4x2
                            estado.rodizio = 1; // reinicia para rod1
                            estado.fase = 0; // reinicia para fase 1
                            estado.telaAtual = 2; // tela de quadra
                        }
                        break;
                }
                break;

            case 2: // TELA DE QUADRA
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
                        estado.telaAtual = 1;
                        break;
                    case ESC:
                        estado.telaAtual = 0;
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

