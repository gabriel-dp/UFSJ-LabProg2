#ifndef MESPARSACSR_H
#define MESPARSACSR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int* A;  // Valores
    int* IA;
    int* JA;
    int lin, col, QNN, QI;
} MEsparsaCSR;
// QNN - Quantidade de Nao Nulos
// QI - Quantidade de Inseridos

MEsparsaCSR* criaMatrizEsparsa(int l, int c, int qnn) {
    MEsparsaCSR* ms;
    ms = (MEsparsaCSR*)malloc(sizeof(MEsparsaCSR));
    if (ms != NULL) {
        if (l <= 0 || c <= 0 || qnn < 0) {
            printf("Valores invalidos, matriz nao criada!\n");
            return NULL;
        }
        ms->lin = l;
        ms->col = c;
        ms->QI = 0;
        ms->QNN = qnn;
        ms->A = ms->IA = ms->JA = NULL;
        if (qnn != 0) {
            ms->A = (int*)malloc(qnn * sizeof(int));
            ms->JA = (int*)malloc(qnn * sizeof(int));
            if (ms->A == NULL || ms->JA == NULL) return NULL;
        }
        ms->IA = (int*)malloc((ms->lin + 1) * sizeof(int));
        if (ms->IA == NULL) return NULL;
        int i;
        for (i = 0; i < l + 1; i++) ms->IA[i] = 0;
    }
    return ms;
}

int* meuRealloc(int* v, int tam) {
    int* aux = (int*)malloc((tam + 1) * sizeof(int));
    if (aux != NULL) {
        if (v != NULL) {
            int i;
            for (i = 0; i < tam; i++)
                aux[i] = v[i];
            free(v);
        }
    }
    return aux;
}

void imprimeEsparsaVetores(MEsparsaCSR* ms) {
    if (ms == NULL) return;
    int i, j;
    printf("Matriz Esparsa, Tam: %d x %d:\n", ms->lin, ms->col);
    printf("%d elementos nao nulos.\n", ms->QNN);
    printf("A = [");
    for (i = 0; i < ms->QNN; i++)
        printf("%d ", ms->A[i]);
    printf("]\n");
    printf("IA = [");
    for (i = 0; i < ms->lin + 1; i++)
        printf("%d ", ms->IA[i]);
    printf("]\n");
    printf("JA = [");
    for (i = 0; i < ms->QNN; i++)
        printf("%d ", ms->JA[i]);
    printf("]\n\n");
}

int insereElemEsparsa(MEsparsaCSR* ms, int elem, int i, int j) {
    if (ms == NULL) return 0;
    if (i < 0 || j < 0 || i >= ms->lin || j >= ms->col) {
        printf("Valores invalidos, elem nao inserido!\n");
        return 0;
    }
    int k;
    int index = -1;
    int ini = ms->IA[i];
    int fim = ms->IA[i + 1];
    // Encontre a posição correta para inserir o valor
    for (k = ini; k < fim; k++)
        if (ms->JA[k] >= j) {
            index = k;
            break;
        }

    if (index == -1) {            // NOVA INSERCAO
        if (ms->QI == ms->QNN) {  // Necessita REALLOC
            ms->A = meuRealloc(ms->A, ms->QNN);
            ms->JA = meuRealloc(ms->JA, ms->QNN);
            ms->QNN++;
        }
        // Move elementos para a nova insercao
        for (k = ms->QNN - 1; k >= fim; k--) {
            ms->A[k] = ms->A[k - 1];
            ms->JA[k] = ms->JA[k - 1];
        }
        ms->A[fim] = elem;
        ms->JA[fim] = j;
        ms->QI++;
        // Atualiza QNN acumulado
        for (int k = i + 1; k <= ms->lin; k++)
            ms->IA[k]++;
    } else {  // Atualiza um valor existente
        ms->A[index] = elem;
    }
    imprimeEsparsaVetores(ms);
    return 1;
}

int removeElemEsparsa(MEsparsaCSR* ms, int i, int j) {
    if (ms == NULL) return 0;
    if (i < 0 || j < 0 || i >= ms->lin || j >= ms->col) {
        printf("Valores invalidos, elem nao removido!\n");
        return 0;
    }

    int k;
    int index = -1;
    int ini = ms->IA[i];
    int fim = ms->IA[i + 1];
    // Encontre a posição do valor a ser removido
    for (k = ini; k < fim; k++)
        if (ms->JA[k] == j) {
            index = k;
            break;
        }

    if (index != -1) {
        // Move todos elementos uma posição para tras
        for (k = index; k < ms->QNN - 1; k++) {
            ms->A[k] = ms->A[k + 1];
            ms->JA[k] = ms->JA[k + 1];
        }
        ms->QNN--;
        ms->QI--;
        // Atualiza QNN acumulado
        for (int k = i + 1; k <= ms->lin; k++)
            ms->IA[k]--;
    } else {
        printf("Elemento nao existente\n");
        return 0;
    }
    imprimeEsparsaVetores(ms);
    return 1;
}

int consultaElemEsparsa(MEsparsaCSR* ms, int i, int j) {
    if (ms == NULL) return 0;
    if (i < 0 || j < 0 || i >= ms->lin || j >= ms->col) {
        printf("Valores invalidos, elem inexistente!\n");
        return 0;
    }
    int k;
    for (k = ms->IA[i]; k < ms->IA[i + 1]; k++)
        if (ms->JA[k] == j) return ms->A[k];
    return 0;
}

void imprimeEsparsa(MEsparsaCSR* ms) {
    if (ms == NULL) return;
    int i, j;
    imprimeEsparsaVetores(ms);
    printf("Matriz Original:\n");
    for (i = 0; i < ms->lin; i++) {
        for (j = 0; j < ms->col; j++)
            printf("%d\t", consultaElemEsparsa(ms, i, j));
        printf("\n");
    }
}

void destroiMatrizEsparsa(MEsparsaCSR* ms) {
    if (ms != NULL) {
        free(ms->A);
        free(ms->IA);
        free(ms->JA);
        free(ms);
    }
}

#endif