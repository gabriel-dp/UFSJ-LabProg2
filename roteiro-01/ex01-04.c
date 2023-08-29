#include <math.h>
#include <stdio.h>

int raizes(float a, float b, float c, float* x1, float* x2) {
    float delta = ((b * b) - (4 * a * c));

    if (delta < 0) return 0;

    if (delta == 0) {
        *x1 = ((-b) / (2 * a));
        return 1;
    }

    *x1 = ((-b + sqrt(delta)) / (2 * a));
    *x2 = ((-b - sqrt(delta)) / (2 * a));
    return 2;
}

int main() {
    float a, b, c, x1, x2;
    printf("ax^2: ");
    scanf("%f", &a);
    printf("bx: ");
    scanf("%f", &b);
    printf("c: ");
    scanf("%f", &c);

    switch (raizes(a, b, c, &x1, &x2)) {
        case 1:
            printf("uma raiz real\n");
            printf("x1 = %f", x1);
            break;
        case 2:
            printf("duas raizes reais\n");
            printf("x1 = %f | x2 = %f", x1, x2);
            break;
        default:
            printf("nao existe raiz real\n");
            break;
    }
    printf("\n");

    return 0;
}