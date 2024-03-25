#ifndef TUPLE_C_INCLUDED
#define TUPLE_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../Tuple.h"

#include "../../../utils/Structure.h"


Tuple* newTuple(void* first, void* second) {
    Tuple* tuple = (Tuple*) newStructure(sizeof(Tuple));
    tuple->first = first;
    tuple->second = second;
    
    return tuple;
}

void freeTuple(Tuple* tuple) {
    free(tuple);
}

void printTuple(Tuple* tuple, void (*ff)(void*), void (*fs)(void*)) {
    if (tuple == NULL) {
        printf("[NULL Tuple]");
        return;
    }
    printf("Tuple(F=");
    ff(tuple->first);
    printf(",S=");
    fs(tuple->second);
    printf(")");
}

#endif // TUPLE_C_INCLUDED