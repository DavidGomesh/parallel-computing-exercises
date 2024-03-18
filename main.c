#include <stdio.h>

#include "adt/list/List.h"
#include "adt/graph/Graph.h"
#include "adt/graph/Vertex.h"
#include "adt/graph/Edge.h"

typedef struct person_type {
    char name[31];
    int age;
} Person;

void printPerson(Person* person) {
    printf("Person(n=%s, a=%d)", person->name, person->age);
}

void testList();
void testGraph();

int main() {
    testList();
    testGraph();
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

    Edge* e1 = newEdge(v1, v2, 25.0);
    Edge* e2 = newEdge(v1, v3, 26.0);
    Edge* e3 = newEdge(v2, v3, 27.0);

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
        printf("F: %s\tS: %s\tW: %.2f\n", (char*) edge->first->data, (char*) edge->second->data, edge->weight);
    }
}
