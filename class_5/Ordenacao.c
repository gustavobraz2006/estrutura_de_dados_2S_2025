#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 100000

// Protótipos

void InsertionSort(int * V, int N);
void ExibirVetor(int * V, int N);

// função principal

int main(){

    int Conjunto[TAMANHO];
    srand(time(NULL));
    for(int i = 0; i < TAMANHO; i++) Conjunto[i] = rand() % 1000;

    clock_t T0 = clock();
    InsertionSort(Conjunto, TAMANHO);
    clock_t TF = clock();

    printf("Tempo de CPU: %f\n", (double)(TF - T0) / CLOCKS_PER_SEC);

}

//implementação das funções

void InsertionSort(int * V, int N){
    
    int chave; //Elemento que será inserido na parte ordenada 
    int i; //Posição(ou coordenada) do elemento chave
    int j; //Posição de elemento da "parte ordenada" que será comparada com Chave

    for(i = 1; i < N; i++){
        chave = V[i];
        j = i - 1;

        while(j >= 0 && V[j] > chave){
            V[j + 1] = V[j];
            j--;
        }
        
        V[j + 1] =  chave; // copiando a chave no último lugar modificado 
    }
    ExibirVetor(V, N);
}

void ExibirVetor(int * V, int N){

    int i;
    for(i = 0; i < N; i++){
    printf("%d\t", V[i]);
    }
}

