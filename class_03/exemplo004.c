#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp;  //fp é um ponteiro para arquivo
    fp = fopen("tabuada.txt", "a"); //abre o texte.txt para escrita e sobressai todo o conteúdo dentro 

    if(fp == NULL){
        printf("ERRO ao abrir arquivo\n");
        exit(1);
    }

    int resultado7;
    int inteiro7 = 7;

    fprintf(fp,"tabuada do 7\n");

    for(int i = 0; i < 11; i++){
         resultado7 = inteiro7 * i;
        fprintf(fp, "O resultado de 7 x %d eh: %d\n", i , resultado7);         
    }

    int resultado9;
    int inteiro9 = 9;

    fprintf(fp,"tabuada do 9\n\n");

    for(int i = 0; i < 11; i++){
         resultado9 = inteiro9 * i;
        fprintf(fp, "O resultado de 9 x %d eh: %d\n", i , resultado9);         
    }

    

    printf("Arquivo aberto/criado!\n");

    fclose(fp);
    return 0;
}