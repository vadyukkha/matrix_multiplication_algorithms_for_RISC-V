#include <stdio.h>
#include <time.h>

#include "benchmarking.h"
#include "matrix_operation.h"

void matmul_naive(const int *a, const int *b, int *c, size_t row_a, size_t col_a, size_t col_b);

void huge_matrices_benchmarking() {
    int mat_size = 500;
    int tests_count = 10;
    double res = 
        benchmarking(matmul_naive, tests_count, mat_size, mat_size, mat_size);
    printf("%f cycles by using naive on the huge matrices\n", res);
}

void medium_matrices_benchmarking(){
    int mat_size = 100;
    int tests_count = 10;
    double res = 
        benchmarking(matmul_naive, tests_count, mat_size, mat_size, mat_size);
    printf("%f cycles by using naive in the medium-sized matrices\n", res);
}

void small_matrices_benchmarking() {
    int mat_size = 10;
    int tests_count = 10;
    double res = 
        benchmarking(matmul_naive, tests_count, mat_size, mat_size, mat_size);
    printf("%f cycles by using naive in the small matrices\n", res);
}

int main() {
    huge_matrices_benchmarking();
    medium_matrices_benchmarking();
    small_matrices_benchmarking();
    return 0;
}
