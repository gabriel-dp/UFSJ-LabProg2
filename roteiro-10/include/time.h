#ifndef TEMPO_H
#define TEMPO_H

#include <stdio.h>
#include <stdlib.h>

typedef long double Time;

Time getCpuTime();
Time formatTime(long int sec, long int usec);
void printElapsedTime(char* message, Time start, Time end);

#endif