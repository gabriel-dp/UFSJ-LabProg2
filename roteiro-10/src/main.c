#include <stdio.h>
#include <stdlib.h>

#include "../include/sort-module.h"
#include "../include/sort.h"
#include "../include/time.h"

int main() {
    void (*sortFunction)(Key *, int, int, Statistics *);
    int order, quantity;
    getOptions(&sortFunction, &order, &quantity);

    Key *arr = (Key *)malloc(quantity * sizeof(Key));
    getElements(arr, quantity);

    Statistics *s = createStatistics();
    s->start = getCpuTime();
    (*sortFunction)(arr, quantity, order, s);
    s->end = getCpuTime();

    print(arr, quantity);

    printf("\n== Statistics ==\n");
    printf("Elapsed time = ");
    printElapsedTime(s->start, s->end);
    printf("\nComparations = %Ld\n", s->comps);
    printf("Swaps = %Ld\n", s->swaps);

    destroyStatistics(&s);
    free(arr);

    return 0;
}