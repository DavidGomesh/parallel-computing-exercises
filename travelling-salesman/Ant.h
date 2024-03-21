#ifndef ANT_H_INCLUDED
#define ANT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../adt/graph/Vertex.h"
#include "../adt/list/List.h"
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