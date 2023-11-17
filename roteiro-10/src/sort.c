#include "../include/sort.h"

#include <stdio.h>
#include <stdlib.h>

int compare(int a, int b, int reverse, Statistics* statistics) {
    if (statistics != NULL) statistics->comps++;
    return (!reverse ? (a < b) : (a > b));
}

void swap(int* a, int* b, Statistics* statistics) {
    if (statistics != NULL) statistics->swaps++;
    int aux = *a;
    *a = *b;
    *b = aux;
}

void print(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

Statistics* createStatistics() {
    Statistics* new = (Statistics*)malloc(sizeof(Statistics));
    new->comps = 0;
    new->swaps = 0;
    new->start = 0;
    new->end = 0;
    return new;
}

void destroyStatistics(Statistics** s) {
    if (*s == NULL) return;
    free(*s);
    *s = NULL;
}

void selectionSort(int* arr, int n, int reverse, Statistics* statistics) {
    statistics->start = getCpuTime();

    for (int i = 0; i < n; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (compare(arr[j], arr[min], reverse, statistics)) min = j;
        }
        if (compare(arr[min], arr[i], reverse, statistics)) swap(&arr[min], &arr[i], statistics);
    }

    statistics->end = getCpuTime();
}

void insertionSort(int* arr, int n, int reverse, Statistics* statistics) {
    statistics->start = getCpuTime();

    for (int i = 0; i < n; i++) {
        for (int j = i; j >= 1; j--) {
            if (compare(arr[j], arr[j - 1], reverse, statistics))
                swap(&arr[j], &arr[j - 1], statistics);
            else
                break;
        }
    }

    statistics->end = getCpuTime();
}

void bubbleSort(int* arr, int n, int reverse, Statistics* statistics) {
    statistics->start = getCpuTime();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compare(arr[j + 1], arr[j], reverse, statistics)) {
                swap(&arr[j + 1], &arr[j], statistics);
            }
        }
    }

    statistics->end = getCpuTime();
}