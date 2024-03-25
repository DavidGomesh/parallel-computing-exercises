#ifndef PATH_C_INCLUDED
#define PATH_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../Path.h"

Path* newPath(float distance, float pheromone) {
    Path* path = (Path*) malloc(sizeof(Path));
    if (path != NULL) {
        path->distance = distance;
        path->pheromone = pheromone;
    }
    return path;
}

void printPath(Path* path) {
    if (path == NULL) {
        printf("[NULL Path]");
        return;
    }
    printf("Path(D=%.2f,P=%.2f)", path->distance, path->pheromone);
}

#endif // PATH_C_INCLUDED