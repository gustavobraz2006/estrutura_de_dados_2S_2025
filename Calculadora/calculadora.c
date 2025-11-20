#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calculadora.h"

// Definições gerais para limites das pilhas
#define MAX_STACK 512
#define MAX_ITEM_STR 512

// Definição de PI, caso não esteja disponível
#define M_PI 3.14159265358979323846


// pilha para float
// Esta pilha é usada para avaliar expressões pósfixas.

typedef struct {
    float itens[MAX_STACK];
    int topo;
} PilhaValor;

// Inicializa a pilha
static void pv_inicia(PilhaValor *p){ p->topo = -1; }

// Verifica se a pilha está vazia
static int pv_vazia(PilhaValor *p){ return p->topo == -1; }

// Empilha um valor
static int pv_push(PilhaValor *p, float v){
    if(p->topo + 1 >= MAX_STACK) return 0;
    p->itens[++p->topo] = v;
    return 1;
}

// Desempilha um valor
static int pv_pop(PilhaValor *p, float *out){
    if(pv_vazia(p)) return 0; 
    *out = p->itens[p->topo--];
    return 1;
}


// pilha para strings
// Esta pilha monta a expressão infixa passo a passo.


typedef struct {
    char itens[MAX_STACK][MAX_ITEM_STR];
    int topo;
} PilhaStr;

static void ps_inicia(PilhaStr *p){ p->topo = -1; }
static int ps_vazia(PilhaStr *p){ return p->topo == -1; }

static int ps_push(PilhaStr *p, const char *s){
    if(p->topo + 1 >= MAX_STACK) return 0;
    strncpy(p->itens[++p->topo], s, MAX_ITEM_STR - 1);
    p->itens[p->topo][MAX_ITEM_STR-1] = '\0';
    return 1;
}

static int ps_pop(PilhaStr *p, char *out){
    if(ps_vazia(p)) return 0;
    strncpy(out, p->itens[p->topo--], MAX_ITEM_STR-1);
    out[MAX_ITEM_STR-1] = '\0';
    return 1;
}


// funções reconhecedoras 
// Estas funções apenas identificam cada item na pilha da expressão:
// número, operador binário ou função unária.

static int e_numero(const char *s){
    if(!s || *s == '\0') return 0;
    char *end;
    strtod(s, &end);
    return (*end == '\0'); 
}

static int e_operador_binario(const char *s){
    return (strcmp(s,"+")==0 || strcmp(s,"-")==0 ||
            strcmp(s,"*")==0 || strcmp(s,"/")==0 ||
            strcmp(s,"%")==0 || strcmp(s,"^")==0);
}

static int e_funcao_unaria(const char *s){
    return (strcmp(s,"raiz")==0 || strcmp(s,"sen")==0 ||
            strcmp(s,"cos")==0  || strcmp(s,"tg")==0  ||
            strcmp(s,"log")==0);
}

// Conversão de graus para radianos --> muito necessária para seno/cosseno/tg
static double graus_para_radianos(double g){
    return g * M_PI / 180.0;
}


// função que remove parênteses externos desnecessários

static void tira_parenteses_externos(char *s){
    int len = strlen(s);

    while (len > 2 && s[0] == '(' && s[len - 1] == ')'){
        int nivel = 0;
        int valido = 1;

        for(int i = 0; i < len - 1; i++){
            if(s[i] == '(') nivel++;
            if(s[i] == ')') nivel--;
            if(nivel == 0 && i < len - 2){
                valido = 0;
                break;
            }
        }

        if(!valido) break;

        memmove(s, s+1, len - 2);
        s[len - 2] = '\0';
        len -= 2;
    }
}


// Esta função avalia uma expressão pós-fixa utilizando pilha.


float getValorPosFixa(char *StrPosFixa){
    if(StrPosFixa == NULL) return NAN;

    char buf[strlen(StrPosFixa) + 1];
    strcpy(buf, StrPosFixa);

    PilhaValor pil;
    pv_inicia(&pil);

    char *tok = strtok(buf, " ");
    while(tok){

        // se for numero , é empilhado certinho
        if(e_numero(tok)){
            double v = strtod(tok, NULL);
            if(!pv_push(&pil, (float)v)) return NAN;
        }

        // processando funções unarias
        else if(e_funcao_unaria(tok)){
            float a;
            if(!pv_pop(&pil, &a)) return NAN;
            double r;

            if(strcmp(tok,"raiz")==0){
                if(a < 0) return NAN;
                r = sqrt(a);
            }
            else if(strcmp(tok,"sen")==0) r = sin(graus_para_radianos(a));
            else if(strcmp(tok,"cos")==0) r = cos(graus_para_radianos(a));
            else if(strcmp(tok,"tg")==0)  r = tan(graus_para_radianos(a));
            else {
                if(a <= 0) return NAN;
                r = log10(a);
            }

            pv_push(&pil, (float)r);
        }

        // processando operadores
        else if(e_operador_binario(tok)){
            float b,a;
            if(!pv_pop(&pil, &b)) return NAN;
            if(!pv_pop(&pil, &a)) return NAN;

            double r = 0;

            if(strcmp(tok,"+")==0) r = a + b;
            else if(strcmp(tok,"-")==0) r = a - b;
            else if(strcmp(tok,"*")==0) r = a * b;
            else if(strcmp(tok,"/")==0){
                if(b == 0) return NAN;
                r = a / b;
            }
            else if(strcmp(tok,"%")==0){
                if(b == 0) return NAN;
                r = fmod(a, b);
            }
            else if(strcmp(tok,"^")==0) r = pow(a, b);

            pv_push(&pil, (float)r);
        }

        // caso item não seja válido = ERRO
        else return NAN;

        tok = strtok(NULL, " ");
    }

    float res;
    if(!pv_pop(&pil, &res)) return NAN;
    if(!pv_vazia(&pil)) return NAN;

    return res;
}


//getFormaInFixa – pós-fixa → infixa



char * getFormaInFixa(char *Str){
    if(Str == NULL) return NULL;

    char buf[strlen(Str) + 1];
    strcpy(buf, Str);

    PilhaStr pil;
    ps_inicia(&pil);

    char *tok = strtok(buf, " ");
    while(tok){

        // Número → empilha diretamente
        if(e_numero(tok)){
            if(!ps_push(&pil, tok)) return NULL;
        }

        // Função unária → pop um operando e monta func(op)
        else if(e_funcao_unaria(tok)){
            char op[MAX_ITEM_STR];
            if(!ps_pop(&pil, op)) return NULL;

            char nova[MAX_ITEM_STR];
            snprintf(nova, sizeof(nova), "%s(%s)", tok, op);

            if(!ps_push(&pil, nova)) return NULL;
        }

        // Operador binário → pop dois operandos e monta 
        else if(e_operador_binario(tok)){
            char dir[MAX_ITEM_STR], esq[MAX_ITEM_STR];
            if(!ps_pop(&pil, dir)) return NULL;
            if(!ps_pop(&pil, esq)) return NULL;

            char nova[MAX_ITEM_STR];
            snprintf(nova, sizeof(nova), "(%s%s%s)", esq, tok, dir);

            if(!ps_push(&pil, nova)) return NULL;
        }

        else return NULL;

        tok = strtok(NULL, " ");
    }

    if(pil.topo != 0) return NULL;

    char *res = malloc(strlen(pil.itens[pil.topo]) + 1);
    strcpy(res, pil.itens[pil.topo]);

    tira_parenteses_externos(res);

    return res;
}
