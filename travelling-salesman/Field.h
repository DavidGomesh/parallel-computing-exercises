#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include "../adt/graph/Graph.h"

#include "Ant.h"
#include "Path.h"
#include "Route.h"

typedef struct field_type {
    Ant** ants;
    Path** paths;
    size_t quantAnts;
    size_t quantPaths;
} Field;

Field* newField(Graph* graph);

void generateOdds(Field* field);
Route** generateRoutes(Field* field);

void printField(Field* field, void (*fv)(void*));

#endif // FIELD_H_INCLUDED