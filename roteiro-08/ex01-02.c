#include "ex01-02.h"

#include <stdio.h>
#include <stdlib.h>

enum {
    EXIT = 0,
    CREATE,
    INSERT,
    SEARCH,
    REMOVE,
    PRINT_INORDER,
    PRINT_BEST,
    PRINT_WORST,
    DESTROY
} Options;

int getOption() {
    int option;

    printf("\n====================\n");
    printf("(%d) Criar\n", CREATE);
    printf("(%d) Inserir aluno\n", INSERT);
    printf("(%d) Buscar aluno\n", SEARCH);
    printf("(%d) Remover aluno\n", REMOVE);
    printf("(%d) Imprimir em ordem\n", PRINT_INORDER);
    printf("(%d) Imprimir melhor aluno\n", PRINT_BEST);
    printf("(%d) Imprimir pior aluno\n", PRINT_WORST);
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
    int exit = 0;
    Aluno item, *itemp;
    char nome[50];
    int matricula;
    double nota;

    do {
        switch (getOption()) {
            case CREATE:
                if (abp != NULL) {
                    destroiABP(&abp);
                }
                abp = criaABP();

                break;

            case INSERT:
                printf("Aluno a ser inserido\n");
                printf("Nome (Max 50 caracteres): ");
                setbuf(stdin, NULL);
                fgets(item.nome, 50, stdin);
                fixString(item.nome);
                setbuf(stdin, NULL);
                printf("Matricula: ");
                scanf("%d", &item.matricula);
                printf("Nota: ");
                scanf("%lf", &item.nota);

                if (insereElem(abp, item)) {
                    printf("Aluno inserido (%s)", item.nome);
                } else {
                    printf("Falha ao inserir (%s)", item.nome);
                }
                break;

            case SEARCH:
                printf("Nome para buscar (Max 50 caracteres): ");
                setbuf(stdin, NULL);
                fgets(item.nome, 50, stdin);
                fixString(item.nome);
                setbuf(stdin, NULL);

                if (pesquisa(abp, item)) {
                    printf("Aluno presente (%s)", item.nome);
                } else {
                    printf("Aluno nao encontrado (%s)", item.nome);
                }
                break;

            case REMOVE:
                printf("Nome para remover (Max 50 caracteres): ");
                setbuf(stdin, NULL);
                fgets(item.nome, 50, stdin);
                fixString(item.nome);
                setbuf(stdin, NULL);

                if (removeElem(abp, item)) {
                    printf("Aluno removido (%s)", item.nome);
                } else {
                    printf("Falha ao remover (%s)", item.nome);
                }
                break;

            case PRINT_INORDER:
                em_ordem(*abp, 0);
                break;

            case PRINT_BEST:
                itemp = melhor(*abp);
                printf("Melhor aluno\n");
                printf("Nome = %s\nMatricula = %d\nNota = %.2lf", itemp->nome, itemp->matricula, itemp->nota);

                break;

            case PRINT_WORST:
                itemp = pior(*abp);
                printf("Pior aluno\n");
                printf("Nome = %s\nMatricula = %d\nNota = %.2lf", itemp->nome, itemp->matricula, itemp->nota);
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