#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include "../adt/graph/Vertex.h"

typedef struct type_path {
    Vertex* origin;
    Vertex* destination;
    float distance;
    float pheromone;
} Path;

Path* newPath(Vertex* origin, Vertex* destination, float distance, float pheromone);

void printPath(Path* path, void (*fv)(void*));

#endif // PATH_H_INCLUDED