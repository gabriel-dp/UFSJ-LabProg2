#include <stdio.h>
#include <stdlib.h>

/*
 *
 *  O ARQUIVO FUNCIONA PARA AS DUAS IMPLEMENTACOES DE FILA
 *  BASTA IMPORTAR APENAS A BIBLIOTECA DESEJADA
 *
 *  EX02-01 = PILHA SEQUENCIAL ESTATICA
 *  EX02-02 = PILHA SIMPLESMENTE ENCADEADA
 *
 */

// #include "ex02-01.h"
#include "ex02-02.h"

enum {
    EXIT = 0,
    CREATE,
    STACK,
    START,
    UNSTACK,
    PRINT,
    DESTROY
} Options;

int getOption() {
    int option;

    printf("\n====================\n");
    printf("(%d) Criar\n", CREATE);
    printf("(%d) Empilhar\n", STACK);
    printf("(%d) Ver topo\n", START);
    printf("(%d) Desempilhar\n", UNSTACK);
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
    Pilha* stack = NULL;
    int exit = 0, item;

    do {
        switch (getOption()) {
            case CREATE:
                if (stack != NULL) {
                    destroiPilha(&stack);
                    printf("Pilha resetada");
                }
                stack = criaPilha();
                break;

            case STACK:
                printf("Elemento para empilhar: ");
                scanf("%d", &item);

                if (empilhar(stack, item)) {
                    printf("Empilhou (%d)", item);
                } else {
                    printf("Nao foi possivel enpilhar (%d)", item);
                }
                break;

            case START:
                if (verTopo(stack, &item)) {
                    printf("Topo da pilha = %d\n", item);
                } else {
                    printf("Nao foi possivel ver o topo da pilha");
                }
                break;

            case UNSTACK:
                if (desempilhar(stack)) {
                    printf("Desempilhou o primeiro elemento");
                } else {
                    printf("Nao foi possivel desempilhar");
                }
                break;

            case PRINT:
                imprime(stack);
                break;

            case DESTROY:
                destroiPilha(&stack);
                printf("Pilha destruida");
                break;

            case EXIT:
                if (stack != NULL) {
                    destroiPilha(&stack);
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