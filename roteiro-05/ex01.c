#include <stdio.h>
#include <stdlib.h>

/*
 *
 *  O ARQUIVO FUNCIONA PARA AS DUAS IMPLEMENTACOES DE FILA
 *  BASTA IMPORTAR APENAS BIBLIOTECA DESEJADA
 *
 *  EX01-01 = LISTA SEQUENCIAL ESTATICA
 *  EX01-02 = LISTA SIMPLESMENTE ENCADEADA
 *
 */

// #include "ex01-01.h"
#include "ex01-02.h"

enum {
    EXIT = 0,
    CREATE,
    QUEUE,
    START,
    DEQUEUE,
    PRINT,
    DESTROY
} Options;

int getOption() {
    int option;

    printf("\n====================\n");
    printf("(%d) Criar\n", CREATE);
    printf("(%d) Enfileirar\n", QUEUE);
    printf("(%d) Ver inicio\n", START);
    printf("(%d) Desenfileirar\n", DEQUEUE);
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
    Fila* queue = NULL;
    int exit = 0, item;

    do {
        switch (getOption()) {
            case CREATE:
                if (queue != NULL) {
                    destroiFila(&queue);
                    printf("Fila resetada");
                }
                queue = criaFila();
                break;

            case QUEUE:
                printf("Elemento para enfileirar: ");
                scanf("%d", &item);

                if (enfileirar(queue, item)) {
                    printf("Enfileirou (%d)", item);
                } else {
                    printf("Nao foi possivel enfileirar (%d)", item);
                }

                break;

            case START:
                if (verInicio(queue, &item)) {
                    printf("Inicio da fila = %d\n", item);
                } else {
                    printf("Nao foi possivel ver o inicio da fila");
                }
                break;

            case DEQUEUE:
                if (desenfileirar(queue)) {
                    printf("Desenfileirou o primeiro elemento");
                } else {
                    printf("Nao foi possivel desenfileirar");
                }
                break;

            case PRINT:
                imprime(queue);
                break;

            case DESTROY:
                destroiFila(&queue);
                printf("Fila destruida");
                break;

            case EXIT:
                if (queue != NULL) {
                    destroiFila(&queue);
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