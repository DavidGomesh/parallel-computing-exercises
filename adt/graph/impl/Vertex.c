#ifndef VERTEX_C_INCLUDED
#define VERTEX_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../Vertex.h"

Vertex* newVertex(void* data) {
    Vertex* vertex = (Vertex*) malloc(sizeof(Vertex));
    if (vertex != NULL) {
        vertex->data = data;
    }
    return vertex;
}

void freeVertex(Vertex* vertex, void (*f)(void*)) {
    f(vertex->data);
    free(vertex);
}

void printVertex(Vertex* vertex, void (*f)(void*)) {
    if(vertex == NULL) {
        printf("[NULL Vertex]");
        return;
    }
    printf("V(d=");
    f(vertex->data);
    printf(")");
}

#endif // VERTEX_C_INCLUDED