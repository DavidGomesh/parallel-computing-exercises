#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#include "graph/Graph.h"
#include "travelling-salesman/Field.h"

#include "utils/Array.h"
#include "utils/Generators.h"

#define QTD_CITIES  70
#define MIN_DIST    1
#define MAX_DIST    10

#define QTD_ITER    100
#define EVAP_RATE   0.01
#define UPD_RATE    10   // Q Constant

void run();
void showBestRoute(Route* route, int iteration, float difference);

int main() {
    srand(time(NULL));

    printf("\nTRAVELLING SALESMAN PROBLEM\n");
    printf("Developer: David Gomes\n\n");

    printf("Quant. Cities: %d\n", QTD_CITIES);
    printf("Min. Distance: %d\n", MIN_DIST);
    printf("Max. Distance: %d\n\n", MAX_DIST);

    printf("Quant. Iterations: %d\n", QTD_ITER);
    printf("Evaporation Rate: %f\n", EVAP_RATE);
    printf("Update Rate (Q): %d\n\n", UPD_RATE);

    run();

    printf("\nThe end.\n");
    return 0;
}

void run() {
    Graph* graph = generateCities(QTD_CITIES, MIN_DIST, MAX_DIST);
    Field* field = newField(graph, EVAP_RATE, UPD_RATE);

    Route* currentBest = NULL;
    double start_time = omp_get_wtime();
    for (int i=0; i<QTD_ITER; i++) {
        
        generateOdds(field);
        generateRoutes(field);
        updatePheromones(field);
        getBestRoute(field);

        if (i % (int) sqrt(QTD_ITER) == 0) {
            printf("Iterations: %d\n", i);
        }

        if (i == 0 || field->bestRoute->distance < currentBest->distance) {
            float diff = currentBest == NULL ? 0.0 : field->bestRoute->distance - currentBest->distance;
            currentBest = field->bestRoute;
            showBestRoute(currentBest, i, diff);
        }
    }
    double end_time = omp_get_wtime();
    printf("\nTIME ELAPSED: %.0f seconds\n", end_time - start_time);
}

void showBestRoute(Route* route, int iteration, float difference) {
    printf("BEST ROUTE (Iteration: %d\tDistance: %.2f\tDifference: %.2f)\n", iteration, route->distance, difference);
    
    for (size_t i=0; i<arraySize((void**) route->paths); i++) {
        printf("%s ", (char*) route->paths[i]->origin->data);
    }
    printf("\n\n");
}
