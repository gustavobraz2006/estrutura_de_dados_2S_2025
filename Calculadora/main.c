#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calculadora.h"

// Função que executa um teste individual
void testar(char *posfixa){
    Expressao e;
    strcpy(e.posFixa, posfixa);

    // Converte para infixa
    char *inf = getFormaInFixa(e.posFixa);
    if(inf == NULL){
        printf("\nexpressao posfixa: %s\n", e.posFixa);
        printf("expressao infixa: ERRO\n");
        printf("valor da expressao: ERRO\n");
        return;
    }

    strcpy(e.inFixa, inf);
    free(inf);

    // Avalia o valor
    e.Valor = getValorPosFixa(e.posFixa);

    printf("\nexpressao posfixa: %s\n", e.posFixa);
    printf("expressao infixa: %s\n", e.inFixa);

    if(isnan(e.Valor))
        printf("valor da expressao: ERRO\n");
    else
        printf("valor da expressao: %.6f\n", e.Valor);
}

int main(){

    
    testar("3 4 + 5 *");
    testar("7 2 * 4 +");
    testar("8 5 2 4 + * +");
    testar("6 2 / 3 + 4 *");
    testar("9 5 2 8 * 4 + * +");
    testar("2 3 + log 5 /");
    testar("10 log 3 ^ 2 +");
    testar("45 60 + 30 cos *");
    testar("0.5 45 sen 2 ^ +");

    return 0;
}
