#ifndef EQUIPE_H
#define EQUIPE_H

typedef struct{
    
    int Pos; //Posição final da equipe CB2024
    char Estado[35];
    char Equipe[50]; //Nome do time
    int Pts;
    int J;
    int V;
    int E;
    int D;
    int GP; // Gols pró
    int GC; // Gols sofridos
    int SG; // Saldo de gols 
    float aproveitamento;
} Time;

Time * LerDados(char* Arquivo);

#endif