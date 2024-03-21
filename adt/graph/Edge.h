#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

#include "Vertex.h"

typedef struct edge_type {
    Vertex* first;
    Vertex* second;
    void* data;
} Edge;

Edge* newEdge(Vertex* first, Vertex* second, void* data);

void printEdge(Edge* edge, void (*fv)(void*), void (*fd)(void*));

#endif // EDGE_H_INCLUDED