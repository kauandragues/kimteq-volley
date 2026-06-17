#include "volei.h"

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