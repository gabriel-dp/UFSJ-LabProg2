#ifndef FILA_SEQUENCIAL_H
#define FILA_SEQUENCIAL_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int qtd, ini, fim;
    int dados[MAX];
} Fila;

Fila* criaFila() {
    Fila* fi;
    fi = (Fila*)malloc(sizeof(Fila));
    if (fi != NULL) {
        fi->qtd = fi->ini = fi->fim = 0;
    }
    return fi;
}

void destroiFila(Fila** fi) {
    if (*fi != NULL)
        free(*fi);
    *fi = NULL;
}

int tamanhoFila(Fila* fi) {
    if (fi == NULL)
        return -1;
    return fi->qtd;
}

int estaCheia(Fila* fi) {
    if (fi == NULL)
        return -1;
    return (fi->qtd == MAX);
}

int estaVazia(Fila* fi) {
    if (fi == NULL)
        return -1;
    return (fi->qtd == 0);
}

int enfileirar(Fila* fi, int elem) {
    if (fi == NULL) return 0;
    if (estaCheia(fi)) return 0;
    fi->dados[fi->fim] = elem;
    fi->fim = (fi->fim + 1) % MAX;
    fi->qtd++;
    return 1;
}

int desenfileirar(Fila* fi) {
    if (fi == NULL) return 0;
    if (estaVazia(fi)) return 0;
    fi->ini = (fi->ini + 1) % MAX;
    fi->qtd--;
    return 1;
}

int verInicio(Fila* fi, int* p) {
    if (fi == NULL) return 0;
    if (estaVazia(fi)) return 0;
    *p = fi->dados[fi->ini];
    return 1;
}

void imprime(Fila* fi) {
    if (fi == NULL) return;
    if (estaVazia(fi)) {
        printf("Fila Vazia!\n");
        return;
    }
    int i = fi->ini;
    printf("Elementos: \n");
    do {
        printf("%d ", fi->dados[i]);
        i = (i + 1) % MAX;
    } while (i != fi->fim);
    printf("\n");
}

#endif