#ifndef PILHA_ENCADEADA_H
#define PILHA_ENCADEADA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int info;
    struct NO* prox;
} NO;

typedef struct {
    int qtd;
    struct NO* topo;
} Pilha;

Pilha* criaPilha() {
    Pilha* pi = (Pilha*)malloc(sizeof(Pilha));
    pi->topo = NULL;
    pi->qtd = 0;

    return pi;
}

void destroiPilha(Pilha** pi) {
    if (*pi != NULL) {
        free(*pi);
        *pi = NULL;
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

int tamanhoPilha(Pilha* pi) {
    if (pi == NULL)
        return 0;
    return pi->qtd;
}

int estaVazia(Pilha* pi) {
    return (pi == NULL || pi->topo == NULL);
}

int empilhar(Pilha* pi, int elem) {
    if (pi == NULL) return 0;

    NO* novo = criaNo();
    novo->info = elem;
    novo->prox = pi->topo;
    pi->topo = novo;
    pi->qtd++;

    return 1;
}

int desempilhar(Pilha* pi) {
    if (pi == NULL || estaVazia(pi)) return 0;

    NO* aux = pi->topo;
    pi->topo = pi->topo->prox;

    destroiNo(aux);
    pi->qtd--;

    return 1;
}

int verTopo(Pilha* pi, int* p) {
    if (pi == NULL || estaVazia(pi)) return 0;

    *p = pi->topo->info;

    return 1;
}

void imprime(Pilha* pi) {
    if (pi == NULL) return;
    if (estaVazia(pi)) {
        printf("Pilha Vazia!\n");
        return;
    }

    printf("Elementos: \n");
    NO* i = pi->topo;
    do {
        printf("%d ", i->info);
        i = i->prox;
    } while (i != NULL);
    printf("\n");
}

#endif