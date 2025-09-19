#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AtualizarProduto(const char * nomeArquivo, const char * getProduto, int novaQuantidade, double novoPreco);

int main(){

    AtualizarProduto("produtos.csv","Teclado",23000,283888.90);

    return 0;
}

void AtualizarProduto(const char * nomeArquivo, const char * getProduto, int novaQuantidade, double novoPreco){

    FILE *F = fopen(nomeArquivo, "r");
    if (F == NULL) {
        printf("ERRO ao abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }

    FILE *Temp = fopen("temp.csv", "w");
    if (Temp == NULL) {
        printf("ERRO ao criar arquivo temporário.\n");
        fclose(F);
        exit(1);
    }


    char Produto[20];
    int Quantidade;
    double Preco;
    char linha[100];

    if (fgets(linha, sizeof(linha), F)) {
        fputs(linha, Temp);
    }

    while (fgets(linha,sizeof(linha), F)){
        if(sscanf(linha,"%19[^,],%d,%lf", Produto, &Quantidade, &Preco) == 3){
            if(strcmp(Produto, getProduto) == 0){  
                fprintf(Temp,"%s,%d,%.2f\n", Produto, novaQuantidade, novoPreco);
            }

            else {
                fprintf(Temp, "%s,%d,%.2f\n", Produto, Quantidade, Preco);
            }
        }
    }

    fclose(F);
    fclose(Temp);

    remove(nomeArquivo);
    rename("temp.csv", nomeArquivo);
}