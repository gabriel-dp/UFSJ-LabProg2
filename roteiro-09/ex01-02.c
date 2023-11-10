#include "ex01-02.h"

#include <stdio.h>
#include <stdlib.h>

enum {
    EXIT = 0,
    CREATE,
    INSERT,
    SEARCH,
    REMOVE,
    PRINT,
    PRINT_BEST,
    PRINT_WORST,
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
    printf("(%d) Imprimir funcionario com maior salario\n", PRINT_BEST);
    printf("(%d) Imprimir funcionario com menor salario\n", PRINT_WORST);
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
    int exit = 0;

    Funcionario item, *itemp;
    char nome[50];
    int contratacao;
    double salario;

    do {
        switch (getOption()) {
            case CREATE:
                if (avl != NULL) {
                    destroiAVL(&avl);
                }
                avl = criaAVL();
                break;

            case INSERT:
                printf("Funcionario a ser inserido\n");
                printf("Nome (Max 50 caracteres): ");
                setbuf(stdin, NULL);
                fgets(item.nome, 50, stdin);
                fixString(item.nome);
                setbuf(stdin, NULL);
                printf("Ano de contratacao: ");
                scanf("%d", &item.contratacao);
                printf("Salario: ");
                scanf("%lf", &item.salario);

                if (insereElem(avl, item)) {
                    printf("Funcionario inserido (%s)", item.nome);
                } else {
                    printf("Falha ao inserir (%s)", item.nome);
                }
                break;

            case SEARCH:
                printf("Salario para buscar: ");
                scanf("%lf", &item.salario);

                if (pesquisa(avl, item)) {
                    printf("Funcionario presente (%.2lf)", item.salario);
                } else {
                    printf("Funcionario nao encontrado (%.2lf)", item.salario);
                }
                break;

            case REMOVE:
                printf("Nome para remover (Max 50 caracteres): ");
                setbuf(stdin, NULL);
                fgets(item.nome, 50, stdin);
                fixString(item.nome);
                setbuf(stdin, NULL);

                if (removeElem(avl, item)) {
                    printf("Funcionario removido (%s)", item.nome);
                } else {
                    printf("Falha ao remover (%s)", item.nome);
                }
                break;

            case PRINT:
                imprime(avl);
                break;

            case PRINT_BEST:
                itemp = melhor(*avl);
                printf("Funcionario com o maior salario\n");
                printf("Nome = %s\nContratacao = %d\nSalario = %.2lf", itemp->nome, itemp->contratacao, itemp->salario);
                break;

            case PRINT_WORST:
                itemp = melhor(*avl);
                printf("Funcionario com o menor salario\n");
                printf("Nome = %s\nContratacao = %d\nSalario = %.2lf", itemp->nome, itemp->contratacao, itemp->salario);
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