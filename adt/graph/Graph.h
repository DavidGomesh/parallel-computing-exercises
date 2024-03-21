#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "../list/List.h"
#include "Vertex.h"
#include "Edge.h"

typedef struct graph_type {
    List* vertices;
    List* edges;
} Graph;

Graph* newGraph();

void addVertex(Graph* graph, Vertex* vertex);
void addEdge(Graph* graph, Edge* edge);

void connectAllVertices(Graph *graph, void* datas[]);
List* getEdgesByVertex(Graph* graph, Vertex* vertex);

#endif // GRAPH_H_INCLUDED