#ifndef PRINTTER_C_INCLUDED
#define PRINTTER_C_INCLUDED

#include <stdio.h>

#include "../Printters.h"

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

#endif // PRINTTER_C_INCLUDED