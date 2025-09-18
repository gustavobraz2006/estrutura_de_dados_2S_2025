#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    
    int id;
    char Nome[15];
    char Email[40];
    
} Cliente;

Cliente * LerarquivoCSV(FILE * F, int *qtd);
void ListarClientes(Cliente * clientes, int qtd);
void RemoverCliente(Cliente * clientes, int *qtd, int IDremove);
void SalvarCSV(const char *filename, Cliente * clientes, int qtd);
int main(){
    
    FILE * Fp;
    Fp = fopen("clientes.csv", "r");

    if (Fp == NULL){ 
        printf("ERRO ao abrir arquivo.\n");
        exit(1);
    }

    int qtdClientes = 0;
    Cliente * clientes = LerarquivoCSV(Fp, &qtdClientes);

    fclose(Fp);


    ListarClientes(clientes, qtdClientes);


    int IDremove;
    printf("Voce deseja remover algum cliente? caso sim digite seu ID: ");
    scanf("%d", &IDremove);

    RemoverCliente(clientes, &qtdClientes, IDremove);

    printf("\nLista apos remocao:\n");
    ListarClientes(clientes, qtdClientes);


    SalvarCSV("clientes.csv", clientes, qtdClientes);

    free(clientes);

    return 0;
}

Cliente * LerarquivoCSV(FILE *F, int *qtd) {
    Cliente *clientes = NULL;
    Cliente temp;
    char linha[100];
    int capacidade = 0;

    // Pular cabeçalho
    fgets(linha, sizeof(linha), F);

    while (fgets(linha, sizeof(linha), F)) {
        if (sscanf(linha, "%d,%14[^,],%39[^\n]", &temp.id, temp.Nome, temp.Email) == 3) {
            
            // Aumentar vetor se necessário
            if (*qtd >= capacidade) {
                capacidade = capacidade == 0 ? 2 : capacidade * 2;
                clientes = realloc(clientes, capacidade * sizeof(Cliente));
                if (!clientes) {
                    printf("Erro de memória!\n");
                    exit(1);
                }
            }

            // Copiar cliente temporário para vetor
            clientes[*qtd] = temp;
            (*qtd)++;
        }
    }

    return clientes;
}

void ListarClientes(Cliente * clientes, int qtd){
    for (int i = 0; i < qtd; i++) {
        printf("ID: %d\t Nome: %s\t Email: %s\n", 
               clientes[i].id, clientes[i].Nome, clientes[i].Email);
    }
}

void RemoverCliente(Cliente * clientes, int *qtd, int IDremove){

    int encontrado = 0;
    for(int i = 0; i < *qtd; i++){
        if(clientes[i].id == IDremove){
            encontrado = 1;

            for(int j = i; j < *qtd - 1; j++){
                clientes[j] = clientes[j + 1];
            }
            (*qtd)--;
            break;
        }
    }

    if(!encontrado){
            printf("Cliente com ID nao encontrado.");
        }
}

void SalvarCSV(const char *filename, Cliente * clientes, int qtd){

    FILE * F = fopen(filename, "w");

    if(!F){
        printf("Erro ao abrir arquivo para salvar.\n");
        return;
    }

    fprintf(F, "ID,Nome,Email\n");

    for (int i = 0; i < qtd; i++)
    {
        fprintf(F,"%d,%s,%s\n", clientes[i].id, clientes[i].Nome, clientes[i].Email);
    }
    
    fclose(F);
}