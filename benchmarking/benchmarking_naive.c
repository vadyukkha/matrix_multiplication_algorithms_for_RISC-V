#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

#include "benchmarking.h"
#include "matrix_operation.h"

#define TEST_COUNT 10
#define BUFFER_SIZE 256
#define FILE_PATH "../benchmarking/benchmarking_outputs/matmul_naive.txt"

void matmul_naive(const int *a, const int *b, int *c, size_t row_a, size_t col_a, size_t col_b);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Using: %s <matrix_size>\n", argv[0]);
        return 1;
    }

    if (mkdir("../benchmarking/benchmarking_outputs", 0777) != 0 && errno != EEXIST) {
        perror("Error creating dir");
        return 1;
    }

    FILE *file = fopen(FILE_PATH, "w");
    if (file == NULL) {
        printf("Error: file was not opened\n");
        return 1;
    }

    size_t step = (size_t)atoi(argv[1]);
    size_t finish = (size_t)atoi(argv[2]);

    static char buffer[BUFFER_SIZE];
    for (size_t mat_size = step; mat_size <= finish; mat_size += step) {
        double res = benchmarking(matmul_naive, TEST_COUNT, mat_size, mat_size, mat_size);
        sprintf(buffer, "%.7f", res);
        fprintf(file, "%zu:%s\n", mat_size, buffer);
        printf("[BENCHMARK C] Running matmul naive with size %zu\n", mat_size);
    }
    fclose(file);

    return 0;
}
