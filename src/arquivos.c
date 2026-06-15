#include "volei.h"

//ponteiro = Vetor de endereço de caracteres

//Constante que salva o nome de cada fase do jogo dentro de um rodízio, vai ser chamado no Telas para o cabeçalho
const char *NOMES_FASES[] = {
    "1 - Base",
    "2 - Saque", 
    "3 - Defesa",
    "4 - Ataque",
    "5 - Recepção",
};

//Constante que salva o nome de cada sistema do jogo, vai ser chamado no Telas para o cabeçalho
const char *NOMES_SISTEMAS[] = {
    "Sistema 5x1",
    "Sistema 4x2"
};

//Constante que salva o nome de cada arquivo de cada fase do jogo, vai ser chamado no Arquivos(este arquivo) para ler os arquivos .txt das quadras
const char *NOMES_ARQUIVOS_FASE[] = {
    "01_base.txt",
    "02_saque.txt",
    "03_defesa.txt",
    "04_ataque.txt",
    "05_recpcao.txt"
};

//Variável global que salva o estado atual do jogo, vai ser chamada em todas as telas para verificar o estado do jogo
char caminho_global[TAM_CAMINHO];

//Função que monta o caminho do arquivo .txt da quadra a ser lida, vai ser chamada na função carregarSlide() no arquivos.c
void montarCaminho(){
    const char *sistemaStr = (estado.sistema == 1) ? "5x1" : "4x2";
    snprintf(caminho_global, TAM_CAMINHO, "quadras/%s/rod%d/%s", sistemaStr, estado.rodizio, NOMES_ARQUIVOS_FASE[estado.fase]);
}

//Função que carrega os arquivos na tela, chamado em telas.c todas as vezes que muda a fase ou o rodizio ou qualquer coisa da tela que precise carregar um dos arquivos de quadra
int carregarSlide(){
    FILE *arquivo;
    char linha[90];

    montarCaminho();

    arquivo = fopen(caminho_global, "r");
    //Verifica se existe o arquivo no caminho global, se não tiver retorna 0
    if (arquivo == NULL) {
        printf("\n %sErro: arquivo não encontrado!%s\n", VERMELHO_B, RESET);
        printf(" Caminho: %s\n", caminho_global);
        printf("\n %sPressione qualquer tecla para voltar.%s", AMARELO, RESET);
        //_getch() serve pra capturar uma tecla do teclado.
        _getch();
        return 0;
    }

    //while para passar por todas as linhas do .txt
    while(fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    //Assim que terminar o while, fecha o arquivo e returna o valor 1
    fclose(arquivo);
    return 1;

}