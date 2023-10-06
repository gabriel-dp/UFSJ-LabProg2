#ifndef DEQUE_H
#define DEQUE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int qtd, ini, fim;
    int dados[MAX];
} Deque;

Deque* criaDeque() {
    Deque* dq;
    dq = (Deque*)malloc(sizeof(Deque));
    if (dq != NULL) {
        dq->qtd = dq->ini = dq->fim = 0;
    }
    return dq;
}

void destroiDeque(Deque** dq) {
    if (*dq != NULL) {
        free(*dq);
        *dq = NULL;
    }
}

int tamanhoDeque(Deque* dq) {
    if (dq == NULL)
        return -1;
    return dq->qtd;
}

int estaCheio(Deque* dq) {
    if (dq == NULL)
        return -1;
    return (dq->qtd == MAX);
}

int estaVazio(Deque* dq) {
    if (dq == NULL)
        return -1;
    return (dq->qtd == 0);
}

int insereInicio(Deque* dq, int elem) {
    if (dq == NULL) return 0;
    if (estaCheio(dq)) return 0;
    dq->ini = (dq->ini - 1 < 0 ? MAX - 1 : dq->ini - 1);
    dq->dados[dq->ini] = elem;
    dq->qtd++;
    return 1;
}

int insereFim(Deque* dq, int elem) {
    if (dq == NULL) return 0;
    if (estaCheio(dq)) return 0;
    dq->dados[dq->fim] = elem;
    dq->fim = (dq->fim + 1) % MAX;
    dq->qtd++;
    return 1;
}

int removeInicio(Deque* dq) {
    if (dq == NULL) return 0;
    if (estaVazio(dq)) return 0;
    dq->ini = (dq->ini + 1) % MAX;
    dq->qtd--;
    return 1;
}

int removeFim(Deque* dq) {
    if (dq == NULL) return 0;
    if (estaVazio(dq)) return 0;
    dq->fim = (dq->fim - 1 < 0 ? MAX - 1 : dq->fim - 1);
    dq->qtd--;
    return 1;
}

int verInicio(Deque* dq, int* p) {
    if (dq == NULL) return 0;
    if (estaVazio(dq)) return 0;
    *p = dq->dados[dq->ini];
    return 1;
}

int verFim(Deque* dq, int* p) {
    if (dq == NULL) return 0;
    if (estaVazio(dq)) return 0;
    int i = (dq->fim - 1 < 0 ? MAX - 1 : dq->fim - 1);
    *p = dq->dados[i];
    return 1;
}

void imprime(Deque* dq) {
    if (dq == NULL) return;
    if (estaVazio(dq)) {
        printf("Deque Vazio!\n");
        return;
    }
    int i = dq->ini;
    printf("Elementos: \n");
    do {
        printf("%d ", dq->dados[i]);
        i = (i + 1) % MAX;
    } while (i != dq->fim);
    // Usar do..while garante a impressao de todos elementos
    // mesmo com a Deque cheia
    printf("\n");
}

#endif