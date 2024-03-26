#ifndef ROUTE_H_INCLUDED
#define ROUTE_H_INCLUDED

#include "Path.h"

typedef struct type_route {
    Path** paths;
    float distance;
} Route;

Route* newRoute(Path** paths);

float getTotalPheromoneDeposited(Route** routes, Path* path, float UPDATE_RATE);
Route* getBestRoute(Route** routes);

#endif // ROUTE_H_INCLUDED