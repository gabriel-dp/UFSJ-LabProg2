#ifndef SORT_MODULE_H
#define SORT_MODULE_H

#include <stdio.h>
#include <stdlib.h>

#include "./time.h"

typedef int Key;

typedef struct {
    long long comps, swaps;
    Time start, end;
} Statistics;

void getElements(Key *arr, int quantity);
int compare(Key a, Key b, int reverse, Statistics* statistics);
void swap(Key* a, Key* b, Statistics* statistics);
void print(Key* arr, int n);

#endif