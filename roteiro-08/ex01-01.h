#ifndef ABP_H
#define ABP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct NO {
    int info;
    struct NO* esq;
    struct NO* dir;
} NO;

typedef struct NO* ABP;

NO* alocarNO() {
    return (NO*)malloc(sizeof(NO));
}

void liberarNO(NO* q) {
    free(q);
}

ABP* criaABP() {
    ABP* raiz = (ABP*)malloc(sizeof(ABP));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void destroiRec(NO* no) {
    if (no == NULL) return;
    destroiRec(no->esq);
    destroiRec(no->dir);
    liberarNO(no);
    no = NULL;
}

void destroiABP(ABP** raiz) {
    if (*raiz != NULL) {
        destroiRec(**raiz);
        free(*raiz);
        *raiz = NULL;
    }
}

int estaVazia(ABP* raiz) {
    if (raiz == NULL) return 0;
    return (*raiz == NULL);
}

int insereRec(NO** raiz, int elem) {
    if (*raiz == NULL) {
        NO* novo = alocarNO();
        if (novo == NULL) return 0;
        novo->info = elem;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
    } else {
        if ((*raiz)->info == elem) {
            printf("Elemento Existente!\n");
            return 0;
        }
        if (elem < (*raiz)->info)
            return insereRec(&(*raiz)->esq, elem);
        else if (elem > (*raiz)->info)
            return insereRec(&(*raiz)->dir, elem);
    }
    return 1;
}

int insereElem(ABP* raiz, int elem) {
    if (raiz == NULL) return 0;
    return insereRec(raiz, elem);
}

int pesquisaRec(NO** raiz, int elem) {
    if (*raiz == NULL) return 0;
    if ((*raiz)->info == elem) return 1;
    if (elem < (*raiz)->info)
        return pesquisaRec(&(*raiz)->esq, elem);
    else
        return pesquisaRec(&(*raiz)->dir, elem);
}

int pesquisa(ABP* raiz, int elem) {
    if (raiz == NULL) return 0;
    if (estaVazia(raiz)) return 0;
    return pesquisaRec(raiz, elem);
}

int removeRec(NO** raiz, int elem) {
    if (*raiz == NULL) return 0;
    if ((*raiz)->info == elem) {
        NO* aux;
        if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {  // Caso 1 - NO sem filhos
            printf("Caso 1: Liberando %d..\n", (*raiz)->info);
            liberarNO(*raiz);
            *raiz = NULL;
        } else if ((*raiz)->esq == NULL) {  // Caso 2.1 - Possui apenas uma subarvore direita
            printf("Caso 2.1: Liberando %d..\n", (*raiz)->info);
            aux = *raiz;
            *raiz = (*raiz)->dir;
            liberarNO(aux);
        } else if ((*raiz)->dir == NULL) {  // Caso 2.2 - Possui apenas uma subarvore esquerda
            printf("Caso 2.2: Liberando %d..\n", (*raiz)->info);
            aux = *raiz;
            *raiz = (*raiz)->esq;
            liberarNO(aux);
        } else {  // Caso 3 - Possui as duas subarvores (esq e dir)
            printf("Caso 3: Liberando %d..\n", (*raiz)->info);
            NO* Filho = (*raiz)->esq;
            while (Filho->dir != NULL)  // Localiza o MAIOR valor da subarvore esquerda
                Filho = Filho->dir;
            (*raiz)->info = Filho->info;
            Filho->info = elem;
            return removeRec(&(*raiz)->esq, elem);
        }
        return 1;
    } else if (elem < (*raiz)->info)
        return removeRec(&(*raiz)->esq, elem);
    else
        return removeRec(&(*raiz)->dir, elem);
}

int removeElem(ABP* raiz, int elem) {
    if (pesquisa(raiz, elem) == 0) {
        printf("Elemento inexistente!\n");
        return 0;
    }
    return removeRec(raiz, elem);
}

void em_ordem(NO* raiz, int nivel) {
    if (raiz != NULL) {
        em_ordem(raiz->esq, nivel + 1);
        printf("[%d, %d] ", raiz->info, nivel);
        em_ordem(raiz->dir, nivel + 1);
    }
}

void pre_ordem(NO* raiz, int nivel) {
    if (raiz != NULL) {
        printf("[%d, %d] ", raiz->info, nivel);
        pre_ordem(raiz->esq, nivel + 1);
        pre_ordem(raiz->dir, nivel + 1);
    }
}

void pos_ordem(NO* raiz, int nivel) {
    if (raiz != NULL) {
        pos_ordem(raiz->esq, nivel + 1);
        pos_ordem(raiz->dir, nivel + 1);
        printf("[%d, %d] ", raiz->info, nivel);
    }
}

int tamanho(NO* raiz, int inicial) {
    if (raiz == NULL) return 0;

    int t = 1;
    t += tamanho(raiz->esq, 0);
    t += tamanho(raiz->dir, 0);
    return t;
}

#endif