#include <stdio.h>

#include "adt/list/List.h"

#include "adt/graph/Graph.h"
#include "adt/graph/Vertex.h"
#include "adt/graph/Edge.h"

#include "travelling-salesman/Field.h"
#include "travelling-salesman/Ant.h"
#include "travelling-salesman/PathInfo.h"

typedef struct person_type {
    char name[31];
    int age;
} Person;

void printPerson(void* person) {
    Person* p = (Person*) person;
    printf("Person(n=%s, a=%d)", p->name, p->age);
}

void printStr(void* str) {
    char* s = (char*) str;
    printf("%s", s);
}

void printInt(void* integer) {
    int* i = (int*) integer;
    printf("%d", *i);
}

void printFloat(void* floating) {
    float* f = (float*) floating;
    printf("%.2f", *f);
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
    printList(list, printPerson);

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

    printGraph(graph, printStr, printFloat);
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

    printGraph(graph, printStr, printInt);
}

void testField() {
    printf("TEST FIELD\n\n");

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

    connectAllVertices(graph, (void**) (PathInfo*[]) {
        newPathInfo(22.0, 0.1), newPathInfo(50.0, 0.1), newPathInfo(48.0, 0.1), newPathInfo(29.0, 0.1),
        newPathInfo(30.0, 0.1), newPathInfo(34.0, 0.1), newPathInfo(32.0, 0.1),
        newPathInfo(22.0, 0.1), newPathInfo(23.0, 0.1),
        newPathInfo(35.0, 0.1)
    });

    Field* field = newField(graph);

    for (uint i=0; i<sizeList(field->ants); i++) {
        Ant* ant = (Ant*) getListData(field->ants, i);
        printf("ID: %s\tL: %s\n", ant->id, (char*) ant->location->data);
    }
}
