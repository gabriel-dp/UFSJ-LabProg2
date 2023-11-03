#include "ex01-01.h"

#include <stdio.h>
#include <stdlib.h>

enum {
    EXIT = 0,
    CREATE,
    INSERT,
    SEARCH,
    REMOVE,
    PRINT_INORDER,
    PRINT_PREORDER,
    PRINT_POSTORDER,
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
    printf("(%d) Imprimir em ordem\n", PRINT_INORDER);
    printf("(%d) Imprimir em pré-ordem\n", PRINT_PREORDER);
    printf("(%d) Imprimir em pós-ordem\n", PRINT_POSTORDER);
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
    ABP* abp = NULL;
    int exit = 0, item;

    do {
        switch (getOption()) {
            case CREATE:
                if (abp != NULL) {
                    destroiABP(&abp);
                }
                abp = criaABP();
                break;

            case INSERT:
                printf("Elemento a ser inserido: ");
                scanf("%d", &item);

                if (insereElem(abp, item)) {
                    printf("Elemento inserido (%d)", item);
                } else {
                    printf("Falha ao inserir (%d)", item);
                }
                break;

            case SEARCH:
                printf("Elemento a ser pesquisado: ");
                scanf("%d", &item);

                if (pesquisa(abp, item)) {
                    printf("Elemento presente (%d)", item);
                } else {
                    printf("Elemento nao encontrado (%d)", item);
                }
                break;

            case REMOVE:
                printf("Elemento a ser removido: ");
                scanf("%d", &item);

                if (removeElem(abp, item)) {
                    printf("Elemento removido (%d)", item);
                } else {
                    printf("Falha ao remover (%d)", item);
                }
                break;

            case PRINT_INORDER:
                em_ordem(*abp, 0);
                break;

            case PRINT_PREORDER:
                pre_ordem(*abp, 0);
                break;
            case PRINT_POSTORDER:
                pos_ordem(*abp, 0);
                break;

            case SIZE:
                printf("Tamanho = %d", tamanho(*abp, 0));
                break;

            case DESTROY:
                destroiABP(&abp);
                break;

            case EXIT:
                if (abp != NULL) {
                    destroiABP(&abp);
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