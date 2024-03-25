#ifndef PATH_C_INCLUDED
#define PATH_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../Path.h"

#include "../../utils/Array.h"

Path* newPath(Vertex* origin, Vertex* destination, float distance, float pheromone, float odd) {
    Path* path = (Path*) malloc(sizeof(Path));
    if (path != NULL) {
        path->origin = origin;
        path->destination = destination;
        path->distance = distance;
        path->pheromone = pheromone;
        path->odd = odd;
    }
    return path;
}

Path** pathsByOrigin(Path** paths, Vertex* origin, Path** excludedPaths) {
    size_t pathsSize = arraySize((void**) paths);

    Path** pathsWithOrigin = (Path**) newArray(pathsSize, sizeof(Path*));
    if (pathsByOrigin == NULL) {
        return NULL;
    }

    size_t j=0;
    for (size_t i=0; i<pathsSize; i++) {
        Path* path = paths[i];
        if (path->origin != origin || arrayContains((void**) excludedPaths, (void*) path)) {
            continue;
        }

        pathsWithOrigin[j++] = path;
    }

    return pathsWithOrigin;
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
    printf("D=%f,P=%f,O=%f)", path->distance, path->pheromone, path->odd);
}

#endif // PATH_C_INCLUDED