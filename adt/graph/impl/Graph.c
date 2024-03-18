#ifndef GRAPH_C_INCLUDED
#define GRAPH_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../Graph.h"
#include "../../list/List.h"

Graph* newGraph() {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    if (graph != NULL) {
        graph->vertices = newList();
        graph->edges = newList();
    }
    return graph;
}

void addVertex(Graph* graph, Vertex* vertex) {
    appendList(graph->vertices, vertex);
}

void addEdge(Graph* graph, Edge* edge) {
    appendList(graph->edges, edge);
}

#endif // GRAPH_C_INCLUDED