#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tarefa.h"

int main(){
    
    Tarefa T1 = {"Preparar relatorio da disciplina RT", "Ana Maria", EM_ANDAMENTO, 0.75, 5};
    Tarefa T2 = {"Entrega do relatório de BD", "Rafael Souza", FEITO, 1.00, 4};
    Tarefa T3 = {"Revisão do código do sistema", "Carlos Henrique", FEITO, 1.00, 5};
    Tarefa T4 = {"Criação de mockups para o app", "Juliana Ribeiro", EM_ANDAMENTO, 0.40, 3};
    Tarefa T5 = {"Levantamento de requisitos", "Rafael Souza", A_FAZER, 0.00, 2};
    Tarefa T6 = {"Treinamento da equipe", "Fernanda Lima", EM_ANDAMENTO, 0.60, 4};
    Tarefa T7 = {"Testes automatizados", "Lucas Martins", A_FAZER, 0.00, 5};
    Tarefa T8 = {"Atualização da documentação técnica", "Mariana Alves", A_FAZER, 0.00, 3};
    Tarefa T9 = {"Integração com API externa", "Pedro Rocha", EM_ANDAMENTO, 0.50, 4};
    Tarefa T10 = {"Apresentação para o cliente", "Bianca Torres", FEITO, 1.00, 5};
    Tarefa T11 = {"Correção de bugs críticos", "João Victor", EM_ANDAMENTO, 0.30, 5};

    Lista * Planner = CriarLista(200);

    AdicionarTarefa(Planner, T1);
    AdicionarTarefa(Planner, T2);
    AdicionarTarefa(Planner, T3);
    AdicionarTarefa(Planner, T4);
    AdicionarTarefa(Planner, T5);
    AdicionarTarefa(Planner, T6);
    AdicionarTarefa(Planner, T7);
    AdicionarTarefa(Planner, T8);
    AdicionarTarefa(Planner, T9);
    AdicionarTarefa(Planner, T10);
    AdicionarTarefa(Planner, T11);

    for(int i = 0; i < Planner->Tamanho; i++){
        printf("%d\t", i);
        printf("%s\n", Planner->Dados[i].Titulo);
    }

    printf("%X\n", Planner);

    return 0;
}