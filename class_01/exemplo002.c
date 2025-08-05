#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float numerador;
    float denominador;    
} Fracao;

Fracao criarFracao(float N, float D)  {
    Fracao F;
    F.numerador = N;
    F.denominador = D;
    return F;
}

int main(){

    int t = sizeof(Fracao);
    printf("Tamanho: %d\n", t);

    Fracao F1 = criarFracao(7, 2);
    printf("o valor de F1 eh %.2f.\n", F1.numerador/F1.denominador);

}


