#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../adt/list/List.h"
#include "Ant.h"
#include "../adt/graph/Graph.h"

typedef struct field_type {
    List* ants; // Ants list
} Field;

Field* newField(Graph* graph) {
    if (graph == NULL) {
        return NULL;
    }

    Field* field = (Field*) malloc(sizeof(Field));
    if (field != NULL) {

        List* ants = newList();
        if (ants == NULL) {
            return NULL;
        }

        List* vertices = graph->vertices;
        for (uint i=0; sizeList(vertices); i++) {
            Vertex* location = (Vertex*) getListData(vertices, i);
            List* paths = getEdgesByVertex(graph, location);

            char id[31];
            sprintf(id, "%u", i);
            strcat("Ant", id);

            Ant* ant = newAnt(id, location, paths);
        }
    }

    return field;
}

#endif // FIELD_H_INCLUDED