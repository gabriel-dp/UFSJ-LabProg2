#include <stdio.h>
#include <stdlib.h>

#include "lista_sim_enc.h"

int tamanho(Lista* li) {
    int t = 0;
    NO* p = *li;
    while (p != NULL) {
        p = p->prox;
        t++;
    }

    return t;
}

int procura(Lista* li, int x) {
    int i = 0;
    NO* p = *li;
    while (p != NULL) {
        if (p->info == x) return i;
        p = p->prox;
        i++;
    }

    return -1;
}

int main() {
    Lista* l = criaLista();

    insereFim(l, 23);
    insereFim(l, 14);
    insereFim(l, 7);
    insereFim(l, 85);
    insereFim(l, 19);
    insereFim(l, 56);

    imprimeLista(l);
    printf("Tamanho = %d\n", tamanho(l));
    printf("Indice do 19 = %d\n", procura(l, 19));

    destroiLista(l);

    return 0;
}