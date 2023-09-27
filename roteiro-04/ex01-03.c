#include <stdio.h>
#include <stdlib.h>

#include "lista_seq_est.h"

int insereOrdenado(Lista* li, int x) {
    if (li == NULL || listaCheia(li)) return 0;

    int i;
    for (i = 0; i < tamanhoLista(li) && li->dados[i] < x; i++)
        ;
    for (int j = li->qtd; j > i; j--) {
        li->dados[j] = li->dados[j - 1];
    }
    li->dados[i] = x;
    li->qtd++;

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