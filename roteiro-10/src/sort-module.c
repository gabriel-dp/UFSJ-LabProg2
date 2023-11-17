#include "./sort-module.h"

#include <stdio.h>
#include <stdlib.h>

// Get elements from user input
void getElements(Key *arr, int quantity) {
    for (int i = 0; i < quantity; i++) {
        scanf("%d", &arr[i]);
    }
}

// Compare elements (a < b)
int compare(Key a, Key b, int reverse, Statistics* statistics) {
    if (statistics != NULL) statistics->comps++;
    return (!reverse ? (a < b) : (a > b));
}

// Swap elements
void swap(Key* a, Key* b, Statistics* statistics) {
    if (statistics != NULL) statistics->swaps++;
    Key aux = *a;
    *a = *b;
    *b = aux;
}

// Print all elements in the array
void print(Key* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
