#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "adt/graph/Graph.h"
#include "adt/graph/Vertex.h"
#include "adt/graph/Edge.h"

#include "adt/tuple/Tuple.h"

#include "travelling-salesman/Field.h"
#include "travelling-salesman/Ant.h"
#include "travelling-salesman/Path.h"
#include "travelling-salesman/Route.h"

#include "utils/Array.h"
#include "utils/Printters.h"
#include "utils/Generators.h"

typedef struct person_type {
    char name[31];
    int age;
} Person;

void printPerson(void* person) {
    Person* p = (Person*) person;
    printf("Person(n=%s, a=%d)", p->name, p->age);
}

void testGraph();
void testGetEdgesByVertex();
void testConnectAllVertices();
void testTulpe();
void testField();
void testAlgorithm();

int main() {
    srand(time(NULL));
    // testList();
    // testGraph();
    // testGetEdgesByVertex();
    // testConnectAllVertices();
    // testTulpe();
    // testField();
    testAlgorithm();
    printf("\n\nThe end.");
    return 0;
}

void testGraph() {
    printf("GRAPH TEST\n\n");

    Vertex* v1 = newVertex("City01");
    Vertex* v2 = newVertex("City02");
    Vertex* v3 = newVertex("City03");

    Edge* e1 = newEdge(v1, v2, 25.0);
    Edge* e2 = newEdge(v1, v3, 26.0);
    Edge* e3 = newEdge(v2, v3, 27.0);

    Graph* graph = newGraph(3, 3);
    
    addVertex(graph, v1);
    addVertex(graph, v2);
    addVertex(graph, v3);
    
    addEdge(graph, e1);
    addEdge(graph, e2);
    addEdge(graph, e3);

    printGraph(graph, printStr);
}

void testGetEdgesByVertex() {
    Vertex* v1 = newVertex("City01");
    Vertex* v2 = newVertex("City02");
    Vertex* v3 = newVertex("City03");
    Vertex* v4 = newVertex("City04");
    Vertex* v5 = newVertex("City05");

    Edge* e1 = newEdge(v1, v2, 25.0);
    Edge* e2 = newEdge(v1, v3, 26.0);
    Edge* e3 = newEdge(v2, v3, 27.0);
    Edge* e4 = newEdge(v2, v4, 27.0);
    Edge* e5 = newEdge(v2, v5, 27.0);

    Graph* graph = newGraph(5, 5);
    
    addVertex(graph, v1);
    addVertex(graph, v2);
    addVertex(graph, v3);
    addVertex(graph, v4);
    addVertex(graph, v5);

    addEdge(graph, e1);
    addEdge(graph, e2);
    addEdge(graph, e3);
    addEdge(graph, e4);
    addEdge(graph, e5);

    Edge** edges = getEdgesByVertex(graph, v1);
    for (unsigned i=0; edges[i]!=NULL; i++) {
        Edge* edge = edges[i];
        printEdge(edge, printStr);
    }
}

void testConnectAllVertices() {
    Vertex* v1 = newVertex("City00");
    Vertex* v2 = newVertex("City01");
    Vertex* v3 = newVertex("City02");
    Vertex* v4 = newVertex("City03");
    Vertex* v5 = newVertex("City04");

    Graph* graph = newGraph(5, 10);

    addVertex(graph, v1);
    addVertex(graph, v2);
    addVertex(graph, v3);
    addVertex(graph, v4);
    addVertex(graph, v5);

    connectAllVertices(graph, (float[]) {
        22.0, 50.0, 48.0, 29.0,
        30.0, 34.0, 32.0,
        22.0, 23.0,
        35.0
    });

    printGraph(graph, printStr);
}

void testTulpe() {
    Tuple* tuple = newTuple("One", &(int){1});
    printTuple(tuple, printStr, printInt);
}

