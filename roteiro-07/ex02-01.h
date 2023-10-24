#ifndef MATRIZFAIXA_H
#define MATRIZFAIXA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int* diagonal;
    int* superior;
    int* inferior;
    int tam;
} Matriz;

void zeraMatriz(Matriz* mf) {
    int i;
    for (i = 0; i < mf->tam; i++) {
        mf->diagonal[i] = 0;
        if (i < mf->tam - 1) {
            mf->superior[i] = 0;
            mf->inferior[i] = 0;
        }
    }
}

Matriz* criaMatriz(int t) {
    Matriz* mf;
    mf = (Matriz*)malloc(sizeof(Matriz));
    if (mf != NULL) {
        if (t <= 1) {
            printf("Dimensao deve ser > 1, matriz nao criada!");
            return NULL;
        }
        mf->tam = t;
        mf->diagonal = (int*)malloc(t * sizeof(int));
        mf->superior = (int*)malloc((t - 1) * sizeof(int));
        mf->inferior = (int*)malloc((t - 1) * sizeof(int));
        if (mf->diagonal == NULL || mf->superior == NULL || mf->inferior == NULL)
            return NULL;
        zeraMatriz(mf);
    }
    return mf;
}

void destroiMatriz(Matriz** mf) {
    if (*mf != NULL) {
        free((*mf)->diagonal);
        free((*mf)->superior);
        free((*mf)->inferior);
        free(*mf);
        *mf = NULL;
    }
}

int preencheAleatorio(Matriz* mf, int ini, int fim) {
    if (mf == NULL) return 0;
    srand(time(NULL));
    int i;
    for (i = 0; i < mf->tam; i++) {
        mf->diagonal[i] = ini + rand() % (fim - ini + 1);
        if (i < mf->tam - 1) {
            mf->superior[i] = ini + rand() % (fim - ini + 1);
            mf->inferior[i] = ini + rand() % (fim - ini + 1);
        }
    }
    return 1;
}

int insereElem(Matriz* mf, int elem, int i, int j) {
    if (mf == NULL) return 0;
    if (i < 0 || j < 0 || i >= mf->tam || j >= mf->tam) {
        printf("Valores invalidos, elem nao inserido!\n");
        return 0;
    }
    if (i == j)
        mf->diagonal[i] = elem;
    else if (i + 1 == j)
        mf->superior[i] = elem;
    else if (i == j + 1)
        mf->inferior[j] = elem;
    else {
        printf("Indices fora da faixa, elem nao inserido!\n");
        return 0;
    }
    return 1;
}

int consultaElem(Matriz* mf, int i, int j) {
    if (mf == NULL) return 0;
    if (i < 0 || j < 0 || i >= mf->tam || j >= mf->tam) {
        printf("Valores invalidos, elem inexistente!\n");
        return 0;
    }
    if (i == j)
        return mf->diagonal[i];
    else if (i + 1 == j)
        return mf->superior[i];
    else if (i == j + 1)
        return mf->inferior[j];
    else
        return 0;
}

void imprimeFaixaVetores(Matriz* mf) {
    if (mf == NULL) return;
    int i;
    printf("Matriz Faixa, Tam: %d x %d:\n", mf->tam, mf->tam);
    printf("Diagonal = [");
    for (i = 0; i < mf->tam; i++)
        printf("%d ", mf->diagonal[i]);
    printf("]\n");
    printf("Superior = [");
    for (i = 0; i < mf->tam - 1; i++)
        printf("%d ", mf->superior[i]);
    printf("]\n");
    printf("Inferior = [");
    for (i = 0; i < mf->tam - 1; i++)
        printf("%d ", mf->inferior[i]);
    printf("]\n\n");
}

void imprime(Matriz* mf) {
    if (mf == NULL) return;
    int i, j;
    imprimeFaixaVetores(mf);
    printf("Matriz Original:\n");
    for (i = 0; i < mf->tam; i++) {
        for (j = 0; j < mf->tam; j++)
            printf("%d\t", consultaElem(mf, i, j));
        printf("\n");
    }
}

#endif