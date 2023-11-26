#include "../include/sort.h"

#include <stdio.h>
#include <stdlib.h>

#pragma region SHELL_SORT
void shellSort(Key* arr, int n, int reverse, Statistics* statistics) {
    Key aux;
    int h = 1;

    do {
        h = 3 * h + 1;
    } while (h < n);

    do {
        h /= 3;
        for (int i = h; i < n; i++) {
            aux = arr[i];

            int j = i;
            while (j >= h && !compare(arr[j - h], aux, reverse, statistics)) {
                arr[j] = arr[j - h];
                statistics->swaps++;
                j -= h;
            }

            arr[j] = aux;
        }
    } while (h > 1);
}
#pragma endregion

#pragma region QUICK_SORT
Key partition(Key* arr, int low, int high, int reverse, Statistics* statistics) {
    Key pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (!compare(pivot, arr[j], reverse, statistics)) {
            i++;
            swap(&arr[i], &arr[j], statistics);
        }
    }

    swap(&arr[i + 1], &arr[high], statistics);
    return (i + 1);
}

void quickSortRecursion(Key* arr, int low, int high, int reverse, Statistics* statistics) {
    if (low < high) {
        int pi = partition(arr, low, high, reverse, statistics);
        quickSortRecursion(arr, low, pi - 1, reverse, statistics);
        quickSortRecursion(arr, pi + 1, high, reverse, statistics);
    }
}

void quickSort(Key* arr, int n, int reverse, Statistics* statistics) {
    quickSortRecursion(arr, 0, n - 1, reverse, statistics);
}
#pragma endregion

#pragma region MERGE_SORT
void merge(Key arr[], int l, int m, int r, int reverse, Statistics* statistics) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
        statistics->swaps++;
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
        statistics->swaps++;
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (compare(L[i], R[j], reverse, statistics)) {
            arr[k] = L[i];
            statistics->swaps++;
            i++;
        } else {
            arr[k] = R[j];
            statistics->swaps++;
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        statistics->swaps++;
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        statistics->swaps++;
        j++;
        k++;
    }
}

void mergeSortRecursion(Key arr[], int l, int r, int reverse, Statistics* statistics) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortRecursion(arr, l, m, reverse, statistics);
        mergeSortRecursion(arr, m + 1, r, reverse, statistics);
        merge(arr, l, m, r, reverse, statistics);
    }
}

void mergeSort(Key* arr, int n, int reverse, Statistics* statistics) {
    mergeSortRecursion(arr, 0, n - 1, reverse, statistics);
}
#pragma endregion

#pragma region HEAP_SORT
void heapify(Key arr[], int n, int i, int reverse, Statistics* statistics) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && !compare(arr[left], arr[largest], reverse, statistics))
        largest = left;

    if (right < n && !compare(arr[right], arr[largest], reverse, statistics))
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest], statistics);
        heapify(arr, n, largest, reverse, statistics);
    }
}

void heapSort(Key* arr, int n, int reverse, Statistics* statistics) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, reverse, statistics);

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i], statistics);
        heapify(arr, i, 0, reverse, statistics);
    }
}
#pragma endregion

// Function to exit the program if there is an error
void throwError(char* message) {
    printf("%s - Aborting...\n", message);
    exit(1);
}

// User select the sorting options
void getOptions(void (**sortFunction)(Key*, int, int, Statistics*), int* order, int* quantity) {
    int option;

    // User selects the algorithm
    printf("1 - Shell Sort\n");
    printf("2 - Quick Sort\n");
    printf("3 - Merge Sort\n");
    printf("4 - Heap Sort\n");
    printf("Sorting Algorithm: ");
    scanf("%d", &option);
    switch (option) {
        case 1:
            *sortFunction = &shellSort;
            break;
        case 2:
            *sortFunction = &quickSort;
            break;
        case 3:
            *sortFunction = &mergeSort;
            break;
        case 4:
            *sortFunction = &heapSort;
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
