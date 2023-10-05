#ifndef PILHA_SEQUENCIAL_H
#define PILHA_SEQUENCIAL_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int topo;
    int dados[MAX];
} Pilha;

Pilha* criaPilha() {
    Pilha* pi;
    pi = (Pilha*)malloc(sizeof(Pilha));
    if (pi != NULL) {
        pi->topo = 0;
    }
    return pi;
}

void destroiPilha(Pilha** pi) {
    if (*pi != NULL) {
        free(*pi);
        *pi = NULL;
    }
}

int tamanhoPilha(Pilha* pi) {
    if (pi == NULL)
        return -1;
    return pi->topo;
}

int estaCheia(Pilha* pi) {
    if (pi == NULL)
        return -1;
    return (pi->topo == MAX);
}

int estaVazia(Pilha* pi) {
    if (pi == NULL)
        return -1;
    return (pi->topo == 0);
}

int empilhar(Pilha* pi, int elem) {
    if (pi == NULL) return 0;
    if (estaCheia(pi)) return 0;
    pi->dados[pi->topo] = elem;
    pi->topo++;
    return 1;
}

int desempilhar(Pilha* pi) {
    if (pi == NULL) return 0;
    if (estaVazia(pi)) return 0;
    pi->topo--;
    return 1;
}

int verTopo(Pilha* pi, int* p) {
    if (pi == NULL) return 0;
    if (estaVazia(pi)) return 0;
    *p = pi->dados[pi->topo - 1];
    return 1;
}

void imprime(Pilha* pi) {
    if (pi == NULL) return;
    if (estaVazia(pi)) {
        printf("Pilha Vazia!\n");
        return;
    }
    printf("Elementos: \n");
    int i;
    for (i = pi->topo - 1; i >= 0; i--)
        printf("%d ", pi->dados[i]);
    printf("\n");
}

#endif