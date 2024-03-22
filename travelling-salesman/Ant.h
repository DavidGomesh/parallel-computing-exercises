#ifndef ANT_H_INCLUDED
#define ANT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../adt/graph/Vertex.h"
#include "../adt/list/List.h"
#include "PathInfo.h"
#include "../adt/tuple/Tuple.h"

#include "../utils/Printters.h"

typedef struct ant_type {
    char id[31];
    Vertex* location;
    List* paths; // Edges List
} Ant;

Ant* newAnt(char id[], Vertex* location, List* paths) {
    Ant* ant = (Ant*) malloc(sizeof(Ant));
    if (ant != NULL) {
        strcpy(ant->id, id);
        ant->location = location;
        ant->paths = paths;
    }
    return ant;
}

float* generatePossibilities(Ant* ant) {
    uint pathsSize = sizeList(ant->paths);

    float sumTxyNxy = 0.0;
    float* TxyNxyList = (float*) malloc(pathsSize * sizeof(float));
    float* possibilities = (float*) malloc(pathsSize * sizeof(float));

    for (uint i=0; i<pathsSize; i++) {
        Edge* edge = (Edge*) getListData(ant->paths, i);
        PathInfo* path = (PathInfo*) edge->data;

        float Txy = 1 / path->distance;
        float TxyNxy = Txy * path->pheromone;

        sumTxyNxy += TxyNxy;
        TxyNxyList[i] = TxyNxy;
    }

    for (uint i=0; i<pathsSize; i++) {
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