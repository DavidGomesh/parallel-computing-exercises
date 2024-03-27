#include <omp.h>
#include <stdio.h>

void parallelCode();

int main() {
    parallelCode();
    printf("The end.\n");
    return 0;
}

void parallelCode() {
    int qtd = 16;

    int matrix1[qtd][qtd];
    int matrix2[qtd][qtd];
    int matrix3[qtd][qtd];

    for (int i=0; i<qtd; i++) {
        for (int j=0; j<qtd; j++) {
            matrix1[i][j] = 2;
            matrix2[i][j] = 3;
        }
    }

    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();
        int nt = omp_get_num_threads();

        int size = (int) qtd/nt;
        int start = id * size;
        int end = start + size - 1;

        for (int i=start; i<=end; i++) {
            for (int j=0; j<qtd; j++) {
                matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
    }

    for (int i=0; i<qtd; i++) {
        for (int j=0; j<qtd; j++) {
            printf("%d\n", matrix3[i][j]);
        }
    }
}