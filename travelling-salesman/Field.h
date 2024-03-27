#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include "../graph/Graph.h"

#include "Ant.h"
#include "Path.h"
#include "Route.h"

typedef struct field_type {
    Ant** ants;
    Path** paths;

    Route** routes;
    Route* bestRoute;

    size_t quantAnts;
    size_t quantPaths;

    float EVAPORATION_RATE;
    float UPDATE_RATE;
} Field;

Field* newField(Graph* graph, float EVAPORATION_RATE, float UPDATE_RATE);

void generateOdds(Field* field);
void generateRoutes(Field* field);
void updatePheromones(Field* field);
void getBestRoute(Field* field);

void printField(Field* field, void (*fv)(void*));

#endif // FIELD_H_INCLUDED