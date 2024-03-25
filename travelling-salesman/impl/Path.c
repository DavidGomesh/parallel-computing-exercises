#ifndef PATH_C_INCLUDED
#define PATH_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../Path.h"

Path* newPath(Vertex* origin, Vertex* destination, float distance, float pheromone) {
    Path* path = (Path*) malloc(sizeof(Path));
    if (path != NULL) {
        path->origin = origin;
        path->destination = destination;
        path->distance = distance;
        path->pheromone = pheromone;
    }
    return path;
}

void printPath(Path* path, void (*fv)(void*)) {
    if (path == NULL) {
        printf("[NULL Path]");
        return;
    }
    printf("Path(OR=");
    printVertex(path->origin, fv);
    printf("DE=");
    printVertex(path->destination, fv);
    printf("D=%.2f,P=%.2f)", path->distance, path->pheromone);
}

#endif // PATH_C_INCLUDED