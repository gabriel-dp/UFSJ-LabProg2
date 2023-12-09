#include <stdio.h>

#include "hash.h"

int main() {
    int elementos[] = {23, 19, 81, 2, 49, 7, 25, 99};
    char* funsNome[] = {"Divisao", "Multiplicacao", "Dobra"};
    int (*funsChave[])(int, int) = {&chaveDivisao, &chaveMultiplicacao, &chaveDobra};

    printf("{ ");
    for (int j = 0; j < (sizeof(elementos) / sizeof(int)); j++) {
        printf("%d ", elementos[j]);
    }
    printf("}\n\n");

    for (int i = 0; i < (sizeof(funsChave) / sizeof(funsChave[0])); i++) {
        Hash* tabela = criaHash(10);

        for (int j = 0; j < (sizeof(elementos) / sizeof(int)); j++)
            insereHash_semTratar(tabela, elementos[j], funsChave[i]);

        printf("%s\n", funsNome[i]);
        imprimeHash(tabela);
        printf("\n");

        destroiHash(tabela);
    }

    return 0;
}