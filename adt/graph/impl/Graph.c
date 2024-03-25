#ifndef GRAPH_C_INCLUDED
#define GRAPH_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../Graph.h"

#include "../../../utils/Array.h"

Graph* newGraph(size_t MAX_VERTICES, size_t MAX_EDGES) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    if (graph == NULL) {
        return NULL;
    }

    graph->vertices = (Vertex**) newArray(MAX_VERTICES, sizeof(Vertex*));
    if (graph->vertices == NULL) {
        return NULL;
    }

    graph->edges = (Edge**) newArray(MAX_EDGES, sizeof(Edge*));
    if (graph->edges == NULL) {
        return NULL;
    }
    
    graph->MAX_VERTICES = MAX_VERTICES;
    graph->MAX_EDGES = MAX_EDGES;
    graph->quantVertices = 0;
    graph->quantEdges = 0;

    return graph;
}

void addVertex(Graph* graph, Vertex* vertex) {
    graph->vertices[graph->quantVertices] = vertex;
    graph->quantVertices++;
}

void addEdge(Graph* graph, Edge* edge) {
    graph->edges[graph->quantEdges] = edge;
    graph->quantEdges++;
}

void connectAllVertices(Graph *graph, void* datas[]) {
    if (graph == NULL) {
        return;
    }

    size_t k=0;
    for (size_t i=0; i<graph->quantVertices; i++) {
        Vertex* first = graph->vertices[i];

        for (size_t j=i+1; j<graph->quantVertices; j++) {
            Vertex* second = graph->vertices[j];
            addEdge(graph, newEdge(first, second, datas[k++]));
        }
    }
}

Edge** getEdgesByVertex(Graph* graph, Vertex* vertex) {
    if (graph == NULL || vertex == NULL) {
        return NULL;
    }

    Edge** edges = (Edge**) newArray(graph->MAX_EDGES, sizeof(Edge*));
    if (edges == NULL) {
        return NULL;
    }

    size_t quantEdges = 0;
    for (size_t i=0; i<graph->quantEdges; i++) {
        Edge* edge = graph->edges[i];
        if (edge->first == vertex || edge->second == vertex) {
            edges[quantEdges++] = edge;
        }
    }

    return edges;
}

void freeGraph(Graph* graph, void (*fvd)(void*), void (*fed)(void*)) {
    if (graph == NULL) {
        return;
    }

    for (size_t i=0; i<graph->quantEdges; i++) {
        freeEdge(graph->edges[i], fed);
    }

    for (size_t i=0; i<graph->quantVertices; i++) {
        freeVertex(graph->vertices[i], fvd);
    }

    free(graph->vertices);
    free(graph->edges);
    free(graph);
}

void printGraph(Graph* graph, void (*fvd)(void*), void (*fed)(void*)) {
    if (graph == NULL) {
        printf("[NULL Graph]");
    }
    printf("Graph(\n");

    printf("  Vertices:\n");
    for (size_t i=0; i<graph->quantVertices; i++) {
        Vertex* v = graph->vertices[i];
        printf("\t");
        printVertex(v, fvd);
        printf("\n");
    }

    printf("  Edges:\n");
    for (size_t i=0; i<graph->quantEdges; i++) {
        Edge* e = graph->edges[i];
        printf("\t");
        printEdge(e, fvd, fed);
        printf("\n");
    }

    printf(")");
}

#endif // GRAPH_C_INCLUDED