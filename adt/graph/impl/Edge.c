#ifndef EDGE_C_INCLUDED
#define EDGE_C_INCLUDED

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

#endif // EDGE_C_INCLUDED