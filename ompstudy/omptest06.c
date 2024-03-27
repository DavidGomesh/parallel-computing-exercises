#include <omp.h>
#include <stdio.h>

void parallelCode01();
void parallelCode02();

int main() {
    // parallelCode01();
    parallelCode02();
    printf("The end.\n");
    return 0;
}

void parallelCode01() {
    int qtd = 10;

    int array1[qtd];
    int array2[qtd];
    int array3[qtd];

    for (int i=0; i<qtd; i++) {
        array1[i] = 2;
        array2[i] = 3;
    }

    #pragma omp parallel num_threads(3)
    {
        #pragma omp for
        for (int i=0; i<qtd; i++) {
            array3[i] = array1[i] + array2[i];
        }
    }

    for (int i=0; i<qtd; i++) {
        printf("%d\n", array3[i]);
    }
}

void parallelCode02() {
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

    #pragma omp parallel num_threads(3)
    {
        #pragma omp for
        for (int i=0; i<qtd; i++) {
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