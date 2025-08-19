#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE * fp;  //fp é um ponteiro para arquivo
    fp = fopen("texte.txt", "a"); //abre o texte.txt para escrita e sobressai todo o conteúdo dentro 

    if(fp == NULL){
        printf("ERRO ao abrir arquivo\n");
        exit(1);
    }

    fprintf(fp, "O Santos perdeu de 6 x 0!\n\n");

    printf("Arquivo aberto/criado!\n");

    fclose(fp);
    return 0;
}