#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "Vertex.h"
#include "Edge.h"

typedef struct graph_type {
    size_t MAX_VERTICES;
    size_t MAX_EDGES;
    
    size_t quantVertices;
    size_t quantEdges;

    Vertex** vertices;
    Edge** edges;
} Graph;

Graph* newGraph(size_t MAX_VERTICES, size_t MAX_EDGES);

void addVertex(Graph* graph, Vertex* vertex);
void addEdge(Graph* graph, Edge* edge);

void connectAllVertices(Graph *graph, void* datas[]);
Edge** getEdgesByVertex(Graph* graph, Vertex* vertex);

void freeGraph(Graph* graph, void (*fvd)(void*), void (*fed)(void*));

void printGraph(Graph* graph, void (*fvd)(void*), void (*fed)(void*));

#endif // GRAPH_H_INCLUDED