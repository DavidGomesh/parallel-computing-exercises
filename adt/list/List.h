#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdbool.h>

#define uint unsigned

typedef struct list_type List;

List* newList();

void appendList(List* list, void* data);
void* getListData(List* list, uint index);

bool isEmptyList(List *list);
uint sizeList(List* list);

void printList(List* list, void (*f)(void*));

#endif // LIST_H_INCLUDED