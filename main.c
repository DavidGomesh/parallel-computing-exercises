#include <stdio.h>

#include "adt/list/List.h"

typedef struct person_type {
    char name[31];
    int age;
} Person;

void printPerson(Person* person) {
    printf("Person(n=%s, a=%d)", person->name, person->age);
}

void testList();

int main() {
    testList();
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
