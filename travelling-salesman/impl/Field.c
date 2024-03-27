#ifndef FIELD_C_INCLUDED
#define FIELD_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#include "../Field.h"
#include "../Ant.h"
#include "../Path.h"
#include "../Route.h"

#include "../../adt/graph/Vertex.h"
#include "../../adt/graph/Edge.h"
#include "../../adt/graph/Graph.h"

#include "../../utils/Array.h"
#include "../../utils/Structure.h"

#define INITIAL_PHEROMONE 0.01
#define INITIAL_ODD       0.00

Field* newField(Graph* graph, float EVAPORATION_RATE, float UPDATE_RATE) {
    if (graph == NULL) {
        return NULL;
    }

    Field* field = (Field*) newStructure(sizeof(Field));
    field->quantAnts = graph->quantVertices;
    field->quantPaths = graph->quantVertices * (graph->quantVertices - 1);
    
    field->EVAPORATION_RATE = EVAPORATION_RATE;
    field->UPDATE_RATE = UPDATE_RATE;

    Ant** ants = (Ant**) newArray(field->quantAnts, sizeof(Ant*));

    for (size_t i=0; i<graph->quantVertices; i++) {
        Vertex* location = graph->vertices[i];

        char id[31];
        snprintf(id, 31, "%s%lld", "Ant-", i);

        Ant* ant = newAnt(id, location);

        ants[i] = ant;
    }

    Path** paths = (Path**) newArray(field->quantPaths, sizeof(Path*));

    size_t j=0;
    for (size_t i=0; i<graph->quantEdges; i++) {
        Edge* edge = graph->edges[i];

        Path* path1 = newPath(edge->first, edge->second, edge->weight, INITIAL_PHEROMONE, INITIAL_ODD);
        Path* path2 = newPath(edge->second, edge->first, edge->weight, INITIAL_PHEROMONE, INITIAL_ODD);

        paths[j++] = path1;
        paths[j++] = path2;
    }

    field->ants = ants;
    field->paths = paths;

    field->routes = NULL;
    field->bestRoute = NULL;

    return field;
}

void generateOdds(Field* field) {
    #pragma omp parallel for
    for (size_t i=0; i<field->quantAnts; i++) {
        Ant* ant = field->ants[i];

        Path** paths = pathsByOrigin(field->paths, ant->location);
        size_t pathsSize = arraySize((void**) paths);

        float sumTxyNxy = 0.0;
        for (size_t j=0; j<pathsSize; j++) {
            float TxyNxy = 1 / paths[j]->distance * paths[j]->pheromone;
            sumTxyNxy += TxyNxy;

            paths[j]->odd = TxyNxy;
        }

        for (size_t j=0; j<pathsSize; j++) {
            paths[j]->odd = (paths[j]->odd / sumTxyNxy) * 100;
        }
    }
}

void generateRoutes(Field* field) {
    Route** routes = (Route**) newArray(field->quantAnts, sizeof(Route*));

    #pragma omp parallel for
    for (size_t i=0; i<field->quantAnts; i++) {

        Vertex* currentLocation = field->ants[i]->location;
        Vertex** excludedDestinations = (Vertex**) newArray(field->quantAnts, sizeof(Vertex*));

        Path** routePaths = (Path**) newArray(field->quantAnts, sizeof(Path*));
        for (size_t j=0; j<field->quantAnts; j++) {

            if (j == field->quantAnts-1) {
                routePaths[j] = pathByOriginAndDestination(field->paths, currentLocation, excludedDestinations[0]);
                continue;
            }

            Path** paths = pathsByOriginExceptDestinations(field->paths, currentLocation, excludedDestinations);
            Path* choosenPath = choosePath(paths);

            currentLocation = choosenPath->destination;
            excludedDestinations[j] = choosenPath->origin;
            routePaths[j] = choosenPath;

            free(paths);
        }

        routes[i] = (Route*) newRoute(routePaths);
        free(excludedDestinations);
    }

    field->routes = routes;
}

float getTotalPherDep(Field* field, Path* path) {
    float totalPherDep = 0.0;
    for (size_t i=0; i<field->quantAnts; i++) {
        if (arrayContains((void**) field->routes[i]->paths, (void*) path)) {
            totalPherDep += (field->UPDATE_RATE / field->routes[i]->distance);
        }
    }

    return totalPherDep;
}

void updatePheromones(Field* field) {
    #pragma omp parallel for
    for (size_t i=0; i<field->quantPaths; i++) {
        field->paths[i]->pheromone *= (1 - field->EVAPORATION_RATE);
        field->paths[i]->pheromone += getTotalPherDep(field, field->paths[i]);
    }
}

void getBestRoute(Field* field) {
    size_t totalRoutes = arraySize((void**) field->routes);

    for (size_t i=0; i<totalRoutes; i++) {
        if (i == 0 || field->routes[i]->distance < field->bestRoute->distance) {
            field->bestRoute = field->routes[i];
        }
    }
}

void printField(Field* field, void (*fv)(void*)) {
    if (field == NULL) {
        printf("[NULL Field]");
        return;
    }
    printf("Field (\n");
    printf("  Ants:\n");
    for (size_t i=0; field->ants[i]!=NULL; i++) {
        printf("\t");
        printAnt(field->ants[i], fv);
        printf("\n");
    }
    printf("  Paths:\n");
    for (size_t i=0; field->paths[i]!=NULL; i++) {
        printf("\t");
        printPath(field->paths[i], fv);
        printf("\n");
    }
    printf(")");
}

#endif // FIELD_C_INCLUDED