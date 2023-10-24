#ifndef MATRIZDIN_H
#define MATRIZDIN_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int** dados;
    int lin, col;
} Matriz;

void zeraMatriz(Matriz* mat) {
    if (mat == NULL) return;

    int i, j;
    for (i = 0; i < mat->lin; i++)
        for (j = 0; j < mat->col; j++)
            mat->dados[i][j] = 0;
}

Matriz* criaMatriz(int l, int c) {
    Matriz* mat;
    mat = (Matriz*)malloc(sizeof(Matriz));
    if (mat != NULL) {
        if (l <= 0 || c <= 0) {
            printf("Valores invalidos, matriz nao criada!\n");
            return NULL;
        }
        int i;
        mat->lin = l;
        mat->col = c;
        mat->dados = (int**)malloc(l * sizeof(int*));
        for (i = 0; i < l; i++)
            mat->dados[i] = (int*)malloc(c * sizeof(int));
        zeraMatriz(mat);
    }
    return mat;
}

void destroiMatriz(Matriz** mat) {
    if (*mat != NULL) {
        int i;
        for (i = 0; i < (*mat)->lin; i++)
            free((*mat)->dados[i]);
        free((*mat)->dados);
        free(*mat);
        *mat = NULL;
    }
}

int preencheAleatorio(Matriz* mat, int ini, int fim) {
    if (mat == NULL) return 0;
    srand(time(NULL));
    int i, j;
    for (i = 0; i < mat->lin; i++)
        for (j = 0; j < mat->col; j++)
            mat->dados[i][j] = ini + rand() % (fim - ini + 1);
    return 1;
}

int insereElem(Matriz* mat, int elem, int l, int c) {
    if (mat == NULL) return 0;
    if (l < 0 || c < 0 || l > mat->lin || c > mat->col) {
        printf("Valores invalidos, elem nao inserido!\n");
        return 0;
    }
    mat->dados[l][c] = elem;
    return 1;
}

int consultaElem(Matriz* mat, int* p, int l, int c) {
    if (mat == NULL) return 0;
    if (l < 0 || c < 0 || l > mat->lin || c > mat->col) {
        printf("Valores invalidos, elem nao existe!\n");
        return 0;
    }
    *p = mat->dados[l][c];
    return 1;
}

void imprime(Matriz* mat) {
    if (mat == NULL) return;
    int i, j;
    printf("Matriz %d x %d:\n", mat->lin, mat->col);
    for (i = 0; i < mat->lin; i++) {
        for (j = 0; j < mat->col; j++)
            printf("%d ", mat->dados[i][j]);
        printf("\n");
    }
    printf("\n");
}

#endif