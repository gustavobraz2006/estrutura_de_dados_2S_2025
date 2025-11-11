#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"


Item * criarItem(int Chave){
    Item * I = (Item *) malloc(sizeof(Item));
    if(I == NULL){
        printf("Erro: Nao foi possivel alocar memoria");
        return NULL;
    }

    I ->Chave = Chave;
    I ->Anterior = NULL;

    return I;
}

Pilha * criarPilha(){

    Pilha * P = (Pilha *) malloc(sizeof(Pilha));
    if(P == NULL){
        printf("Erro: Nao foi possivel alocar memoria");
        return NULL;
    }

    P ->tamanho = 0;
    P ->Topo = NULL;

    return P;

}

void empilhar(Pilha * P, Item * I){

    I->Anterior = P->Topo;
    P->Topo = I;
    P->tamanho++;
    
}

void desempilhar(Pilha * P){

    if(P ->tamanho == 0){
        printf("ERRO: a pilha está vazia!\n");
        return;
    }

    Item * I = P->Topo;
    P->Topo = I->Anterior;
    free(I);
    P->tamanho--;
}