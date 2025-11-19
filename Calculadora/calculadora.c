#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "calculadora.h"

// Limites gerais para as pilhas e strings
#define MAX_TOKENS 512
#define MAX_STACK 512
#define MAX_ITEM_STR 512

// Definição de PI caso a biblioteca não tenha
#define M_PI 3.14159265358979323846

// -----------------------------------------------
// PILHA PARA VALORES (float)
// usada na avaliação da expressão pós-fixa
// -----------------------------------------------
typedef struct {
    float itens[MAX_STACK];  // armazena os números
    int topo;                // topo da pilha
} PilhaValor;

// -----------------------------------------------
// PILHA PARA STRINGS
// usada na construção da expressão infixa
// -----------------------------------------------
typedef struct {
    char itens[MAX_STACK][MAX_ITEM_STR]; // expressões parciais
    int topo;
} PilhaStr;

// -----------------------------------------------
// Funções auxiliares da pilha de valores
// -----------------------------------------------
static void pv_inicia(PilhaValor *p){ p->topo = -1; }

static int pv_vazia(PilhaValor *p){ return p->topo == -1; }

static int pv_push(PilhaValor *p, float v){
    if(p->topo + 1 >= MAX_STACK) return 0; // overflow
    p->itens[++p->topo] = v;
    return 1;
}

static int pv_pop(PilhaValor *p, float *out){
    if(pv_vazia(p)) return 0; // underflow
    *out = p->itens[p->topo--];
    return 1;
}

// -----------------------------------------------
// Funções auxiliares da pilha de strings
// -----------------------------------------------
static void ps_inicia(PilhaStr *p){ p->topo = -1; }

static int ps_vazia(PilhaStr *p){ return p->topo == -1; }

static int ps_push(PilhaStr *p, const char *s){
    if(p->topo + 1 >= MAX_STACK) return 0;
    strncpy(p->itens[++p->topo], s, MAX_ITEM_STR - 1);
    p->itens[p->topo][MAX_ITEM_STR - 1] = '\0';
    return 1;
}

static int ps_pop(PilhaStr *p, char *out){
    if(ps_vazia(p)) return 0;
    strncpy(out, p->itens[p->topo--], MAX_ITEM_STR - 1);
    out[MAX_ITEM_STR-1] = '\0';
    return 1;
}

// -----------------------------------------------
// Reconhecedores de tokens
// -----------------------------------------------
static int e_numero(const char *s){
    if(!s || *s == '\0') return 0;
    char *end;
    strtod(s, &end);
    return (*end == '\0'); // termina em número
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

// Converte graus para radianos
static double graus_para_radianos(double g){
    return g * M_PI / 180.0;
}

// Remove espaços (por garantia)
static void remove_espacos(char *s){
    char *d = s;
    while(*s){
        if(*s != ' ') *d++ = *s;
        s++;
    }
    *d = '\0';
}

// -----------------------------------------------
// FUNÇÃO PÚBLICA 1: getValorPosFixa
// Avalia expressão pós-fixa
// -----------------------------------------------
float getValorPosFixa(char *StrPosFixa){
    if(StrPosFixa == NULL) return NAN;

    // Copiamos a string pois strtok altera
    char buf[strlen(StrPosFixa) + 1];
    strcpy(buf, StrPosFixa);

    PilhaValor pil;
    pv_inicia(&pil);

    // Lê token por token
    char *tok = strtok(buf, " ");
    while(tok != NULL){

        if(e_numero(tok)){
            // Token é número → empilha
            double v = strtod(tok, NULL);
            if(!pv_push(&pil, (float)v)) return NAN;
        }

        // função unária → pop 1 valor e calcula
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
            else { // log
                if(a <= 0) return NAN;
                r = log10(a);
            }

            pv_push(&pil, r);
        }

        // operador binário → pop dois valores
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

            pv_push(&pil, r);
        }

        else {
            // token inválido
            return NAN;
        }

        tok = strtok(NULL, " ");
    }

    // Ao final deve haver exatamente 1
    float resultado;
    if(!pv_pop(&pil, &resultado)) return NAN;
    if(!pv_vazia(&pil)) return NAN;

    return resultado;
}

// -----------------------------------------------
// FUNÇÃO PÚBLICA 2: getFormaInFixa
// Converte expressão pós-fixa → infixa
// -----------------------------------------------
char * getFormaInFixa(char *Str){
    if(Str == NULL) return NULL;

    char buf[strlen(Str) + 1];
    strcpy(buf, Str);

    PilhaStr pil;
    ps_inicia(&pil);

    char *tok = strtok(buf, " ");
    while(tok != NULL){

        if(e_numero(tok)){
            ps_push(&pil, tok);
        }

        else if(e_funcao_unaria(tok)){
            char op[MAX_ITEM_STR];
            if(!ps_pop(&pil, op)) return NULL;

            char nova[MAX_ITEM_STR];
            sprintf(nova, "%s(%s)", tok, op);

            ps_push(&pil, nova);
        }

        else if(e_operador_binario(tok)){
            char right[MAX_ITEM_STR], left[MAX_ITEM_STR];
            if(!ps_pop(&pil, right)) return NULL;
            if(!ps_pop(&pil, left)) return NULL;

            char nova[MAX_ITEM_STR];
            sprintf(nova, "(%s%s%s)", left, tok, right);

            ps_push(&pil, nova);
        }

        else return NULL;

        tok = strtok(NULL, " ");
    }

    if(pil.topo != 0) return NULL;

    char *res = malloc(strlen(pil.itens[pil.topo]) + 1);
    strcpy(res, pil.itens[pil.topo]);
    remove_espacos(res);

    return res;
}
