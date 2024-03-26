#ifndef GENERATORS_C_INCLUDED
#define GENERATORS_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../../adt/graph/Graph.h"
#include "../../adt/graph/Vertex.h"

Graph* generateCities(int quant, int minDistance, int maxDistance) {
    int quantVert = quant * (quant - 1) / 2;
    Graph* graph = newGraph(quant, quantVert);

    for (int i=0; i<quant; i++) {
        char cityName[31];
        snprintf(cityName, 31, "%s%d", "City", i);
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