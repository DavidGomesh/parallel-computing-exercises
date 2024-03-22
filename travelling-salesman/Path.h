#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include <stdlib.h>

typedef struct type_path {
    float distance;
    float pheromone;
} Path;

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

#endif // PATH_H_INCLUDED