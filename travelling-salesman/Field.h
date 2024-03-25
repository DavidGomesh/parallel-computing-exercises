#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include "../adt/graph/Graph.h"

#include "Ant.h"

typedef struct field_type {
    Ant** ants;
} Field;

Field* newField(Graph* graph);

void printField(Field* field, void (*fv)(void*));

#endif // FIELD_H_INCLUDED