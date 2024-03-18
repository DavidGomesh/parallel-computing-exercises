#ifndef VERTEX_C_INCLUDED
#define VERTEX_C_INCLUDED

#include <stdlib.h>
#include "../Vertex.h"

Vertex* newVertex(void* data) {
    Vertex* vertex = (Vertex*) malloc(sizeof(Vertex));
    if (vertex != NULL) {
        vertex->data = data;
    }
    return vertex;
}

#endif // VERTEX_C_INCLUDED