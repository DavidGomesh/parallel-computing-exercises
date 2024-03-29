#ifndef ANT_H_INCLUDED
#define ANT_H_INCLUDED

#include "../graph/Vertex.h"
#include "../graph/Edge.h"

typedef struct ant_type {
    char id[31];
    Vertex* location;
} Ant;

Ant* newAnt(char id[], Vertex* location);

// float* generatePossibilities(Ant* ant);

void printAnt(Ant* ant, void (*fl)(void*));

#endif // ANT_H_INCLUDED