#include "../include/time.h"

#include <sys/resource.h>

// Returns CPU time in that moment
Time getCpuTime() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return formatTime(usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
}

// Join time in seconds and microseconds into a long double variable
Time formatTime(long int sec, long int usec) {
    Time totalTime = sec + ((Time)usec / 1000000.0L);
    return totalTime;
}

// Prints the difference between start to end
void printElapsedTime(Time start, Time end) {
    Time elapsedTime = end - start;
    printf("%Lf", elapsedTime);
}
