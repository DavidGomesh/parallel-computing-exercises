#include <omp.h>
#include <stdio.h>

int main() {

    printf("Hello! I'm out of parallel region!\n");

    #pragma omp parallel
    {
        int idThread = omp_get_thread_num();
        int qtdThread = omp_get_num_threads();
        printf("Thread: %d\tTotal: %d\n", idThread, qtdThread);
    }

    printf("Hello! I'm out of parallel region again!\n");

    return 0;
}
