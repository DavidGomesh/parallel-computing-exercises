#include <omp.h>
#include <stdio.h>

void serialCode();
void parallelCode();

int main() {
    // serialCode();
    parallelCode();
    printf("The end.\n");
    return 0;
}

void serialCode() {
    int qtd = 2048;

    int array1[qtd];
    int array2[qtd];
    int array3[qtd];

    for (int i=0; i<qtd; i++) {
        array1[i] = 2;
        array2[i] = 3;
    }

    for (int i=0; i<qtd; i++) {
        array3[i] = array1[i] + array2[i];
    }

    for (int i=0; i<qtd; i++) {
        printf("%d\n", array3[i]);
    }
}

void parallelCode() {
    int qtd = 2048;

    int array1[qtd];
    int array2[qtd];
    int array3[qtd];

    for (int i=0; i<qtd; i++) {
        array1[i] = 2;
        array2[i] = 3;
    }

    #pragma omp parallel num_threads(16)
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();

        int size = (int) qtd/nt;
        int start = id * size;
        int end = start + size - 1;

        for (int i=start; i<=end; i++) {
            array3[i] = array1[i] + array2[i];
        }
    }

    for (int i=0; i<qtd; i++) {
        printf("%d\n", array3[i]);
    }
}