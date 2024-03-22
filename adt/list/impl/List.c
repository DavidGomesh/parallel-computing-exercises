#ifndef LIST_C_INCLUDED
#define LIST_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../List.h"

typedef struct node_type {
    void* data;
    struct node_type* next;
} Node;

Node* newNode(void* data, Node* next) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (node != NULL) {
        node->data = data;
        node->next = next;
    }
    return node;
}

void printNode(Node* node, void (*f)(void*)) {
    if (node == NULL) {
        printf("[NULL Node]");
        return;
    }
    printf("Node[d=");
    f(node->data);
    printf(",n=");
    printNode(node->next, f);
    printf("]");
}

struct list_type {
    Node* first;
    uint size;
};

List* newList() {
    List* list = (List*) malloc(sizeof(List));
    if (list != NULL) {
        list->first = NULL;
        list->size = 0;
    }
    return list;
}

void appendList(List* list, void* data) {
    if (list == NULL) {
        return;
    }

    Node* node = newNode(data, NULL);
    if (node == NULL) {
        return;
    }

    if (isEmptyList(list)) {
        list->first = node;
    } else {
        Node* last = list->first;
        while(last->next != NULL) {
            last = last->next;
        }

        last->next = node;
    }

    list->size++;
}

void* getListData(List* list, uint index) {
    if (list == NULL || index >= list->size) {
        return NULL;
    }

    Node* node = list->first;
    for (uint i=0; i<index; i++) {
        node = node->next;
    }

    return node->data;
}

bool isEmptyList(List *list) {
    return list->first == NULL;
}

uint sizeList(List* list) {
    return list->size;
}

void freeList(List* list, void (*f)(void*)) {
    if (list == NULL) {
        return;
    }

    Node* freedNode;
    Node* node = list->first;

    while(node != NULL) {
        freedNode = node;
        node = node->next;
        
        f(freedNode->data);
        free(freedNode);
    }

    free(list);
}

void printList(List* list, void (*f)(void*)) {
    if (list == NULL) {
        printf("[NULL List]");
        return;
    }
    printf("List(");
    printNode(list->first, f);
    printf(")");
}

#endif // LIST_C_INCLUDED