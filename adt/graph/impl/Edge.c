#ifndef EDGE_C_INCLUDED
#define EDGE_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../Vertex.h"
#include "../Edge.h"

Edge* newEdge(Vertex* first, Vertex* second, void* data) {
    Edge* edge = (Edge*) malloc(sizeof(Edge));
    if(edge != NULL) {
        edge->first = first;
        edge->second = second;
        edge->data = data;
    }
    return edge;
}

void printEdge(Edge* edge, void (*fv)(void*), void (*fd)(void*)) {
    if (edge == NULL) {
        printf("[NULL Edge]");
        return;
    }
    printf("E[F=");
    printVertex(edge->first, fv);
    printf(",S=");
    printVertex(edge->second, fv);
    printf(",D=");
    fd(edge->data);
    printf("]");
}

#endif // EDGE_C_INCLUDED