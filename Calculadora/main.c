#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calculadora.h"

void testar(char *expr) {
    char *infixa = getFormaInFixa(expr);
    float valor = getValorPosFixa(expr);

    printf("-------------------------------------------------\n");
    printf("PosFixa : %s\n", expr);
    printf("InFixa  : %s\n", infixa ? infixa : "ERRO");
    if(isnan(valor))
        printf("Valor   : ERRO\n");
    else
        printf("Valor   : %.6f\n");

    if(infixa) free(infixa);
}

int main() {

    testar("3 4 +");
    testar("3 4 -");
    testar("3 4 *");
    testar("3 4 /");
    testar("10 3 %");
    testar("2 3 ^");
    testar("9 raiz");
    testar("30 sen");
    testar("45 cos");
    testar("60 tg");
    testar("100 log");

    return 0;
}
