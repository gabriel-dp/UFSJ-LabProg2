#ifndef SORT_MODULE_PERSON_H
#define SORT_MODULE_PERSON_H

#include <stdio.h>
#include <stdlib.h>

#include "./time.h"

#define NAME_LENGTH 50

typedef struct Person {
    char name[NAME_LENGTH + 1];
    int age;
} Key;

typedef struct {
    long long comps, swaps;
    Time start, end;
} Statistics;

void getElements(Key *arr, int quantity);
int compare(Key a, Key b, int reverse, Statistics* statistics);
void swap(Key* a, Key* b, Statistics* statistics);
void print(Key* arr, int n);

#endif