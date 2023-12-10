#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100

typedef struct sArq {
    FILE *f;
    int pos, max, *buffer;
} Arquivo;

void criaArquivoTeste(char *nome, int ini, int fim) {
    int i;
    FILE *f = fopen(nome, "w");
    srand(time(NULL));
    for (i = 1; i < 1000; i++)
        fprintf(f, "%d\n", ini + rand() % (fim - ini + 1));
    fprintf(f, "%d", ini + rand() % (fim - ini + 1));
    fclose(f);
}

// QuickSort
void troca(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

int particao(int *v, int ini, int fim) {
    int i = ini, j = fim;
    int pivo = v[(ini + fim) / 2];
    while (1) {
        while (v[i] < pivo) i++;  // procura algum >= pivo do lado esquerdo
        while (v[j] > pivo) j--;  // procura algum <= pivo do lado direito

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

//-----------------------------------

// Cria Arquivos Ordenados
void salvaArquivo(char *nome, int *v, int tam, int mudaLinhaFinal) {
    int i;
    FILE *f = fopen(nome, "a");
    for (i = 0; i < tam - 1; i++)
        fprintf(f, "%d\n", v[i]);
    if (mudaLinhaFinal == 0)
        fprintf(f, "%d", v[tam - 1]);
    else
        fprintf(f, "%d\n", v[tam - 1]);
    fclose(f);
}

int criaArquivosOrdenados(char *nome) {
    int *v = (int *)malloc(N * sizeof(int));
    char novo[20];
    int K = 0, total = 0;
    FILE *f = fopen(nome, "r");
    while (!feof(f)) {
        fscanf(f, "%d", &v[total]);
        total++;
        if (total == N) {
            K++;
            sprintf(novo, "Temp%d.txt", K);
            QuickSort(v, 0, N - 1);
            salvaArquivo(novo, v, total, 0);
            total = 0;
        }
    }
    if (total > 0) {
        K++;
        sprintf(novo, "Temp%d.txt", K);
        QuickSort(v, 0, total - 1);
        salvaArquivo(novo, v, total, 0);
    }
    fclose(f);
    free(v);
    return K;
}

//----------------------

// Multiway Merging
void preencheBuffer(Arquivo *arq, int T) {
    int i;
    if (arq->f == NULL) return;
    arq->pos = 0;
    arq->max = 0;
    for (i = 0; i < T; i++) {
        if (!feof(arq->f)) {
            fscanf(arq->f, "%d", &arq->buffer[arq->max]);
            arq->max++;
        } else {
            fclose(arq->f);
            arq->f = NULL;
            break;
        }
    }
}

int procuraMenor(Arquivo *arq, int K, int T, int *menor) {
    int i, idx = -1;
    for (i = 0; i < K; i++) {
        if (arq[i].pos < arq[i].max) {
            if (idx == -1)
                idx = i;
            else {
                if (arq[i].buffer[arq[i].pos] < arq[idx].buffer[arq[idx].pos])
                    idx = i;
            }
        }
    }
    if (idx != -1) {
        *menor = arq[idx].buffer[arq[idx].pos];
        arq[idx].pos++;
        if (arq[idx].pos == arq[idx].max)
            preencheBuffer(&arq[idx], T);
        return 1;
    } else
        return 0;
}

void multiWayMerge(char *nome, int K, int T) {
    char novo[20];
    int i;
    int *saida = (int *)malloc(T * sizeof(int));
    Arquivo *arq;
    arq = (Arquivo *)malloc(K * sizeof(Arquivo));
    for (i = 0; i < K; i++) {
        sprintf(novo, "Temp%d.txt", i + 1);
        arq[i].f = fopen(novo, "r");
        arq[i].buffer = (int *)malloc(T * sizeof(int));
        preencheBuffer(&arq[i], T);
    }
    int menor, qtdSaida = 0;
    while (procuraMenor(arq, K, T, &menor) == 1) {
        saida[qtdSaida] = menor;
        qtdSaida++;
        if (qtdSaida == T) {
            salvaArquivo(nome, saida, T, 1);
            qtdSaida = 0;
        }
    }
    if (qtdSaida != 0)
        salvaArquivo(nome, saida, qtdSaida, 1);

    for (i = 0; i < K; i++) free(arq[i].buffer);
    free(arq);
    free(saida);
}

//----------------------

void MergeSortExterno(char *nome) {
    char novo[20];
    int K = criaArquivosOrdenados(nome);
    int i, T = N / (K + 1);
    remove(nome);
    multiWayMerge(nome, K, T);
    for (i = 0; i < K; i++) {
        sprintf(novo, "Temp%d.txt", i + 1);
        remove(novo);
    }
}

int main() {
    criaArquivoTeste("dados.txt", 1, 1000);
    system("cp dados.txt dados2.txt");
    MergeSortExterno("dados.txt");
    return 0;
}
