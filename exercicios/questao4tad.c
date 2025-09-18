#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
typedef struct{
    
    char Nome[MAX_NOME];
    int Idade;
    double Salario;

} Funcionario;

typedef struct{
    Funcionario *dados;
    int tamanho;
    int capacidade;

} Folha;


Funcionario * CriarFuncionario(int idade, const char* nome, double Salario);
float CalcularFGTS(Funcionario * F);
void LiberarFuncionario(Funcionario * F);


int main(){

    Funcionario * F1 = CriarFuncionario(30,"Roberto", 2500.00);
    Funcionario * F2 = CriarFuncionario(45, "Juliana", 3000.50);

    printf("Funcionario: %s com %d anos\n", F1->Nome, F1->Idade);
    printf("Salario: %.2fR$\n", F1->Salario);
    printf("FGTS: %.2f\n", CalcularFGTS(F1));

    LiberarFuncionario(F1);

    printf("Funcionario: %s com %d anos\n", F2->Nome, F2->Idade);
    printf("Salario: %.2fR$\n", F2->Salario);
    printf("FGTS: %.2f\n", CalcularFGTS(F2));

    LiberarFuncionario(F2);

    return 0;
}

Funcionario * CriarFuncionario(int idade, const char nome [MAX_NOME], double Salario){

    Funcionario* F = (Funcionario*)malloc(sizeof(Funcionario));
    if (!F) return NULL;
    F -> Idade = idade;
    strncpy(F -> Nome, nome, MAX_NOME - 1);
    F ->Nome[MAX_NOME - 1] = '\0';
    F ->Salario = Salario;

    return F;
}


float CalcularFGTS(Funcionario * F){
    if (!F) return 0.0;
    return F->Salario * 0.08; // aliquota 8%
}

void LiberarFuncionario(Funcionario * F){
    if (F) free(F);
}
