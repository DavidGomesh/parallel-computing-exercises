#include <omp.h>
#include <stdio.h>

int main() {

    printf("\nSerial region 01!\n");

    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int idThread = omp_get_thread_num();
        int qtdThread = omp_get_num_threads();
        printf("Thread: %d\tTotal: %d\n", idThread, qtdThread);
    }

    printf("\nSerial region 02!\n");

    omp_set_num_threads(8);
    #pragma omp parallel
    {
        int idThread = omp_get_thread_num();
        int qtdThread = omp_get_num_threads();
        printf("Thread: %d\tTotal: %d\n", idThread, qtdThread);
    }

    printf("\nSerial region 03!\n");

    omp_set_num_threads(32);
    #pragma omp parallel
    {
        int idThread = omp_get_thread_num();
        int qtdThread = omp_get_num_threads();
        printf("Thread: %d\tTotal: %d\n", idThread, qtdThread);
    }

    printf("The end (non parallel).\n");

    return 0;
}
