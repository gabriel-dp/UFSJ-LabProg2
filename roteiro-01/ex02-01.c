#include <stdio.h>

void printCrescente(int i, int max) {
    if (i > max) return;
    printf("(%d)", i);
    printCrescente(i + 1, max);
}

void printDecrescente(int min, int i) {
    if (i < min) return;
    printf("(%d)", i);
    printDecrescente(min, i - 1);
}

int main () {
    printCrescente(1, 5);
    printf("\n");
    printDecrescente(1, 5);
    printf("\n");

    return 0;
}