#include <stdio.h>
#include <stdlib.h>

#include "../include/sort.h"

void throwError(char *message) {
    printf("%s - Aborting...\n", message);
    exit(1);
}

void getOptions(void (**sortFunction)(int *, int, int, Statistics *), int *order, int *quantity) {
    int option;

    // User selects the algorithm
    printf("1 - Selection Sort\n");
    printf("2 - Insertion Sort\n");
    printf("3 - Bubble Sort\n");
    printf("Sorting Algorithm: ");
    scanf("%d", &option);
    switch (option) {
        case 1:
            *sortFunction = &selectionSort;
            break;
        case 2:
            *sortFunction = &insertionSort;
            break;
        case 3:
            *sortFunction = &bubbleSort;
            break;
        default:
            throwError("Invalid algorithm option");
    }

    printf("\n");

    // User selects the order
    printf("0 - Ascending\n");
    printf("1 - Descending\n");
    printf("Order: ");
    scanf("%d", &option);
    if (option != 0 && option != 1)
        throwError("Invalid order option");

    *order = option;

    printf("\n");

    // User enters the quantity
    printf("Number of Elements: ");
    scanf("%d", quantity);
    if (quantity < 0)
        throwError("Invalid number");

    printf("\n");
}

void getElements(int *arr, int quantity) {
    for (int i = 0; i < quantity; i++) {
        scanf("%d", &arr[i]);
    }
}

int main() {
    void (*sortFunction)(int *, int, int, Statistics *);
    int order, quantity;
    getOptions(&sortFunction, &order, &quantity);

    int *arr = (int *)malloc(quantity * sizeof(int));
    getElements(arr, quantity);

    Statistics *s = createStatistics();
    (*sortFunction)(arr, quantity, order, s);
    print(arr, quantity);

    printf("\nStatistics\n");
    printElapsedTime("Elapsed time", s->start, s->end);
    printf("Comparations = %Ld\n", s->comps);
    printf("Swaps = %Ld\n", s->swaps);

    destroyStatistics(&s);
    free(arr);

    return 0;
}