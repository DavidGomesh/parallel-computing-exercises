#include <stdio.h>

#include "adt/list/List.h"

#include "adt/graph/Graph.h"
#include "adt/graph/Vertex.h"
#include "adt/graph/Edge.h"

#include "travelling-salesman/Field.h"
#include "travelling-salesman/Ant.h"

typedef struct person_type {
    char name[31];
    int age;
} Person;

void printPerson(Person* person) {
    printf("Person(n=%s, a=%d)", person->name, person->age);
}

void testList();
void testGraph();
void testGetEdgesByVertex();
void testConnectAllVertices();
void testField();

int main() {
    // testList();
    // testGraph();
    // testGetEdgesByVertex();
    testConnectAllVertices();
    // testField();
    return 0;
}

void testList() {
    printf("LIST TESTS\n\n");

    List* list = newList();
    appendList(list, &(Person) {"David", 22});
    appendList(list, &(Person) {"Carla", 23});
    appendList(list, &(Person) {"Pedro", 24});

    printf("PRINT LIST\n");
    for (unsigned i=0; i<sizeList(list); i++) {
        printPerson((Person*) getListData(list, i));
        printf("\n");
    }

    printf("\n");
}

void testGraph() {
    printf("GRAPH TEST\n\n");

    Vertex* v1 = newVertex("City01");
    Vertex* v2 = newVertex("City02");
    Vertex* v3 = newVertex("City03");

    Edge* e1 = newEdge(v1, v2, &(float){25.0});
    Edge* e2 = newEdge(v1, v3, &(float){26.0});
    Edge* e3 = newEdge(v2, v3, &(float){27.0});

    Graph* graph = newGraph();
    
    addVertex(graph, v1);
    addVertex(graph, v2);
    addVertex(graph, v3);
    
    addEdge(graph, e1);
    addEdge(graph, e2);
    addEdge(graph, e3);

    printf("PRINT VERTICES\n");
    for (unsigned i=0; i<sizeList(graph->vertices); i++) {
        printf("V: %s\n", (char*) ((Vertex*) getListData(graph->vertices, i))->data);
    }

    printf("\n\n");

    printf("PRINT EDGES\n");
    for (unsigned i=0; i<sizeList(graph->edges); i++) {
        Edge* edge = (Edge*) getListData(graph->edges, i);
        printf("F: %s\tS: %s\tW: %.2f\n", (char*) edge->first->data, (char*) edge->second->data, *(float*) edge->data);
    }
}

void testGetEdgesByVertex() {
    Vertex* v1 = newVertex("City01");
    Vertex* v2 = newVertex("City02");
    Vertex* v3 = newVertex("City03");
    Vertex* v4 = newVertex("City04");
    Vertex* v5 = newVertex("City05");

    Edge* e1 = newEdge(v1, v2, &(float){25.0});
    Edge* e2 = newEdge(v1, v3, &(float){26.0});
    Edge* e3 = newEdge(v2, v3, &(float){27.0});
    Edge* e4 = newEdge(v2, v4, &(float){27.0});
    Edge* e5 = newEdge(v2, v5, &(float){27.0});

    Graph* graph = newGraph();
    
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

    List* edges = getEdgesByVertex(graph, v5);
    for (unsigned i=0; i<sizeList(edges); i++) {
        Edge* edge = (Edge*) getListData(edges, i);
        printf("F: %s\tS: %s\tW: %.2f\n", (char*) edge->first->data, (char*) edge->second->data, *(float*) edge->data);
    }
}

void testConnectAllVertices() {
    Vertex* v1 = newVertex("City00");
    Vertex* v2 = newVertex("City01");
    Vertex* v3 = newVertex("City02");
    Vertex* v4 = newVertex("City03");
    Vertex* v5 = newVertex("City04");

    Graph* graph = newGraph();

    addVertex(graph, v1);
    addVertex(graph, v2);
    addVertex(graph, v3);
    addVertex(graph, v4);
    addVertex(graph, v5);

    connectAllVertices(graph, (void**) (int*[]) {
        &(int){22}, &(int){50}, &(int){48}, &(int){29},
        &(int){30}, &(int){34}, &(int){32},
        &(int){22}, &(int){23},
        &(int){35}
    });

    printf("FDS: %d\n", sizeList(graph->vertices));

    printf("PRINT EDGES\n");
    for (unsigned i=0; i<sizeList(graph->edges); i++) {
        Edge* edge = (Edge*) getListData(graph->edges, i);
        printf("F: %s\tS: %s\tW: %d\n", (char*) edge->first->data, (char*) edge->second->data, *(int*) edge->data);
    }
}

// void testField() {
//     printf("TEST FIELD\n\n");

//     Vertex* v1 = newVertex("City00");
//     Vertex* v2 = newVertex("City01");
//     Vertex* v3 = newVertex("City02");
//     Vertex* v4 = newVertex("City03");
//     Vertex* v5 = newVertex("City04");

//     Graph* graph = newGraph();

//     addVertex(graph, v1);
//     addVertex(graph, v2);
//     addVertex(graph, v3);
//     addVertex(graph, v4);
//     addVertex(graph, v5);

//     connectAllVertices(graph, (float[]) {
//         22, 50, 48, 29,
//         30, 34, 32,
//         22, 23,
//         35
//     });

//     Field* field = newField(graph);

//     for (uint i=0; i<sizeList(field->ants); i++) {
//         Ant* ant = (Ant*) getListData(field->ants, i);
//         printf("ID: %s\tL: %s\n", ant->id, (char*) ant->location->data);

//     }
// }
