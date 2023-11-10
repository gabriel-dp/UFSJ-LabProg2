#include "ex01-01.h"

#include <stdio.h>
#include <stdlib.h>

enum {
    EXIT = 0,
    CREATE,
    INSERT,
    SEARCH,
    REMOVE,
    PRINT,
    SIZE,
    DESTROY
} Options;

int getOption() {
    int option;

    printf("\n====================\n");
    printf("(%d) Criar\n", CREATE);
    printf("(%d) Inserir elemento\n", INSERT);
    printf("(%d) Buscar elemento\n", SEARCH);
    printf("(%d) Remover elemento\n", REMOVE);
    printf("(%d) Imprimir em ordem\n", PRINT);
    printf("(%d) Tamanho\n", SIZE);
    printf("(%d) Destruir\n", DESTROY);
    printf("(%d) Sair\n", EXIT);
    printf("====================\n");
    printf("Operacao: ");

    scanf("%d", &option);
    printf("\n");

    return option;
}

int runMenu() {
    AVL* avl = NULL;
    int exit = 0, item;

    do {
        switch (getOption()) {
            case CREATE:
                if (avl != NULL) {
                    destroiAVL(&avl);
                }
                avl = criaAVL();
                break;

            case INSERT:
                printf("Elemento a ser inserido: ");
                scanf("%d", &item);

                if (insereElem(avl, item)) {
                    printf("Elemento inserido (%d)", item);
                } else {
                    printf("Falha ao inserir (%d)", item);
                }
                break;

            case SEARCH:
                printf("Elemento a ser pesquisado: ");
                scanf("%d", &item);

                if (pesquisa(avl, item)) {
                    printf("Elemento presente (%d)", item);
                } else {
                    printf("Elemento nao encontrado (%d)", item);
                }
                break;

            case REMOVE:
                printf("Elemento a ser removido: ");
                scanf("%d", &item);

                if (removeElem(avl, item)) {
                    printf("Elemento removido (%d)", item);
                } else {
                    printf("Falha ao remover (%d)", item);
                }
                break;

            case PRINT:
                imprime(avl);
                break;

            case SIZE:
                printf("Tamanho = %d", tamanho(*avl, 0));
                break;

            case DESTROY:
                destroiAVL(&avl);
                break;

            case EXIT:
                if (avl != NULL) {
                    destroiAVL(&avl);
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