#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE * fp;  //fp é um ponteiro para arquivo
    fp = fopen("texte.txt", "w"); //abre o texte.txt para escrita e apaga todo o conteúdo dentro 

    if(fp == NULL){
        printf("ERRO ao abrir arquivo\n");
        exit(1);
    }

    printf("Arquivo aberto/criado!\n");

    fclose(fp);
    return 0;
}