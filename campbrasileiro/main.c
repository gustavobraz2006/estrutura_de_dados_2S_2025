#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipe.h"

int main(){

    Time * Tabela = LerDados("tabela.csv");
    for(int i = 0; i < 20; i++)
        printf("%d\t%.2f%%\t%s\n", Tabela[i].Pos, Tabela[i].aproveitamento, Tabela[i].Equipe);



    return 0;
}