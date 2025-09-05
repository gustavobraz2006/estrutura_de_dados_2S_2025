#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processos.h"

int main() {

    Processos * P = LerDadosProcessos("TJDFT_filtrado.csv");

    printf("Numero de processos: %d\n", getnumProcessos(P));
    printf("Numero de processos com violência doméstica: %d\n", getviolenciadomestica(P));
    printf("Numero de processos com feminicídio: %d\n", getfeminicidios(P));
    printf("Numero de processos ambientais: %d\n", getambientais(P));
    printf("Numero de processos com comunidades quilombolas: %d\n", getquilombolas(P));
    printf("Numero de processos com comunidades indígenas: %d\n", getindigenas(P));
    printf("Numero de processos com crimes contra a infância: %d\n", getinfancia(P));

    printf("id do processo mais antigo: %d\n", getidprocessoMaisAntigo(P));
    printf("Numero de dias entre 2020-01-01 e 2021-01-01: %d\n", getdiasEntreDatas("2020-01-01", "2021-01-01"));
    printf("Percentual de cumprimento da Meta 1: %.2f%%\n", getcumprimentoMeta1(P));

    gerarCSVMeta1julgados(P, "processos_julgados_meta1.csv");

    free(P); 

    return 0;
}