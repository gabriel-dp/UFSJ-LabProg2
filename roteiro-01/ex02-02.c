#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR 255

void imprimeLetrasDecrescente(char* vetor, int atual) {
    if (atual > MAX_CHAR) {
        printf("\n");
        return;
    }

    int length = strlen(vetor);
    for (int i = 0; i < length; i++) {
        if (vetor[i] == (char)(MAX_CHAR - atual)) printf("%c", (char)(MAX_CHAR - atual));
    }

    imprimeLetrasDecrescente(vetor, atual + 1);
}

int main () {
    imprimeLetrasDecrescente("gabriel", 0);

    return 0;
}