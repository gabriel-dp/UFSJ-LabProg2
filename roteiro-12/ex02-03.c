#include <stdio.h>

#include "hash-lse.h"

int main() {
    int elementos[] = {23, 19, 81, 2, 49, 7, 25, 99};

    Hash* tabela = criaHash(10);

    printf("{ ");
    for (int j = 0; j < (sizeof(elementos) / sizeof(int)); j++) {
        printf("%d ", elementos[j]);
        insereHashLSE(tabela, elementos[j]);
    }
    printf("}\n\n");

    imprimeHash(tabela);

    destroiHash(tabela);

    return 0;
}