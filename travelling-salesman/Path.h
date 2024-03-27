#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include "../graph/Vertex.h"

typedef struct type_path {
    Vertex* origin;
    Vertex* destination;
    float distance;
    float pheromone;
    float odd;
} Path;

Path* newPath(Vertex* origin, Vertex* destination, float distance, float pheromone, float odd);

Path** pathsByOrigin(Path** paths, Vertex* origin);
Path** pathsByOriginExceptDestinations(Path** paths, Vertex* origin, Vertex** exceptDestinations);

Path* pathByOriginAndDestination(Path** paths, Vertex* origin, Vertex* destination);
Path* choosePath(Path** paths);

void printPath(Path* path, void (*fv)(void*));

#endif // PATH_H_INCLUDED