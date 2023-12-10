/*---------------- File: Patricia.h  -------------------+
|TAD: Arvore Patricia                                   |
|					      		                        |
| Do livro do Ziviani     		                        |
| Adaptado por Guilherme C. Pena em 04/12/2023          |
+-------------------------------------------------------+ */

#ifndef PATRICIA_H
#define PATRICIA_H

#include <stdio.h>
#include <stdlib.h>

#define D 6  // depende de TipoChave

typedef unsigned char TipoChave;  // a definir, depende da aplicacao
typedef unsigned char TipoIndexAmp;

typedef enum {
    Interno,
    Externo
} TipoNo;

typedef struct patriciaNO *ArvorePat;

typedef struct patriciaNO {
    TipoNo nt;  // NO type - Uma flag para dizer se o NO eh Externo ou Interno
    union {
        struct {
            TipoIndexAmp Index;
            ArvorePat Esq, Dir;
        } NInterno;
        TipoChave Chave;
    } NO;
} patriciaNO;

// Outra Tentativa da Funcao
int valorBit2(int i, TipoChave k) {
    // Todo numero sera considerado com D bits
    // Exemplo: chave 5 em bin (101) -> (00000101)
    // Exemplo: chave 10 em bin (1010) -> (00001010)
    // Exemplo: chave 11 em bin (1011) -> (00001011)

    int n_bits = D;
    int p = 1, j, r;
    // int r = p << n_bits;//R teria o bit 8 ligado (10000000)

    // //Encontra o bit mais a esquerda primeiro
    // //Esse sera o bit 1
    // while((k & r) != r){ n_bits--; r = p << n_bits; }
    // n_bits++;

    // Desloca i bits a partir da esquerda
    for (j = 1; j <= i; j++)
        n_bits--;

    if (n_bits < 0) return 0;
    r = p << n_bits;

    return ((k & r) == r);  // Retorna se o i-esimo bit eh 1 ou 0
}

int retornaNBits(TipoChave k) {
    int n_bits = D;
    int p = 1;
    int r = p << n_bits;
    // Encontra o bit mais a esquerda primeiro
    // Esse sera o bit 1
    while ((k & r) != r) {
        n_bits--;
        r = p << n_bits;
    }
    n_bits++;
    return n_bits;
}

int valorBit(int i, TipoChave k) {
    int n_bits = D;
    int p = 1, j;
    int r = p << n_bits;
    // Encontra o bit mais a esquerda primeiro
    // Esse sera o bit 1
    while ((k & r) != r) {
        n_bits--;
        r = p << n_bits;
    }
    n_bits++;

    // Desloca i bits a partir da esquerda
    for (j = 1; j <= i; j++)
        n_bits--;

    if (n_bits < 0) return 0;
    r = p << n_bits;

    // printf("Bit[%d] em %d: %d\n", i, k, (k & r) == r);

    return ((k & r) == r);  // Retorna se o i-esimo bit eh 1 ou 0
}

int EExterno(ArvorePat p) {
    // Verifica se p^ eh um nodo externo
    return (p->nt == Externo);
}

ArvorePat CriaNoInt(int i, ArvorePat *Esq, ArvorePat *Dir) {
    ArvorePat p;
    p = (ArvorePat)malloc(sizeof(patriciaNO));
    p->nt = Interno;
    p->NO.NInterno.Esq = *Esq;
    p->NO.NInterno.Dir = *Dir;
    p->NO.NInterno.Index = i;
    return p;
}

ArvorePat CriaNoExt(TipoChave k) {
    ArvorePat p;
    p = (ArvorePat)malloc(sizeof(patriciaNO));
    p->nt = Externo;
    p->NO.Chave = k;
    return p;
}

int Pesquisa(TipoChave k, ArvorePat t) {
    if (EExterno(t)) {
        if (k == t->NO.Chave) {
            printf("Elemento %d encontrado!\n", k);
            return 1;
        } else {
            printf("Elemento %d NAO encontrado!\n", k);
            return 0;
        }
    }
    if (valorBit2(t->NO.NInterno.Index, k) == 0)
        return Pesquisa(k, t->NO.NInterno.Esq);
    else
        return Pesquisa(k, t->NO.NInterno.Dir);
}

ArvorePat InsereEntre(TipoChave k, ArvorePat *t, int i) {
    // printf("Insere Entre %d, [%d]\n", k, i);
    ArvorePat p;
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index) {
        int nb1 = retornaNBits((*t)->NO.Chave);
        int nb2 = retornaNBits(k);
        // cria um novo no externo
        p = CriaNoExt(k);
        if (nb1 <= nb2) {
            if (valorBit2(i, k) == 1)
                return CriaNoInt(i, t, &p);
            else
                return CriaNoInt(i, &p, t);
        } else {
            return CriaNoInt(i, &p, t);
        }
    } else {
        if (valorBit2((*t)->NO.NInterno.Index, k) == 1)
            (*t)->NO.NInterno.Dir = InsereEntre(k, &((*t)->NO.NInterno.Dir), i);
        else
            (*t)->NO.NInterno.Esq = InsereEntre(k, &((*t)->NO.NInterno.Esq), i);
        return (*t);
    }
}

ArvorePat Insere(TipoChave k, ArvorePat *t) {
    printf("Inserindo %d..\n", k);
    ArvorePat p;
    int i;
    if (*t == NULL)
        return CriaNoExt(k);
    else {
        if (Pesquisa(k, *t)) {
            printf("Erro: chave ja esta na arvore\n");
            return (*t);
        }
        p = *t;
        while (!EExterno(p)) {
            if (valorBit2(p->NO.NInterno.Index, k) == 1)
                p = p->NO.NInterno.Dir;
            else
                p = p->NO.NInterno.Esq;
        }
        // acha o primeiro bit diferente
        i = 1;
        while ((i <= D) && (valorBit2((int)i, k) == valorBit2((int)i, p->NO.Chave)))
            i++;
        printf("Bit diferente eh: [%d]\n", i);
        if (i > D) {
            // fazer outra coisa
            // No caso de exemplo, inserir 5 (Bin: 101) antes de 10 (Bin: 1010), funciona corretamente
            // No entanto, ainda nao funciona se inserer 10 antes de 5
            return InsereEntre(k, t, 1);
        } else
            return InsereEntre(k, t, i);
    }
}

void pre_ordem(ArvorePat raiz, int nivel) {
    if (raiz != NULL) {
        printf("Nivel %d: ", nivel);
        if (raiz->nt == Interno) {
            printf("(INT) %d\n", raiz->NO.NInterno.Index);
            pre_ordem(raiz->NO.NInterno.Esq, nivel + 1);
            pre_ordem(raiz->NO.NInterno.Dir, nivel + 1);
        } else {
            printf("(EXT) %d\n", raiz->NO.Chave);
        }
    }
}

void imprimePatricia(ArvorePat raiz) {
    if (raiz == NULL) return;
    pre_ordem(raiz, 0);
    printf("\n");
}

#endif