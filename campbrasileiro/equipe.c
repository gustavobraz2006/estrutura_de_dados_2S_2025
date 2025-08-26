#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipe.h"

Time * LerDados(char* Arquivo){

    printf("Arquivo a ser aberto: %s\n", Arquivo);
    Time *X = malloc(20 * sizeof(Time));
    if(X == NULL){
        printf("ERRO: memória insuficiente!\n");
        exit(1);
    }

    FILE * fp = fopen(Arquivo, "r");
    if(fp == NULL){
        printf("ERRO: Arquivo não pode ser aberto!\n");
        exit(1);
    }

    int i = 0;

    char cabecalho[100];
    fscanf(fp, "%s", cabecalho);

    //;D;gp;gc;sg

    while(
        fscanf(
            fp,
            "%d;%[^;];%[^;];%d;%d;%d;%d;%d;%d;%d;%d",
            &X[i].Pos, X[i].Estado, X[i].Equipe, &X[i].Pts, &X[i].J, &X[i].V, &X[i].E, &X[i].D, &X[i].GP, &X[i].GC, &X[i].SG
        ) == 11) {
            X[i].aproveitamento = (float) 100 * X[i].Pts / (3 * X[i].J);
            //printf("%s - aproveitamento: %.2f%%\n", X[i].Equipe, X[i].aproveitamento);
            i++;
        }
    
    
    fclose(fp);
    return X;
}