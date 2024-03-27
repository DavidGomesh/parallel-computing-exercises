#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

typedef struct vertex_type {
    void* data;
} Vertex;

Vertex* newVertex(void* data);

void freeVertex(Vertex* vertex, void (*f)(void*));

void printVertex(Vertex* vertex, void (*f)(void*));

#endif // VERTEX_H_INCLUDED