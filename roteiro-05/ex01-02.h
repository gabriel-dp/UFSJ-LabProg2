#ifndef FILA_ENCADEADA_H
#define FILA_ENCADEADA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int info;
    struct NO* prox;
} NO;

typedef struct {
    int qtd;
    struct NO *ini, *fim;
} Fila;

Fila* criaFila() {
    Fila* nova = (Fila*)malloc(sizeof(Fila));
    nova->qtd = 0;
    nova->ini = NULL;
    nova->fim = NULL;

    return nova;
}

void destroiFila(Fila** fi) {
    if (*fi != NULL) {
        free(*fi);
        *fi = NULL;
    }
}

NO* criaNo() {
    NO* novo = (NO*)malloc(sizeof(NO));
    novo->info = 0;
    novo->prox = NULL;

    return novo;
}

void destroiNo(NO* no) {
    free(no);
}

int tamanhoFila(Fila* fi) {
    if (fi == NULL) return 0;
    return fi->qtd;
}

int estaVazia(Fila* fi) {
    return (fi == NULL || fi->ini == NULL);
}

int enfileirar(Fila* fi, int elem) {
    if (fi == NULL) return 0;

    NO* novo = criaNo();
    novo->info = elem;

    if (estaVazia(fi)) {
        fi->ini = novo;
        fi->fim = novo;
    } else {
        fi->fim->prox = novo;
        fi->fim = novo;
    }
    fi->qtd++;

    return 1;
}

int desenfileirar(Fila* fi) {
    if (fi == NULL || estaVazia(fi)) return 0;

    NO* aux = fi->ini;
    fi->ini = fi->ini->prox;
    if (estaVazia(fi)) fi->fim = NULL;

    destroiNo(aux);
    fi->qtd--;

    return 1;
}

int verInicio(Fila* fi, int* p) {
    if (fi == NULL || estaVazia(fi)) return 0;

    *p = fi->ini->info;

    return 1;
}

void imprime(Fila* fi) {
    if (fi == NULL) return;
    if (estaVazia(fi)) {
        printf("Fila vazia");
        return;
    }

    printf("Elementos:\n");
    NO* i = fi->ini;
    do {
        printf("%d ", i->info);
        i = i->prox;
    } while (i != NULL);
    printf("\n");
}

#endif