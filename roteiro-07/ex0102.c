#include <stdio.h>
#include <stdlib.h>

/*
 *
 *  O ARQUIVO FUNCIONA PARA AS DUAS IMPLEMENTACOES DE MATRIZES
 *  BASTA IMPORTAR APENAS A BIBLIOTECA DESEJADA
 *
 *  EX01-01 = MATRIZ SEQUENCIAL ESTATICA
 *  EX01-02 = MATRIZ SEQUENCIAL DINAMICA
 *
 */

// #include "ex01-01.h"
#include "ex01-02.h"

enum {
    EXIT = 0,
    CREATE,
    FILL,
    INSERT,
    QUERY,
    PRINT,
    RESET,
    DESTROY
} Options;

int getOption() {
    int option;

    printf("\n====================\n");
    printf("(%d) Criar\n", CREATE);
    printf("(%d) Preencher aleatoriamente\n", FILL);
    printf("(%d) Inserir\n", INSERT);
    printf("(%d) Consultar\n", QUERY);
    printf("(%d) Imprimir\n", PRINT);
    printf("(%d) Zerar\n", RESET);
    printf("(%d) Destruir\n", DESTROY);
    printf("(%d) Sair\n", EXIT);
    printf("====================\n");
    printf("Operacao: ");

    scanf("%d", &option);
    printf("\n");

    return option;
}

int runMenu() {
    Matriz* matriz = NULL;
    int exit = 0, item, pri, linhas, colunas, min, max;

    do {
        switch (getOption()) {
            case CREATE:
                if (matriz != NULL) {
                    destroiMatriz(&matriz);
                    printf("Matriz apagada");
                }

                printf("Insira as dimensoes\n");
                printf("Linhas: ");
                scanf("%d", &linhas);
                printf("Colunas: ");
                scanf("%d", &colunas);

                matriz = criaMatriz(linhas, colunas);
                break;

            case FILL:
                printf("Insira os limites dos valores\n");
                printf("Min: ");
                scanf("%d", &min);
                printf("Max: ");
                scanf("%d", &max);

                preencheAleatorio(matriz, min, max);
                break;

            case INSERT:
                printf("Elemento para inserir: ");
                scanf("%d", &item);
                printf("Linha (inicio 0): ");
                scanf("%d", &linhas);
                printf("Colunas (inicio 0): ");
                scanf("%d", &colunas);

                if (insereElem(matriz, item, linhas, colunas)) {
                    printf("Inserir(%d) (%d, %d)", item, linhas, colunas);
                } else {
                    printf("Nao foi possivel inserir(%d)", item);
                }
                break;

            case QUERY:
                printf("Posicao para consultar");
                printf("Linha (inicio 0): ");
                scanf("%d", &linhas);
                printf("Colunas (inicio 0): ");
                scanf("%d", &colunas);

                if (consultaElem(matriz, &item, linhas, colunas)) {
                    printf("Elemento = %d\n", item);
                } else {
                    printf("Nao foi consultar a matriz nessa posicao");
                }
                break;

            case PRINT:
                imprime(matriz);
                break;

            case RESET:
                zeraMatriz(matriz);
                printf("Matriz zerada");
                break;

            case DESTROY:
                destroiMatriz(&matriz);
                printf("Matriz destruida");
                break;

            case EXIT:
                if (matriz != NULL) {
                    destroiMatriz(&matriz);
                }
                printf("Programa encerrado");
                exit = 1;
                break;

            default:
                printf("Opcao desconhecida, tente novamente");
        }
        printf("\n");
    } while (!exit);
}

int main() {
    runMenu();
    return 0;
}