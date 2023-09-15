#include <stdio.h>
#include <stdlib.h>
#include "inteiros.h"

Inteiros criar () {
    Inteiros novo;
    novo.alocado = 100;
    novo.elementos = (int*) malloc(sizeof(int) * novo.alocado);
    novo.tamanho = 0;
    return novo;
}

int tamanho(Inteiros* c) {
    return c->tamanho;
}

int busca(Inteiros* c, int numero) {
    for (int i = 0; i < tamanho(c); i++) {
        if (c->elementos[i] == numero) return i;
    }
    return -1;
}

void inserir(Inteiros* c, int numero) {
    if (tamanho(c) >= c->alocado) {
        c->elementos = (int*) realloc(c->elementos, c->alocado * 2);
    }
    c->elementos[tamanho(c)] = numero;
    (c->tamanho)++;
}

void remover(Inteiros* c, int posicao) {
    if (posicao < tamanho(c) - 1) {
        for (int i = posicao; i < tamanho(c); i++) {
            c->elementos[i] = c->elementos[i+1];
        }
        (c->tamanho)--;
    }
}

Inteiros uniao(Inteiros* c1, Inteiros* c2) {
    Inteiros c3 = criar();
    for (int i = 0; i < tamanho(c1); i++) {
        inserir(&c3, c1->elementos[i]);
    }
    for (int i = 0; i < tamanho(c2); i++) {
        inserir(&c3, c2->elementos[i]);
    }
    return c3;
}

Inteiros intersecao(Inteiros* c1, Inteiros* c2) {
    Inteiros c3 = criar();
    for (int i = 0; i < tamanho(c1); i++) {
        if (busca(c2, c1->elementos[i]) != -1) {
            inserir(&c3, c1->elementos[i]);
        }
    }
    return c3;
}

Inteiros diferenca(Inteiros* c1, Inteiros* c2) {
    Inteiros c3 = criar();
    for (int i = 0; i < tamanho(c1); i++) {
        if (busca(c2, c1->elementos[i]) == -1) {
            inserir(&c3, c1->elementos[i]);
        }
    }
    return c3;
}

int imenor(Inteiros* c) {
    if (tamanho(c) == 0) {
        return -1;
    }

    int min = 0;
    for (int i = 1; i < tamanho(c); i++) {
        if (c->elementos[min] > c->elementos[i]) {
            min = i;
        }
    }
}

int imaior(Inteiros* c) {
    if (tamanho(c) == 0) {
        return -1;
    }

    int max = 0;
    for (int i = 1; i < tamanho(c); i++) {
        if (c->elementos[max] < c->elementos[i]) {
            max = i;
        }
    }
}

int iguais(Inteiros* c1, Inteiros* c2) {
    int diff = 0;
    for (int i = 0; i < tamanho(c1); i++) {
        if (busca(c2, c1->elementos[i]) == -1) {
            diff = 1;
            break;
        }
    }

    return diff;
}

int vazio(Inteiros* c) {
    return (tamanho(c) == 0);
}

void imprime (Inteiros* c) {
    for (int i = 0; i < tamanho(c); i++) {
        printf("%d ", c->elementos[i]);
    }
    printf("\n");
}

int main() {
    Inteiros i1 = criar();
    inserir(&i1, 23);
    inserir(&i1, 12);
    inserir(&i1, 5);
    inserir(&i1, 47);
    inserir(&i1, 81);
    
    Inteiros i2 = criar();
    inserir(&i2, 15);
    inserir(&i2, 13);
    inserir(&i2, 5);
    inserir(&i2, 99);
    inserir(&i2, 81);

    imprime(&i1);
    imprime(&i2);

    Inteiros une = uniao(&i1, &i2);
    Inteiros inter = intersecao(&i1, &i2);
    imprime(&une);
    imprime(&inter);


    return 0;
}