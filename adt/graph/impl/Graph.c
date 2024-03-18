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

List* getEdgesByVertex(Graph* graph, Vertex* vertex) {
    if (graph == NULL || vertex == NULL) {
        return NULL;
    }

    List* edges = newList();
    if (edges == NULL) {
        return NULL;
    }

    for (uint i=0; i<sizeList(graph->edges); i++) {
        Edge* edge = (Edge*) getListData(graph->edges, i);
        if (edge->first == vertex || edge->second == vertex) {
            appendList(edges, edge);
        }
    }

    return edges;
}

#endif // GRAPH_C_INCLUDED