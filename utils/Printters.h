#ifndef PRINTTER_H_INCLUDED
#define PRINTTER_H_INCLUDED

#include <stdio.h>

void printStr(void* str) {
    char* s = (char*) str;
    printf("%s", s);
}

void printInt(void* integer) {
    int* i = (int*) integer;
    printf("%d", *i);
}

void printFloat(void* floating) {
    float* f = (float*) floating;
    printf("%.2f", *f);
}

#endif // PRINTTER_H_INCLUDED