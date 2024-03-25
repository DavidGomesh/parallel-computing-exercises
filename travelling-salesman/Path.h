#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include "../adt/graph/Vertex.h"

typedef struct type_path {
    Vertex* origin;
    Vertex* destination;
    float distance;
    float pheromone;
    float odd;
} Path;

Path* newPath(Vertex* origin, Vertex* destination, float distance, float pheromone, float odd);

Path** pathsByOrigin(Path** paths, Vertex* origin, Path** excludedPaths);

void printPath(Path* path, void (*fv)(void*));

#endif // PATH_H_INCLUDED