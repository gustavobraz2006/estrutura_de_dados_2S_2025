#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int SomaArquivo(FILE *f1);

int main() {
    FILE *f1;

    f1 = fopen("venda.csv", "r");

    if (f1 == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    SomaArquivo(f1);

    fclose(f1);
    return 0;
}

int SomaArquivo(FILE *f1) {
    char produto[50];
    int quantidade;
    float preco;
    int somaquantidade = 0;

    while (fscanf(f1, "%49[^,],%d,%f", produto, &quantidade, &preco) == 3) {
        somaquantidade += quantidade;
    }

    printf("A quantidade de produtos comprados foi %d\n", somaquantidade);

    return somaquantidade;
}