#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

#include <stdlib.h>
#include <stdbool.h>

void** newArray(size_t quantElem, size_t elemSize);
size_t arraySize(void** array);
bool arrayContains(void** array, void* data);

#endif // ARRAY_H_INCLUDED