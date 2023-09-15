#ifndef CUBO_H
#define CUBO_H

typedef struct {
    double lado;
} Cubo;

double lado(Cubo* c);
double area(Cubo* c);
double volume(Cubo* c);

#endif