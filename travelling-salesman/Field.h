#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../adt/graph/Vertex.h"
#include "../adt/graph/Edge.h"
#include "../adt/graph/Graph.h"

#include "Ant.h"

#include "../utils/Array.h"

typedef struct field_type {
    Ant** ants;
} Field;

Field* newField(Graph* graph) {
    if (graph == NULL) {
        return NULL;
    }

    Field* field = (Field*) malloc(sizeof(Field));
    if (field != NULL) {

        Ant** ants = (Ant**) newArray(graph->quantVertices, sizeof(Ant*));
        if (ants == NULL) {
            free(field);
            return NULL;
        }

        for (size_t i=0; i<graph->quantVertices; i++) {
            Vertex* location = graph->vertices[i];
            Edge** paths = getEdgesByVertex(graph, location);

            char id[31];
            snprintf(id, 31, "%s%lld", "Ant", i);

            Ant* ant = newAnt(id, location, paths);
            if (ant == NULL) {
                return NULL;
            }

            ants[i] = ant;
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
    for (size_t i=0; field->ants[i]!=NULL; i++) {
        printf("\t");
        printAnt(field->ants[i], fv);
        printf("\n");
    }
    printf(")");
}

#endif // FIELD_H_INCLUDED