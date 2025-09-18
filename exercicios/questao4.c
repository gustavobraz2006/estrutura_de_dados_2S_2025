#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char arquivo1[100];
    char arquivo2[100];
    char arquivoout[100];

    FILE *f1, *f2, *fsaida;
    int c;

    printf("Digite o nome do primeiro arquivo: \n");
    scanf("%s", arquivo1);

    printf("Digite o nome do segundo arquivo: \n");
    scanf("%s", arquivo2);

    printf("Digite o nome do arquivo de saida: \n");
    scanf("%s", arquivoout);

    f1 = fopen(arquivo1, "r");

    if (f1 == NULL){
        printf("Erro ao abrir arquivo.\n");
        exit(1);
    }

    f2 = fopen(arquivo2, "r");

    if (f2 == NULL){
        printf("Erro ao abrir arquivo.\n");
        fclose(f1);
        exit(1);
    }

    fsaida = fopen(arquivoout, "w");

     if (fsaida == NULL){
        printf("Erro ao abrir arquivo.\n");
        fclose(f1);
        fclose(f2);
        exit(1);
    
    while((c = fgetc(f1)) != EOF){
        fputc(c, fsaida);
    }

    while((c = fgetc(f2)) != EOF){
        fputc(c, fsaida);
    }   


    fclose(f1);
    fclose(f2);
    fclose(fsaida);

    printf("o conteudo dos arquivos foi devidamente colocado no terceiro arquivo.\n");

    return 0;
}