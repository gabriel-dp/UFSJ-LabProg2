#include <stdio.h>

int somaIntervaloRecursivo(int atual, int inf, int sup) {
    if (atual < inf) return 0;
    return atual + somaIntervaloRecursivo(atual - 1, inf, sup);
}

int main() {
    int inf, sup, soma = 0;

    printf("limite inferior: ");
    scanf("%d", &inf);
    printf("limite superior: ");
    scanf("%d", &sup);
    printf("somatorio = %d\n", somaIntervaloRecursivo(sup, inf, sup));

    return 0;
}