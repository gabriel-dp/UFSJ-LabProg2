#include <stdio.h>
#include "cubo.h"

double lado (Cubo* c) {
    return c->lado;
}

double area(Cubo* c){
    double l = lado(c);
    return l * l;    
}

double volume(Cubo* c){
    double a = area(c);
    double l = lado(c);
    return a * l;
}

int main() {
    double l;
    
    printf("Lado do cubo: ");
    scanf("%lf", &l);
    Cubo c;
    c.lado = l;

    printf("Lado = %.2lf\n", lado(&c));
    printf("Area = %.2lf\n", area(&c));
    printf("Volume = %.2lf\n", volume(&c));

    return 0;
}