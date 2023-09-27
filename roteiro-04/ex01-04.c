#include <stdio.h>
#include <stdlib.h>

#include "lista_seq_est.h"

int removePrimeiroX(Lista* li, int x) {
    if (li == NULL || listaVazia(li)) return 0;

    int i;
    for (i = 0; i < li->qtd; i++) {
        if (li->dados[i] == x) break;
    }

    if (i < li->qtd) {
        for (int j = i; j < li->qtd; j++) {
            li->dados[j] = li->dados[j + 1];
        }
        li->qtd--;
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