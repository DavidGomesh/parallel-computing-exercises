#ifndef ANT_H_INCLUDED
#define ANT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../adt/graph/Vertex.h"
#include "../adt/graph/Edge.h"

#include "Path.h"

#include "../utils/Array.h"
#include "../utils/Printters.h"

typedef struct ant_type {
    char id[31];
    Vertex* location;
    Edge** paths;
} Ant;

Ant* newAnt(char id[], Vertex* location, Edge** paths) {
    Ant* ant = (Ant*) malloc(sizeof(Ant));
    if (ant != NULL) {
        strcpy(ant->id, id);
        ant->location = location;
        ant->paths = paths;
    }
    return ant;
}

float* generatePossibilities(Ant* ant) {
    size_t quantPaths = arraySize((void**) ant->paths);

    float sumTxyNxy = 0.0;
    float* TxyNxyList = (float*) malloc(quantPaths * sizeof(float));
    float* possibilities = (float*) malloc(quantPaths * sizeof(float));

    for (size_t i=0; i<quantPaths; i++) {
        Path* path = (Path*) ant->paths[i]->data;

        float Txy = 1 / path->distance;
        float TxyNxy = Txy * path->pheromone;

        sumTxyNxy += TxyNxy;
        TxyNxyList[i] = TxyNxy;
    }

    for (size_t i=0; i<quantPaths; i++) {
        possibilities[i] = TxyNxyList[i] / sumTxyNxy;
    }

    free(TxyNxyList);
    return possibilities;

}

void printAnt(Ant* ant, void (*fl)(void*)) {
    if (ant == NULL) {
        printf("[NULL Ant]");
        return;
    }
    printf("Ant(ID=");
    printStr(ant->id);
    printf(",L=");
    printVertex(ant->location, fl);
    printf(")");
}

#endif // ANT_H_INCLUDED