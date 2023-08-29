#include <stdio.h>

int multiplica(int m, int n) {
    if (n == 0) return 0;
    return m + multiplica(m, n - 1);
}

int main () {
    int n, m;
    printf("Primeiro numero: ");
    scanf("%d", &n);
    printf("Segundo numero: ");
    scanf("%d", &m);

    printf("Produto = %d\n", multiplica(n, m));
    return 0;
}