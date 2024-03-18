#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

typedef struct vertex_type {
    void* data;
} Vertex;

Vertex* newVertex(void* data);

#endif // VERTEX_H_INCLUDED