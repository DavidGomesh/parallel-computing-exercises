#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int isPrime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int countPrimes(int start, int end) {
    int count = 0;
    for (int i = start; i <= end; i++) {
        if (isPrime(i)) count++;
    }
    return count;
}

int main() {
    int start = 1;
    int end = 50000000;
    int num_threads = 16;

    omp_set_num_threads(num_threads);

    double start_time = omp_get_wtime();

    int total_primes = 0;
    #pragma omp parallel for reduction(+:total_primes)
    for (int i = start; i <= end; i++) {
        total_primes += isPrime(i);
    }

    double end_time = omp_get_wtime();

    printf("Total number of primes in the range from %d to %d: %d\n", start, end, total_primes);
    printf("Execution time: %f seconds\n", end_time - start_time);

    return 0;
}
