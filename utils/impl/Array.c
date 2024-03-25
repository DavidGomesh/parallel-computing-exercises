#ifndef ARRAY_C_INCLUDED
#define ARRAY_C_INCLUDED

#include <stdlib.h>

#include "../Array.h"

void** newArray(size_t quantElem, size_t elemSize) {
    void** array = malloc((quantElem + 1) * elemSize);
    if (array == NULL) {
        return NULL;
    }

    for (size_t i=0; i<quantElem+1; i++) {
        array[i] = NULL;
    }
    return array;
}

size_t arraySize(void** array) {
    size_t size = 0;
    while (array[size] != NULL) {
        size++;
    }
    return size;
}

#endif // ARRAY_C_INCLUDED