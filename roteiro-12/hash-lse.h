#ifndef HASH_LSE_H
#define HASH_LSE_H

#include <stdio.h>
#include <stdlib.h>

#include "lse.h"

typedef struct {
    Lista **tabela;
    int tam, qtd;
} Hash;

Hash *criaHash(int t) {
    Hash *h;
    h = (Hash *)malloc(sizeof(Hash));
    if (h != NULL) {
        h->tam = t;
        h->qtd = 0;
        h->tabela = (Lista **)malloc(t * sizeof(Lista *));
        if (h->tabela == NULL) return NULL;
        int i;
        for (i = 0; i < t; i++)
            h->tabela[i] = NULL;
    }
    return h;
}

void destroiHash(Hash *h) {
    if (h != NULL) {
        int i;
        for (i = 0; i < h->tam; i++)
            if (h->tabela[i] != NULL)
                destroiLista(h->tabela[i]);
        free(h->tabela);
        free(h);
    }
}

int chaveDivisao(int chave, int tam) {
    return (chave & 0x7FFFFFFF) % tam;
}

int insereHashLSE(Hash *h, int elem) {
    if (h == NULL) return 0;
    int pos = chaveDivisao(elem, h->tam);
    if (h->tabela[pos] == NULL)
        h->tabela[pos] = criaLista();
    insereIni(h->tabela[pos], elem);
    h->qtd++;
    return 1;
}

int buscaHashLSE(Hash *h, int elem, int *p) {
    if (h == NULL) return 0;
    int pos = chaveDivisao(elem, h->tam);
    if (h->tabela[pos] == NULL) return 0;
    return listaBuscaElem(h->tabela[pos], elem, p);
}

void imprimeHash(Hash *h) {
    if (h == NULL) return;
    int i;
    for (i = 0; i < h->tam; i++) {
        printf("%d: ", i);
        if (h->tabela[i] == NULL)
            printf("NULL\n");
        else
            imprimeLista(h->tabela[i]);
    }
}

#endif