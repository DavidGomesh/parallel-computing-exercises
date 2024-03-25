#ifndef EDGE_C_INCLUDED
#define EDGE_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../Vertex.h"
#include "../Edge.h"

Edge* newEdge(Vertex* first, Vertex* second, float weight) {
    Edge* edge = (Edge*) malloc(sizeof(Edge));
    if(edge != NULL) {
        edge->first = first;
        edge->second = second;
        edge->weight = weight;
    }
    return edge;
}

void freeEdge(Edge* edge) {
    free(edge);
}

void printEdge(Edge* edge, void (*fv)(void*)) {
    if (edge == NULL) {
        printf("[NULL Edge]");
        return;
    }
    printf("E[F=");
    printVertex(edge->first, fv);
    printf(",S=");
    printVertex(edge->second, fv);
    printf(",W=%f]", edge->weight);
}

#endif // EDGE_C_INCLUDED