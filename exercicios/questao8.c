#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void NomesAprovados(FILE *f1);

int main(){

    FILE *f1;

    f1 = fopen("alunos.csv", "r");

    if (f1 == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    NomesAprovados(f1);

    fclose(f1);

    return 0;
}

void NomesAprovados(FILE *f1){

    char nome[100];
    float nota1;
    float nota2;
    float media;
    
    while(fscanf(f1, " %99[^,],%f,%f", nome, &nota1, &nota2) == 3){

        media = (nota1 + nota2)/2;

        if (media >= 7){
            printf("o(a) aluno(a) %s passou com %.2f de media\n", nome, media);              
        }

        else {
            printf("o(a) aluno(a) %s nao passou e ficou com %.2f de media\n", nome, media);              
        }
    }
}
