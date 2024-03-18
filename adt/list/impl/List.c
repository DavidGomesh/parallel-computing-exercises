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

#endif // LIST_C_INCLUDED