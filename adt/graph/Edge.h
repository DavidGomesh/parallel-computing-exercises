#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

#include "Vertex.h"

typedef struct edge_type {
    Vertex* first;
    Vertex* second;
    void* data;
} Edge;

Edge* newEdge(Vertex* first, Vertex* second, void* data);

#endif // EDGE_H_INCLUDED