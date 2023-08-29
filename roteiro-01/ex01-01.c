#include <stdio.h>

#define TAMANHO 10

int negativos (float* vet, int N) {
    int total = 0;
    for (int i = 0; i < N; i++) {
        if (vet[i] < 0) total++;
    }
    return total;
}

int main () {
    float vetor[TAMANHO] = { 10, -9, 5, -1, -2, 4, 3, 0, 6, -7 };

    printf("[");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%.2f", vetor[i]);
        if (i < TAMANHO - 1) printf(", ");
    }
    printf("]\n");

    printf("Quantidade de negativos = %d\n", negativos(vetor, TAMANHO));
}
