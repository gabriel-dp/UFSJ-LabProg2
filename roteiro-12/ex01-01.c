#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comp;

void preencheAleatorio(int *v, int n, int ini, int fim) {
    int i;
    for (i = 0; i < n; i++)
        v[i] = ini + rand() % (fim - ini + 1);
}

void troca(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

int buscaSequencial(int *v, int n, int elem) {
    int i;
    for (i = 0; i < n; i++) {
        comp++;
        if (v[i] == elem)
            return i;  // Elemento encontrado
    }
    return -1;  // Elemento nao encontrado
}

int particao(int *v, int ini, int fim) {
    int i = ini, j = fim;
    int pivo = v[(ini + fim) / 2];
    while (1) {
        while (v[i] < pivo) {
            i++;
        }  // procura algum >= pivo do lado esquerdo
        while (v[j] > pivo) {
            j--;
        }  // procura algum <= pivo do lado direito

        if (i < j) {
            troca(&v[i], &v[j]);  // troca os elementos encontrados
            i++;
            j--;
        } else
            return j;  // retorna o local onde foi feita a particao
    }
}

void QuickSort(int *v, int ini, int fim) {
    if (ini < fim) {
        int q = particao(v, ini, fim);
        QuickSort(v, ini, q);
        QuickSort(v, q + 1, fim);
    }
}

int rec_buscaBinaria(int *v, int ini, int fim, int elem) {
    if (ini > fim) return -1;
    int meio = (ini + fim) / 2;
    comp++;
    if (v[meio] == elem)
        return meio;
    else if (elem < v[meio])
        return rec_buscaBinaria(v, ini, meio - 1, elem);
    else
        return rec_buscaBinaria(v, meio + 1, fim, elem);
}

int it_buscaBinaria(int *v, int ini, int fim, int elem) {
    int meio;
    while (ini <= fim) {
        meio = (ini + fim) / 2;
        comp++;
        if (elem == v[meio])
            return meio;
        else if (elem < v[meio])
            fim = meio - 1;
        else
            ini = meio + 1;
    }
    return -1;
}

int main() {
    srand(time(NULL));
    comp = 0;
    clock_t t;

    int *v;
    int n, x;
    printf("Digite o tamanho do vetor:\n");
    scanf("%d", &n);
    v = (int *)malloc(n * sizeof(int));

    preencheAleatorio(v, n, 1, n);
    QuickSort(v, 0, n - 1);

    printf("Digite um elemento para busca:\n");
    scanf("%d", &x);

    int ind;

    t = clock();
    ind = buscaSequencial(v, n, x);
    t = clock() - t;
    printf("-----Informacoes Busca Sequencial:\n");
    printf("Tempo Execucao:  %f seconds.\n", ((float)t) / CLOCKS_PER_SEC);
    printf("Comparacoes: %d\n", comp);

    if (ind != -1)
        printf("O elemento %d foi encontrado na pos %d.\n", x, ind);
    else
        printf("O elemento %d NAO foi encontrado!\n", x);

    comp = 0;
    t = clock();
    ind = rec_buscaBinaria(v, 0, n - 1, x);
    t = clock() - t;
    printf("-----Informacoes Busca Binaria Recursiva:\n");
    printf("Tempo Execucao:  %f seconds.\n", ((float)t) / CLOCKS_PER_SEC);
    printf("Comparacoes: %d\n", comp);

    if (ind != -1)
        printf("O elemento %d foi encontrado na pos %d.\n", x, ind);
    else
        printf("O elemento %d NAO foi encontrado!\n", x);

    comp = 0;
    t = clock();
    ind = it_buscaBinaria(v, 0, n - 1, x);
    t = clock() - t;
    printf("-----Informacoes Busca Binaria Iterativa:\n");
    printf("Tempo Execucao:  %f seconds.\n", ((float)t) / CLOCKS_PER_SEC);
    printf("Comparacoes: %d\n", comp);

    if (ind != -1)
        printf("O elemento %d foi encontrado na pos %d.\n", x, ind);
    else
        printf("O elemento %d NAO foi encontrado!\n", x);

    free(v);
    return 0;
}