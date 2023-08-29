#include <stdio.h>

#define N 10

void preencheRecursivo(int i, int n, int* vetor) {
    if (i >= n) return;
    vetor[i] = i + 1;
    preencheRecursivo(i + 1, n, vetor);
}

void imprimeVetorCrescente(int i, int n, int* vetor) {
    if (i >= n) return;
    printf("%d ", vetor[i]);
    imprimeVetorCrescente(i + 1, n, vetor);
}

void imprimeVetorDecrescente(int i, int n, int* vetor) {
    if (i >= n) return;
    printf("%d ", vetor[n - 1 - i]);
    imprimeVetorDecrescente(i + 1, n, vetor);
}

int maiorRecursivo(int i, int n, int* vetor) {
    int next = i < n - 1 ? maiorRecursivo(i + 1, n, vetor) : vetor[i];
    return (vetor[i] > next) ? vetor[i] : next;
}

int main() {
    int vetor[N];
    preencheRecursivo(0, N, vetor);
    imprimeVetorCrescente(0, N, vetor);
    printf("\n");
    imprimeVetorDecrescente(0, N, vetor);
    printf("\n");
    printf("maior = %d\n", maiorRecursivo(0, N, vetor));

    return 0;
}
