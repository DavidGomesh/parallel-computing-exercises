#ifndef FIELD_C_INCLUDED
#define FIELD_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Field.h"
#include "../Ant.h"
#include "../Path.h"

#include "../../adt/graph/Vertex.h"
#include "../../adt/graph/Edge.h"
#include "../../adt/graph/Graph.h"

#include "../../utils/Array.h"

Field* newField(Graph* graph) {
    if (graph == NULL) {
        return NULL;
    }

    Field* field = (Field*) malloc(sizeof(Field));
    if (field == NULL) {
        return NULL;
    }

    Ant** ants = (Ant**) newArray(graph->quantVertices, sizeof(Ant*));

    for (size_t i=0; i<graph->quantVertices; i++) {
        Vertex* location = graph->vertices[i];

        char id[31];
        snprintf(id, 31, "%s%lld", "Ant-", i);

        Ant* ant = newAnt(id, location);
        if (ant == NULL) {
            return NULL;
        }

        ants[i] = ant;
    }

    Path** paths = (Path**) newArray(graph->quantVertices * (graph->quantVertices - 1), sizeof(Path*));

    size_t j=0;
    for (size_t i=0; i<graph->quantEdges; i++) {
        Edge* edge = graph->edges[i];

        Path* path1 = newPath(edge->first, edge->second, edge->weight, 0.1, 0.0);
        Path* path2 = newPath(edge->second, edge->first, edge->weight, 0.1, 0.0);

        paths[j++] = path1;
        paths[j++] = path2;
    }

    field->ants = ants;
    field->paths = paths;

    return field;
}

void generateOdds(Field* field) {
    size_t antsSize = arraySize((void**) field->ants);

    for (size_t i=0; i<antsSize; i++) {
        Ant* ant = field->ants[i];

        Path** paths = pathsByOrigin(field->paths, ant->location);
        size_t pathsSize = arraySize((void**) paths);

        float sumTxyNxy = 0.0;
        for (size_t j=0; j<pathsSize; j++) {
            float TxyNxy = 1 / paths[j]->distance * paths[j]->pheromone;
            sumTxyNxy += TxyNxy;

            paths[j]->odd = TxyNxy;
        }

        for (size_t j=0; j<pathsSize; j++) {
            printf("O=%s,D=%s,TN=%f", paths[j]->origin->data, paths[j]->destination->data, paths[j]->odd);
            paths[j]->odd /= sumTxyNxy;
            printf("P=%f", paths[j]->odd);
            printf("\n");
        }

        printf("\n");
    }
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
    printf("  Paths:\n");
    for (size_t i=0; field->paths[i]!=NULL; i++) {
        printf("\t");
        printPath(field->paths[i], fv);
        printf("\n");
    }
    printf(")");
}

#endif // FIELD_C_INCLUDED