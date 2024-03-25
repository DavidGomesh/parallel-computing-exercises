#ifndef ANT_H_INCLUDED
#define ANT_H_INCLUDED

#include "../adt/graph/Vertex.h"
#include "../adt/graph/Edge.h"

typedef struct ant_type {
    char id[31];
    Vertex* location;
    Edge** paths;
} Ant;

Ant* newAnt(char id[], Vertex* location, Edge** paths);

float* generatePossibilities(Ant* ant);

void printAnt(Ant* ant, void (*fl)(void*));

#endif // ANT_H_INCLUDED