#include "../include/volei.h"

const char *NOMES_FASES[] = {
    "1 - Posicao Base",
    "2 - Passe",
    "3 - Levantamento",
    "4 - Corte (Ataque)",
    "5 - Defesa",
    "6 - Bloqueio"
};

const char *NOMES_SISTEMAS[] = {
    "Sistema 5x1",
    "Sistema 4x2"
};

const char *NOMES_ARQUIVOS_FASE[] = {
    "01_base.txt",
    "02_passe.txt",
    "03_levantamento.txt",
    "04_corte.txt",
    "05_defesa.txt",
    "06_bloqueio.txt"
};

char caminho_global[TAM_CAMINHO];

void montarCaminho() {
    const char *sistemaStr = (estado.sistema == 1) ? "5x1" : "4x2";
    sprintf(caminho_global, "slides/%s/rod%d/%s",
            sistemaStr, estado.rodizio,
            NOMES_ARQUIVOS_FASE[estado.fase]);
}

int carregarSlide() {
    FILE *arquivo;
    char linha[150];

    montarCaminho();

    arquivo = fopen(caminho_global, "r");
    if (arquivo == NULL) {
        printf("\n  %sErro: arquivo nao encontrado!%s\n", VERMELHO_B, RESET);
        printf("  Caminho: %s\n", caminho_global);
        printf("\n  %sPressione qualquer tecla para voltar.%s", AMARELO, RESET);
        _getch();
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
    return 1;
}
