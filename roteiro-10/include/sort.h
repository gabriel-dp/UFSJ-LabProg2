#ifndef SORT_H
#define SORT_H

#include "./sort-module-person.h"

// Sorting essential functions
Statistics* createStatistics();
void destroyStatistics(Statistics** s);
void selectionSort(Key* arr, int n, int reverse, Statistics* statistics);
void insertionSort(Key* arr, int n, int reverse, Statistics* statistics);
void bubbleSort(Key* arr, int n, int reverse, Statistics* statistics);
void getOptions(void (**sortFunction)(Key *, int, int, Statistics *), int *order, int *quantity);

#endif