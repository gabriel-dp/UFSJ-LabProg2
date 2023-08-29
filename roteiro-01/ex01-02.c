#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO 10

void preenche(double* vet, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        vet[i] = (rand() % 200) - 100;
    }
}

double max(double* vet, int n) {
    double maior = vet[0];
    for (int i = 1; i < n; i++) {
        if (vet[i] > maior) maior = vet[i];
    }
    return maior;
}

double min(double* vet, int n) {
    double menor = vet[0];
    for (int i = 1; i < n; i++) {
        if (vet[i] < menor) menor = vet[i];
    }
    return menor;
}

double media(double* vet, int n) {
    double total = 0;
    for (int i = 0; i < n; i++) {
        total += vet[i];
    }
    return (total / n);
}

int main() {
    double vetor[TAMANHO];
    preenche(vetor, TAMANHO);

    printf("[");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%.0f ", vetor[i]);
        if (i < TAMANHO - 1) printf(", ");
    }
    printf("]\n");

    printf("min = %.0f\n", min(vetor, TAMANHO));
    printf("max = %.0f\n", max(vetor, TAMANHO));
    printf("media = %.2f\n", media(vetor, TAMANHO));

    return 0;
}
