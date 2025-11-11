#ifndef PILHA_H
#define PILHA_H
typedef struct{
    int Chave;
    struct Item *Anterior;
} Item;

typedef struct {
    int tamanho;
    Item * Topo;
} Pilha;

Item * criarItem(int Chave);
Pilha * criarPilha();

void empilhar(Pilha * P, Item * I);
void desempilhar(Pilha * P);
#endif
