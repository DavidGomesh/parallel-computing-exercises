#ifndef PATH_INFO_H_INCLUDED
#define PATH_INFO_H_INCLUDED

#include <stdlib.h>

typedef struct type_path_info {
    float distance;
    float pheromone;
} PathInfo;

PathInfo* newPathInfo(float distance, float pheromone) {
    PathInfo* pathInfo = (PathInfo*) malloc(sizeof(PathInfo));
    if (pathInfo != NULL) {
        pathInfo->distance = distance;
        pathInfo->pheromone = pheromone;
    }
    return pathInfo;
}

void printPathInfo(PathInfo* pathInfo) {
    if (pathInfo == NULL) {
        printf("[NULL PathInfo]");
        return;
    }
    printf("PathInfo(D=%.2f,P=%.2f)", pathInfo->distance, pathInfo->pheromone);
}

#endif // PATH_INFO_H_INCLUDED