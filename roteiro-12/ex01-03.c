#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NOME_TAMANHO 50

typedef struct {
    char nome[50 + 1];
    int matricula;
} Aluno;

int comp;

void troca(Aluno *a, Aluno *b) {
    Aluno aux = *a;
    *a = *b;
    *b = aux;
}

int particao(Aluno *v, int ini, int fim, int (*compara)(Aluno *, Aluno *)) {
    int i = ini, j = fim;
    Aluno pivo = v[(ini + fim) / 2];
    while (1) {
        while (compara(&(v[i]), &pivo) < 0) {
            i++;
        }
        while (compara(&(v[j]), &pivo) > 0) {
            j--;
        }

        if (i < j) {
            troca(&v[i], &v[j]);
            i++;
            j--;
        } else
            return j;
    }
}

void QuickSort(Aluno *v, int ini, int fim, int (*compara)(Aluno *, Aluno *)) {
    if (ini < fim) {
        int q = particao(v, ini, fim, compara);
        QuickSort(v, ini, q, compara);
        QuickSort(v, q + 1, fim, compara);
    }
}

int rec_buscaBinaria(Aluno *v, int ini, int fim, Aluno elem, int (*compara)(Aluno *, Aluno *)) {
    if (ini > fim) return -1;
    int meio = (ini + fim) / 2;
    comp++;
    if (compara(&(v[meio]), &elem) == 0)
        return meio;
    else if (compara(&(v[meio]), &elem) > 0)
        return rec_buscaBinaria(v, ini, meio - 1, elem, compara);
    else
        return rec_buscaBinaria(v, meio + 1, fim, elem, compara);
}

int comparaNome(Aluno *a, Aluno *b) {
    return strcmp(a->nome, b->nome);
}

int comparaMatricula(Aluno *a, Aluno *b) {
    return a->matricula - b->matricula;
}

int main() {
    // Atribuicoes iniciais
    srand(time(NULL));
    comp = 0;
    clock_t t;

    Aluno *v, x;
    int n;
    printf("Digite o tamanho do vetor:\n");
    scanf("%d", &n);
    v = (Aluno *)malloc(n * sizeof(Aluno));

    for (int i = 0; i < n; i++) {
        printf("Aluno %d\n", i + 1);
        printf("Nome: ");
        fgets(v[i].nome, NOME_TAMANHO, stdin);
        fgets(v[i].nome, NOME_TAMANHO, stdin);
        printf("Matricula: ");
        scanf("%d", &(v[i].matricula));
    }

    printf("Digite um elemento para busca:\n");
    printf("Nome: ");
    fgets(x.nome, NOME_TAMANHO, stdin);
    fgets(x.nome, NOME_TAMANHO, stdin);
    printf("Matricula: ");
    scanf("%d", &(x.matricula));

    int ind;

    QuickSort(v, 0, n - 1, &comparaNome);
    comp = 0;
    t = clock();
    ind = rec_buscaBinaria(v, 0, n - 1, x, &comparaNome);
    t = clock() - t;
    printf("\n-----Informacoes Busca Binaria Recursiva (Nome):\n");
    printf("Tempo Execucao:  %f seconds.\n", ((float)t) / CLOCKS_PER_SEC);
    printf("Comparacoes: %d\n", comp);

    if (ind != -1)
        printf("O elemento foi encontrado na pos %d.\n", ind);
    else
        printf("O elemento NAO foi encontrado!\n");

    QuickSort(v, 0, n - 1, comparaMatricula);
    comp = 0;
    t = clock();
    ind = rec_buscaBinaria(v, 0, n - 1, x, comparaMatricula);
    t = clock() - t;
    printf("\n-----Informacoes Busca Binaria Recursiva (Matricula):\n");
    printf("Tempo Execucao:  %f seconds.\n", ((float)t) / CLOCKS_PER_SEC);
    printf("Comparacoes: %d\n", comp);

    if (ind != -1)
        printf("O elemento foi encontrado na pos %d.\n", ind);
    else
        printf("O elemento NAO foi encontrado!\n");

    free(v);
    return 0;
}