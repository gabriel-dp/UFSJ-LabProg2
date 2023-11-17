#ifndef SORT_H
#define SORT_H

#include "./time.h"

typedef struct {
    long long comps, swaps;
    Time start, end;
} Statistics;

// Sorting essential functions
void swap(int* a, int* b, Statistics* statistics);
int compare(int a, int b, int invert, Statistics* statistics);
void print(int* arr, int n);
Statistics* createStatistics();
void destroyStatistics(Statistics** s);

// Sorting algorithms
void selectionSort(int* arr, int n, int reverse, Statistics* statistics);
void insertionSort(int* arr, int n, int reverse, Statistics* statistics);
void bubbleSort(int* arr, int n, int reverse, Statistics* statistics);

#endif