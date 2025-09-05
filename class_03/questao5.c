#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE*fp;
    fp = fopen("compras.txt", "r"); // read para leitura

    if (fp == NULL){
        printf("ERRO ao abrir arquivo\n");
        exit(1);
    }

    char nome[50];
    int quantidade;
    float preco;

    while (fscanf(fp, "%s %d %f", nome, &quantidade, &preco) == 3){

        fscanf(fp, "%[^\n] %d %f\n", nome, &quantidade, &preco);
        printf("%s\t%.d\t%.2f\n", nome, quantidade, preco);
    }

    

    fclose(fp);
    return 0;
}