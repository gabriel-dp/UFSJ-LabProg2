#include "./sort-module.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/*
// Get elements from user input
void getElements(Key *arr, int quantity) {
    char name[NAME_LENGTH + 1];
    for (int i = 0; i < quantity; i++) {
        printf("Name (max length %d): ", NAME_LENGTH);
        setbuf(stdin, NULL);
        fgets(name, NAME_LENGTH, stdin);
        if (name[strlen(name) - 1] == '\n') name[strlen(name) - 1] = '\0';
        strcpy(arr[i].name, name);

        printf("Age: ");
        scanf("%d", &arr[i].age);

        printf("\n");
    }
}

// Compare elements (a.name < b.name) and (a.age < b.age)
int compare(Key a, Key b, int reverse, Statistics* statistics) {
    if (statistics != NULL) statistics->comps++;

    int cmp = strcmp(a.name, b.name);
    if (cmp == 0)
        return (!reverse ? (a.age < b.age) : (a.age > b.age));
    return (!reverse ? (cmp < 0) : (cmp > 0));
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
        printf("%s - %d\n", arr[i].name, arr[i].age);
    }
    printf("\n");
}
*/
