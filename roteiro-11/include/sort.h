#ifndef SORT_H
#define SORT_H

#include "./sort-module.h"

// Sorting essential functions
void shellSort(Key* arr, int n, int reverse, Statistics* statistics);
void quickSort(Key* arr, int n, int reverse, Statistics* statistics);
void mergeSort(Key* arr, int n, int reverse, Statistics* statistics);
void heapSort(Key* arr, int n, int reverse, Statistics* statistics);
void getOptions(void (**sortFunction)(Key*, int, int, Statistics*), int* order, int* quantity);

#endif