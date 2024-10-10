// Copyright 2024 by Contributors
#include "../include/naive.h"

int main() {
    clock_t start_programm = clock();
    for (size_t n = 0; n <= 100; n++) {
        clock_t start = clock();
        float* a = (float*)malloc(n * n * sizeof(float));
        float* b = (float*)malloc(n * n * sizeof(float));
        float* c = (float*)calloc(n * n, sizeof(float));

        matmul_naive(a, b, c, n);
        printf("n = %zu, time = %.7f\n", n, (double)(clock() - start) / CLOCKS_PER_SEC);
    }
    printf("Programm time = %f\n", (double)(clock() - start_programm) / CLOCKS_PER_SEC);
    return 0;
}
