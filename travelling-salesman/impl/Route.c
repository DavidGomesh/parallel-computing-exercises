#ifndef ROUTE_C_INCLUDED
#define ROUTE_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "../Route.h"
#include "../Path.h"

#include "../../utils/Array.h"
#include "../../utils/Structure.h"
#include "../../utils/Printters.h"

Route* newRoute(Path** paths) {
    Route* route = (Route*) newStructure(sizeof(Route));
    route->paths = paths;
    route->distance = 0.0;

    for (size_t i=0; i<arraySize((void**) paths); i++) {
        route->distance += paths[i]->distance;
    }

    return route;
}

float getTotalPheromoneDeposited(Route** routes, Path* path, float UPDATE_RATE) {
    float totalPherDep = 0.0;
    size_t totalRoutes = arraySize((void**) routes);

    for (size_t i=0; i<totalRoutes; i++) {
        if (arrayContains((void**) routes[i]->paths, (void*) path)) {
            totalPherDep += (UPDATE_RATE / routes[i]->distance);
        }
    }

    return totalPherDep;
}

#endif // ROUTE_C_INCLUDED