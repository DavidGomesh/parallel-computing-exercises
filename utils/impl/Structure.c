#ifndef STRUCTURE_C_INCLUDED
#define STRUCTURE_C_INCLUDED

#include <stdlib.h>
#include "../Structure.h"

void* newStructure(size_t size) {
    void* structure = malloc(size);
    if (structure == NULL) {
        exit(ENOMEM);
    }
    return structure;
}

#endif // STRUCTURECH_INCLUDED