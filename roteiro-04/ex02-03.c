#include <stdio.h>
#include <stdlib.h>

#include "lista_sim_enc.h"

int insereOrdenado(Lista* li, int x) {
    if (li == NULL) return 0;

    NO* novo = alocarNO();
    novo->info = x;
    novo->prox = NULL;

    if (listaVazia(li)) {
        *li = novo;
    } else {
        NO i;
        i.prox = *li;

        NO* p = &i;
        while (p->prox != NULL && p->prox->info < x) {
            p = p->prox;
        }

        if (p->prox == *li) {
            novo->prox = *li;
            *li = novo;
        }

        novo->prox = p->prox;
        p->prox = novo;
    }

    return 1;
}

int main() {
    Lista* l = criaLista();

    insereOrdenado(l, 23);
    imprimeLista(l);
    insereOrdenado(l, 14);
    imprimeLista(l);
    insereOrdenado(l, 7);
    imprimeLista(l);
    insereOrdenado(l, 85);
    imprimeLista(l);
    insereOrdenado(l, 19);
    imprimeLista(l);
    insereOrdenado(l, 56);
    imprimeLista(l);

    destroiLista(l);

    return 0;
}