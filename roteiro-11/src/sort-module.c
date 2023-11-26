#include "./sort-module.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Get elements from user input
void getElements(Key* arr, int quantity) {
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
