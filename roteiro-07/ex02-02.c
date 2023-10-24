#include "ex02-02.h"

#include <stdio.h>
#include <stdlib.h>

enum {
    EXIT = 0,
    CREATE,
    INSERT,
    REMOVE,
    QUERY,
    PRINT,
    DESTROY
} Options;

int getOption() {
    int option;

    printf("\n====================\n");
    printf("(%d) Criar\n", CREATE);
    printf("(%d) Inserir\n", INSERT);
    printf("(%d) Remove\n", REMOVE);
    printf("(%d) Consultar\n", QUERY);
    printf("(%d) Imprimir\n", PRINT);
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

                matriz = criaMatriz(linhas, colunas, 0);
                break;

            case INSERT:
                printf("Elemento para inserir: ");
                scanf("%d", &item);
                printf("Linha (inicio 0): ");
                scanf("%d", &linhas);
                printf("Colunas (inicio 0): ");
                scanf("%d", &colunas);

                if (insereElem(matriz, item, linhas, colunas)) {
                    printf("Inseriu(%d) (%d, %d)", item, linhas, colunas);
                } else {
                    printf("Nao foi possivel inserir(%d)", item);
                }
                break;

            case REMOVE:
                printf("Linha (inicio 0): ");
                scanf("%d", &linhas);
                printf("Colunas (inicio 0): ");
                scanf("%d", &colunas);

                if (removeElem(matriz, linhas, colunas)) {
                    printf("Removeu (%d) (%d, %d)", item, linhas, colunas);
                } else {
                    printf("Nao foi possivel remover(%d)", item);
                }

                printf("Matriz zerada");
                break;

            case QUERY:
                printf("Posicao para consultar");
                printf("Linha (inicio 0): ");
                scanf("%d", &linhas);
                printf("Colunas (inicio 0): ");
                scanf("%d", &colunas);

                if (item = consultaElem(matriz, linhas, colunas)) {
                    printf("Elemento = %d\n", item);
                } else {
                    printf("Nao foi consultar a matriz nessa posicao");
                }
                break;

            case PRINT:
                imprime(matriz);
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