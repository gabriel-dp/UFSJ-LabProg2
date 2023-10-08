#include <stdio.h>
#include <stdlib.h>

/*
 *
 *  O ARQUIVO FUNCIONA PARA AS DUAS IMPLEMENTACOES DE DEQUE
 *  BASTA IMPORTAR APENAS A BIBLIOTECA DESEJADA
 *
 *  EX01-01 = DEQUE SEQUENCIAL ESTATICO
 *  EX01-02 = DEQUE SIMPLESMENTE ENCADEADO
 *
 */

// #include "ex01-01.h"
#include "ex01-02.h"

enum {
    EXIT = 0,
    CREATE,
    QUEUE_START,
    QUEUE_END,
    START,
    END,
    DEQUEUE_START,
    DEQUEUE_END,
    PRINT,
    DESTROY
} Options;

int getOption() {
    int option;

    printf("\n====================\n");
    printf("(%d) Criar\n", CREATE);
    printf("(%d) Enfileirar inicio\n", QUEUE_START);
    printf("(%d) Enfileirar fim\n", QUEUE_END);
    printf("(%d) Ver inicio\n", START);
    printf("(%d) Ver fim\n", END);
    printf("(%d) Desenfileirar inicio\n", DEQUEUE_START);
    printf("(%d) Desenfileirar fim\n", DEQUEUE_END);
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
    Deque* deque = NULL;
    int exit = 0, item;

    do {
        switch (getOption()) {
            case CREATE:
                if (deque != NULL) {
                    destroiDeque(&deque);
                    printf("Deque resetado");
                }
                deque = criaDeque();
                break;

            case QUEUE_START:
                printf("Elemento para enfileirar no inicio: ");
                scanf("%d", &item);
                if (insereInicio(deque, item)) {
                    printf("Enfileirou (%d) no inicio", item);
                } else {
                    printf("Nao foi possivel enfileirar (%d)", item);
                }
                break;

            case QUEUE_END:
                printf("Elemento para enfileirar no fim: ");
                scanf("%d", &item);
                if (insereFim(deque, item)) {
                    printf("Enfileirou (%d) no fim", item);
                } else {
                    printf("Nao foi possivel enfileirar (%d)", item);
                }
                break;

            case START:
                if (verInicio(deque, &item)) {
                    printf("Inicio do deque = %d\n", item);
                } else {
                    printf("Nao foi possivel ver o inicio do deque");
                }
                break;

            case END:
                if (verFim(deque, &item)) {
                    printf("Fim do deque = %d\n", item);
                } else {
                    printf("Nao foi possivel ver o fim do deque");
                }
                break;

            case DEQUEUE_START:
                if (removeInicio(deque)) {
                    printf("Desenfileirou o primeiro elemento");
                } else {
                    printf("Nao foi possivel desenfileirar");
                }
                break;

            case DEQUEUE_END:
                if (removeFim(deque)) {
                    printf("Desenfileirou o ultimo elemento");
                } else {
                    printf("Nao foi possivel desenfileirar");
                }
                break;

            case PRINT:
                imprime(deque);
                break;

            case DESTROY:
                destroiDeque(&deque);
                printf("Deque destruido");
                break;

            case EXIT:
                if (deque != NULL) {
                    destroiDeque(&deque);
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