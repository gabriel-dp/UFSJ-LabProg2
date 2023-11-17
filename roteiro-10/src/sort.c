#include "../include/sort.h"

#include <stdio.h>
#include <stdlib.h>

// Allocate a new statistics pointer
Statistics* createStatistics() {
    Statistics* new = (Statistics*)malloc(sizeof(Statistics));
    new->comps = 0;
    new->swaps = 0;
    new->start = 0;
    new->end = 0;
    return new;
}

// Destroy statistics allocated pointer
void destroyStatistics(Statistics** s) {
    if (*s == NULL) return;
    free(*s);
    *s = NULL;
}

// Selection Sort Function
void selectionSort(Key* arr, int n, int reverse, Statistics* statistics) {
    for (int i = 0; i < n; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (compare(arr[j], arr[min], reverse, statistics)) min = j;
        }
        if (compare(arr[min], arr[i], reverse, statistics)) swap(&arr[min], &arr[i], statistics);
    }
}

// Insertion Sort Function
void insertionSort(Key* arr, int n, int reverse, Statistics* statistics) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j >= 1; j--) {
            if (compare(arr[j], arr[j - 1], reverse, statistics))
                swap(&arr[j], &arr[j - 1], statistics);
            else
                break;
        }
    }
}

// Bubble Sort Function
void bubbleSort(Key* arr, int n, int reverse, Statistics* statistics) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(arr[j + 1], arr[j], reverse, statistics)) {
                swap(&arr[j + 1], &arr[j], statistics);
            }
        }
    }
}

// Function to exit the program if there is an error
void throwError(char *message) {
    printf("%s - Aborting...\n", message);
    exit(1);
}

// User select the sorting options
void getOptions(void (**sortFunction)(Key*, int, int, Statistics *), int *order, int *quantity) {
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

