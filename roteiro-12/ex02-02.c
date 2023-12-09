#include <stdio.h>

#include "hash.h"

int main() {
    int elementos[] = {23, 19, 81, 2, 49, 7, 25, 99};
    char* funsNome[] = {"Linear", "Quadratica", "Duplo Hash"};
    int (*funsSondagem[])(int, int, int, int, int (*)(int, int)) = {&sondagemLinear, &sondagemQuadratica, &sondagemDuploHash};

    printf("{ ");
    for (int j = 0; j < (sizeof(elementos) / sizeof(int)); j++)
        printf("%d ", elementos[j]);
    printf("}\n\n");

    for (int i = 0; i < (sizeof(funsSondagem) / sizeof(funsSondagem[0])); i++) {
        Hash* tabela = criaHash(10);

        for (int j = 0; j < (sizeof(elementos) / sizeof(int)); j++)
            insereHash_EnderAberto(tabela, elementos[j], &chaveDivisao, funsSondagem[i]);

        printf("%s\n", funsNome[i]);
        imprimeHash(tabela);
        printf("\n");

        destroiHash(tabela);
    }

    return 0;
}