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

void connectAllVertices(Graph *graph, void* datas[]) {
    if (graph == NULL) {
        return;
    }

    uint k=0;
    uint verticesListSize = sizeList(graph->vertices);
    for (uint i=0; i<verticesListSize; i++) {
        Vertex* first = (Vertex*) getListData(graph->vertices, i);

        for (uint j=i+1; j<verticesListSize; j++) {
            Vertex* second = (Vertex*) getListData(graph->vertices, j);
            addEdge(graph, newEdge(first, second, datas[k++]));
        }
    }
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

void printGraph(Graph* graph, void (*fvd)(void*), void (*fed)(void*)) {
    if (graph == NULL) {
        printf("[NULL Graph]");
    }
    printf("Graph(\n");

    printf("  Vertices:\n");
    for (uint i=0; i<sizeList(graph->vertices); i++) {
        Vertex* v = (Vertex*) getListData(graph->vertices, i);
        printf("\t");
        printVertex(v, fvd);
        printf("\n");
    }

    printf("  Edges:\n");
    for (uint i=0; i<sizeList(graph->edges); i++) {
        Edge* e = (Edge*) getListData(graph->edges, i);
        printf("\t");
        printEdge(e, fvd, fed);
        printf("\n");
    }

    printf(")");
}

#endif // GRAPH_C_INCLUDED