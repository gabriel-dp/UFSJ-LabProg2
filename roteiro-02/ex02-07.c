#include <stdio.h>

int main() {
    int N = 7;

    int i, j, k, s = 0;
    for (i = 0; i < N - 1; i++)
        for (j = i + 1; j < N; j++)
            for (k = 1; k < j; k++)
                s++;

    printf("%d\n", s);

    return 0;
}