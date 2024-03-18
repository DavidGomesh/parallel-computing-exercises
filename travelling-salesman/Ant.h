#ifndef ANT_H_INCLUDED
#define ANT_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#include "../adt/graph/Vertex.h"
#include "../adt/list/List.h"

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

#endif // ANT_H_INCLUDED