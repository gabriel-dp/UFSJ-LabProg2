#include <stdio.h>
#include <stdlib.h>

#include "lista_seq_est.h"

int procura(Lista* li, int x) {
    for (int i = 0; i < tamanhoLista(li); i++) {
        if (li->dados[i] == x) {
            return i;
        }
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
    printf("Indice do 19 = %d\n", procura(l, 19));

    destroiLista(l);

    return 0;
}