void testField() {
    printf("TEST FIELD\n\n");

    Vertex* v1 = newVertex("City-A");
    Vertex* v2 = newVertex("City-B");
    Vertex* v3 = newVertex("City-C");
    Vertex* v4 = newVertex("City-D");
    Vertex* v5 = newVertex("City-E");

    Graph* graph = newGraph(5, 10);

    addVertex(graph, v1);
    addVertex(graph, v2);
    addVertex(graph, v3);
    addVertex(graph, v4);
    addVertex(graph, v5);

    connectAllVertices(graph, (float[]) {
        22.0, 50.0, 48.0, 29.0,
        30.0, 34.0, 32.0,
        22.0, 23.0,
        35.0
    });

    Field* field = newField(graph, 0.01, 10.0);

    for (size_t i=0; i<field->quantPaths; i++) {
        printPath(field->paths[i], printStr);
        printf("\n");
    }
    printf("\n\n");

    for (int i=0; i<9000; i++) {
        generateOdds(field);
        Route** routes = generateRoutes(field);
        evaporatePheromones(field);
        updatePheromones(field, routes);

        if (i == 9000 - 1) {
            for (size_t i=0; i<arraySize((void**) routes); i++) {
                printf("ROUTE\n");
                printf("Distance: %f\n", routes[i]->distance);
                for (size_t j=0; j<arraySize((void**) routes[i]->paths); j++) {
                    printPath(routes[i]->paths[j], printStr);
                    printf("\n");
                }
                printf("\n");
            }
        }
    }


    for (size_t i=0; i<field->quantPaths; i++) {
        printPath(field->paths[i], printStr);
        printf("\n");
    }
    printf("\n\n");

    // for (size_t i=0; i<arraySize((void**) field->ants); i++) {
    //     Ant* ant = field->ants[i];
    //     float* possibilities = generatePossibilities(ant);
    //     printAnt(ant, printStr);
    //     printf("\n");

    //     for (size_t j=0; j<arraySize((void**) ant->paths); j++) {
    //         Edge* path = ant->paths[j];

    //         printf("P=");
    //         printEdge(path, printStr, (void(*)(void*)) printPath);
    //         printf(",%%=%f\n", possibilities[j]);
    //     }

    //     printf("\n");
    // }
}

void testAlgorithm() {
    // printField(field, printStr);
    // Graph* graph = newGraph(5, 10);

    // addVertex(graph, newVertex("A"));
    // addVertex(graph, newVertex("B"));
    // addVertex(graph, newVertex("C"));
    // addVertex(graph, newVertex("D"));
    // addVertex(graph, newVertex("E"));

    // connectAllVertices(graph, (float[]) {
    //     22.0, 50.0, 48.0, 29.0,
    //     30.0, 34.0, 32.0,
    //     22.0, 23.0,
    //     35.0
    // });

    // Field* field = newField(graph, 0.01, 10.0);

    Field* field = newField(generateCities(40, 1, 100), 0.01, 10);
    int quant = 1000;
    Route* currentBest = NULL;

    for (int i=0; i<quant; i++) {
        generateOdds(field);
        Route** routes = generateRoutes(field);
        evaporatePheromones(field);
        updatePheromones(field, routes);
        Route* best = getBestRoute(routes);

        if (i == 0 || best->distance < currentBest->distance) {
            float difference = currentBest == NULL ? 0.0 : best->distance - currentBest->distance;
            currentBest = best;
            printf("\n\nBest route: I=%d,D=%.2f (%.2f)\n", i, best->distance, difference);
            for (size_t i=0; i<arraySize((void**) best->paths); i++) {
                printf("%s ", (char *) best->paths[i]->origin->data);
            }
        }



        


        // if (i == quant - 1) {
        //     for (size_t i=0; i<arraySize((void**) routes); i++) {
        //         printf("ROUTE\n");
        //         printf("Distance: %f\n", routes[i]->distance);
        //         for (size_t j=0; j<arraySize((void**) routes[i]->paths); j++) {
        //             printPath(routes[i]->paths[j], printStr);
        //             printf("\n");
        //         }
        //         printf("\n");
        //     }
        // }
    }
}
