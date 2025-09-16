#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 50000

void TrocarElemento(int * A, int * B);
int Particao(int * V, int Inf, int Sup);
void Quicksort(int * V, int Inf, int Sup);
void ExibirVetor(int * V, int N);
void InsertionSort(int * V, int N);

int main() {
    int Conjunto[TAMANHO];
    int Conjunto2[TAMANHO];

    srand(time(NULL));
    for(int i = 0; i < TAMANHO; i++) {
        Conjunto[i] = rand() % 1000;
        Conjunto2[i] = Conjunto[i];  // copiar para garantir mesmos dados nos dois vetores
    }

    clock_t T0 = clock();
    Quicksort(Conjunto, 0, TAMANHO - 1);
    clock_t TF = clock();
    printf("Tempo Quicksort: %f segundos\n", (double)(TF - T0) / CLOCKS_PER_SEC);

    T0 = clock();
    InsertionSort(Conjunto2, TAMANHO);
    TF = clock();
    printf("Tempo InsertionSort: %f segundos\n", (double)(TF - T0) / CLOCKS_PER_SEC);

    return 0;
}


void TrocarElemento(int * A, int * B){
    int temp = *A;
    *A = *B;
    *B = temp;
}

int Particao(int * V, int Inf, int Sup){
    int Pivot = V[(Inf + Sup) / 2];
    int i = Inf;
    int j = Sup;

    while (i <= j){
        while(V[i] < Pivot){
            i++;
        }
        while (V[j] > Pivot){
            j--;
        }
        if(i <= j){
            TrocarElemento(&V[i], &V[j]);
            i++;
            j--;
        }
    }
    return i;
}

void Quicksort(int * V, int Inf, int Sup){
    if(Inf < Sup){
        int P = Particao(V, Inf, Sup);
        Quicksort(V, Inf, P - 1);
        Quicksort(V, P, Sup);
    }
}

void ExibirVetor(int * V, int N){
    for(int i = 0; i < N; i++) printf("%d\t", V[i]);
    printf("\n");
}

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
}