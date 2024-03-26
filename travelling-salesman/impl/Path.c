#ifndef PATH_C_INCLUDED
#define PATH_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../Path.h"

#include "../../utils/Array.h"
#include "../../utils/Structure.h"

Path* newPath(Vertex* origin, Vertex* destination, float distance, float pheromone, float odd) {
    Path* path = (Path*) newStructure(sizeof(Path));
    path->origin = origin;
    path->destination = destination;
    path->distance = distance;
    path->pheromone = pheromone;
    path->odd = odd;
    
    return path;
}

Path** pathsByOrigin(Path** paths, Vertex* origin) {
    size_t pathsSize = arraySize((void**) paths);

    Path** pathsWithOrigin = (Path**) newArray(pathsSize, sizeof(Path*));

    size_t j=0;
    for (size_t i=0; i<pathsSize; i++) {
        Path* path = paths[i];
        if (path->origin != origin) {
            continue;
        }

        pathsWithOrigin[j++] = path;
    }

    return pathsWithOrigin;
}

Path** pathsByOriginExceptDestinations(Path** paths, Vertex* origin, Vertex** exceptDestinations) {
    size_t pathsSize = arraySize((void**) paths);
    Path** pathsWithOrigin = (Path**) newArray(pathsSize, sizeof(Path*));

    size_t j=0;
    for (size_t i=0; i<pathsSize; i++) {
        Path* path = paths[i];
        if (path->origin == origin && !arrayContains((void**) exceptDestinations, (void*) path->destination)) {
            pathsWithOrigin[j++] = path;
        }
    }

    return pathsWithOrigin;
}

Path* pathByOriginAndDestination(Path** paths, Vertex* origin, Vertex* destination) {
    size_t pathsSize = arraySize((void**) paths);
    
    for (size_t i=0; i<pathsSize; i++) {
        if (paths[i]->origin == origin && paths[i]->destination == destination) {
            return paths[i];
        }
    }

    return NULL;
}

Path* choosePath(Path** paths) {
    size_t size = arraySize((void**) paths);

    int weightSum = 0;
    for (size_t i=0; i<size; i++){
        weightSum += ceil(paths[i]->odd);
    }

    int randNum = rand() % weightSum;
    for (size_t i=0; i<size; i++){
        randNum -= paths[i]->odd;

        if (randNum <= 0) {
            return paths[i];
        }
    }

    return NULL;
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