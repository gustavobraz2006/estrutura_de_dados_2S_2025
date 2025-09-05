#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE*fp;
    fp = fopen("bd.txt", "r"); // read para leitura

    if (fp == NULL){
        printf("ERRO ao abrir arquivo\n");
        exit(1);
    }

    int conta;
    float saldo;
    char nome[50];

    for (int i = 0; i < 4; i++){
        fscanf(fp, "%d %f %[^\n]\n", &conta, &saldo, nome);
        printf("%d\t%.2f\t%s\n", conta, saldo, nome);
    }
    
    
    fclose(fp);
    return 0;
}