#include <stdio.h>
#include <time.h>

#include "benchmarking.h"
#include "matrix_operation.h"

#define TEST_COUNT 10
#define BUFFER_SIZE 256
#define FILE_PATH "benchmarking_outputs/matmul_vectorization.txt"

void matmul_vectorization(const int *a, const int *b, int *c, size_t row_a, size_t col_a,
                          size_t col_b);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Using: <step> <finish>\n");
        return 1;
    }

    FILE *file = fopen(FILE_PATH, "w");

    size_t step = (size_t)atoi(argv[1]);
    size_t finish = (size_t)atoi(argv[2]);

    static char buffer[BUFFER_SIZE];
    for (size_t mat_size = step; mat_size <= finish; mat_size += step) {
        double res = benchmarking(matmul_vectorization, TEST_COUNT, mat_size, mat_size, mat_size);
        sprintf(buffer, "%.7f", res);
        fprintf(file, "%zu:%s\n", mat_size, buffer);
        printf("[BENCHMARK C] Running matmul vectorization with size %zu\n", mat_size);
    }
    fclose(file);

    return 0;
}
