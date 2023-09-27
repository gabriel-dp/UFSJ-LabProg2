#include <stdio.h>
#include <stdlib.h>

#include "lista_dup_enc.h"

int removePrimeiroX(Lista* li, int x) {
    if (li == NULL || listaVazia(li)) return 0;

    NO i;  // No inicial auxiliar
    i.prox = *li;

    NO* p = &i;
    while (p->prox != NULL) {
        if (p->prox->info == x) {
            NO* aux = p->prox;
            p->prox = aux->prox;
            p->prox->ant = aux->ant;
            liberarNO(aux);
            break;
        }

        p = p->prox;
    }

    return 1;
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
    removePrimeiroX(l, 7);
    imprimeLista(l);

    destroiLista(l);

    return 0;
}