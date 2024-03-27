#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

#include "Vertex.h"

typedef struct edge_type {
    Vertex* first;
    Vertex* second;
    float weight;
} Edge;

Edge* newEdge(Vertex* first, Vertex* second, float weight);

void freeEdge(Edge* edge);

void printEdge(Edge* edge, void (*fv)(void*));

#endif // EDGE_H_INCLUDED