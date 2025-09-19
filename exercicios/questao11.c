#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ParticionamentoCSV(FILE * F);

int main(){

    FILE * Fp;
    Fp = fopen("transacoes.csv", "r");

    if(Fp == NULL){
        printf("Erro ao abrir arquivo de transacoes.\n");
        exit(1);
    }

    ParticionamentoCSV(Fp);

    fclose(Fp);
    
    return 0;
}


void ParticionamentoCSV(FILE * F){
    
    char linha[100];
    int ID;
    char Operacao[20];
    double Valor;
    
    
    FILE * Vendas;
    Vendas = fopen("vendas.csv", "w");
    FILE * Compras;
    Compras = fopen("compras.csv", "w");

    if (!Vendas || !Compras){
        printf("Erro ao criar arquivos de saida.\n");
        return;
    }

    fprintf(Vendas, "ID,Operacao,Valor\n");
    fprintf(Compras, "ID,Operacao,Valor\n");

    fgets(linha, sizeof(linha), F);

    while (fgets(linha, sizeof(linha), F)){
        if(sscanf(linha, "%d, %19[^,],%lf", &ID, Operacao, &Valor) == 3){

            if(strcmp(Operacao,"Venda") == 0){
                fprintf(Vendas,"%d,%s,%.2f\n", ID, Operacao, Valor);
            }    

            else if(strcmp(Operacao,"Compra") == 0){
                fprintf(Compras,"%d,%s,%.2f\n", ID, Operacao, Valor);
            }    
        }      
    }

    fclose(Vendas);
    fclose(Compras);
}