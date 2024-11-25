#include <gtest/gtest.h>

#include "matrix_operation.h"
#include "matsize_generator.h"

class matmul_vectorization_test : public ::testing::TestWithParam<matrix_size_t> {};

static void fill_matrix_with_randint(int *matrix, size_t row, size_t col) {
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            matrix[i * col + j] = rand() % 32768;
        }
    }
}

TEST_P(matmul_vectorization_test, equal_matrix) {
    auto params = GetParam();
    size_t row_a = std::get<0>(params);
    size_t col_a = std::get<1>(params);
    size_t col_b = std::get<2>(params);

    int *a = (int *)malloc(row_a * col_a * sizeof(int));
    int *b = (int *)malloc(col_a * col_b * sizeof(int));
    int *mat_naive = (int *)calloc(row_a * col_b, sizeof(int));
    int *mat_vectorization = (int *)calloc(row_a * col_b, sizeof(int));

    fill_matrix_with_randint(a, row_a, col_a);
    fill_matrix_with_randint(b, col_a, col_b);

    matmul_naive(a, b, mat_naive, row_a, col_a, col_b);
    matmul_vectorization(a, b, mat_vectorization, row_a, col_a, col_b);

    for (size_t i = 0; i < row_a; i++) {
        for (size_t j = 0; j < col_b; j++) {
            EXPECT_EQ(mat_naive[i * col_b + j], mat_vectorization[i * col_b + j])
                << "Error: element is not equal";
        }
    }

    free(a);
    free(b);
    free(mat_naive);
    free(mat_vectorization);
}

INSTANTIATE_TEST_SUITE_P(, matmul_vectorization_test,
                         ::testing::ValuesIn(generate_tests_parametrs(100)));
