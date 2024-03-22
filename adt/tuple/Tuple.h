#ifndef TUPLE_H_INCLUDED
#define TUPLE_H_INCLUDED

typedef struct type_tuple {
    void* first;
    void* second;
} Tuple;

Tuple* newTuple(void* first, void* second);

void freeTuple(Tuple* tuple);

void printTuple(Tuple* tuple, void (*ff)(void*), void (*fs)(void*));

#endif // TUPLE_H_INCLUDED