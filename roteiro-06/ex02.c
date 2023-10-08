#include <stdio.h>
#include <stdlib.h>

/*
 *
 *  O ARQUIVO FUNCIONA PARA AS DUAS IMPLEMENTACOES DE FILA DE PRIORIDADES
 *  BASTA IMPORTAR APENAS A BIBLIOTECA DESEJADA
 *
 *  EX02-01 = FILA DE PRIORIDADES SIMPLESMENTE ENCADEADA
 *  EX02-02 = HEAP
 *
 */

#include "ex02-01.h"
// #include "ex02-02.h"

enum {
    EXIT = 0,
    CREATE,
    QUEUE,
    START,
    DEQUEUE,
    PRINT,
    SIZE,
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
    FilaP* fila = NULL;
    int exit = 0, item, pri;

    do {
        switch (getOption()) {
            case CREATE:
                if (fila != NULL) {
                    destroiFila(&fila);
                    printf("Fila resetada");
                }
                fila = criaFila();
                break;

            case QUEUE:
                printf("Elemento para enfileirar: ");
                scanf("%d", &item);
                printf("Prioridade: ");
                scanf("%d", &pri);
                if (inserirPrio(fila, item, pri)) {
                    printf("Enfileirou (%d)", item);
                } else {
                    printf("Nao foi possivel enfileirar (%d)", item);
                }
                break;

            case START:
                if (verInicio(fila, &item, &pri)) {
                    printf("Inicio da fila = %d (Prioridade = %d)\n", item, pri);
                } else {
                    printf("Nao foi possivel ver o inicio da fila");
                }
                break;

            case DEQUEUE:
                if (removeInicio(fila)) {
                    printf("Desenfileirou o primeiro elemento");
                } else {
                    printf("Nao foi possivel desenfileirar");
                }
                break;

            case PRINT:
                imprime(fila);
                break;

            case SIZE:
                printf("Tamanho da fila = %d", tamanhoFila(fila));
                break;

            case DESTROY:
                destroiFila(&fila);
                printf("Fila destruida");
                break;

            case EXIT:
                if (fila != NULL) {
                    destroiFila(&fila);
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