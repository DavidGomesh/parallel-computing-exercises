#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../adt/list/List.h"
#include "../adt/graph/Graph.h"
#include "Ant.h"

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
            free(field);
            return NULL;
        }

        List* vertices = graph->vertices;
        for (uint i=0; i<sizeList(vertices); i++) {
            Vertex* location = (Vertex*) getListData(vertices, i);
            List* paths = getEdgesByVertex(graph, location);

            char id[31];
            snprintf(id, 31, "%s%u", "Ant", i);

            Ant* ant = newAnt(id, location, paths);
            if (ant == NULL) {
                return NULL;
            }

            appendList(ants, ant);
        }

        field->ants = ants;
    }

    return field;
}

void printField(Field* field, void (*fv)(void*)) {
    if (field == NULL) {
        printf("[NULL Field]");
        return;
    }
    printf("Field (\n");
    printf("  Ants:\n");
    for (uint i=0; i<sizeList(field->ants); i++) {
        Ant* ant = (Ant*) getListData(field->ants, i);
        printf("\t");
        printAnt(ant, fv);
        printf("\n");
    }
    printf(")");
}

#endif // FIELD_H_INCLUDED