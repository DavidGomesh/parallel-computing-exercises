#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

typedef struct type_path {
    float distance;
    float pheromone;
} Path;

Path* newPath(float distance, float pheromone);

void printPath(Path* path);

#endif // PATH_H_INCLUDED