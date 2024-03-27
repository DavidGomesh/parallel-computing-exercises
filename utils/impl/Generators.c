#ifndef GENERATORS_C_INCLUDED
#define GENERATORS_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../../graph/Graph.h"
#include "../../graph/Vertex.h"

Graph* generateCities(int quant, int minDistance, int maxDistance) {
    int quantVert = quant * (quant - 1) / 2;
    Graph* graph = newGraph(quant, quantVert);

    for (int i=0; i<quant; i++) {
        char* cityName = (char*) malloc(31 * sizeof(char));
        snprintf(cityName, 31, "%s%d", "C", i);
        addVertex(graph, newVertex(cityName));
    }

    float weights[quantVert];
    for (int i=0; i<quantVert; i++) {
        weights[i] = (float) (rand() % maxDistance + minDistance);
    }

    connectAllVertices(graph, weights);
    return graph;
}

#endif // GENERATORS_C_INCLUDED