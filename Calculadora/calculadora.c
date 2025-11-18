#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "calculadora.h"

//Pilha para float que irá guardar os números durante o cálculo da expressão
typedef struct {
    float items[128];
    int top;
} PilhaFloat;


//Pilha para strings que irá guardar os operandos durante a conversão da expressão 
typedef struct {
    char items[128][128];
    int top;
} PilhaStr;

