#include <gtest/gtest.h>

#include "matrix_operation.h"
#include "matsize_generator.h"

class matmul_transpose_test : public ::testing::TestWithParam<matrix_size_t> {};

void fill_matrix_with_randint(int *matrix, size_t row, size_t col) {
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            matrix[i * col + j] = rand() % 32768;
        }
    }
}

TEST_P(matmul_transpose_test, equal_matrix) {
    auto params = GetParam();
    size_t row_a = std::get<0>(params);
    size_t col_a = std::get<1>(params);
    size_t col_b = std::get<2>(params);

    int *a = (int *)malloc(row_a * col_a * sizeof(int));
    int *b = (int *)malloc(col_a * col_b * sizeof(int));
    int *mat_naive = (int *)calloc(row_a * col_b, sizeof(int));
    int *mat_transpose = (int *)calloc(row_a * col_b, sizeof(int));

    matmul_naive(a, b, mat_naive, row_a, col_a, col_b);
    matmul_transpose(a, b, mat_transpose, row_a, col_a, col_b);

    for (size_t i = 0; i < row_a; i++) {
        for (size_t j = 0; j < col_b; j++) {
            EXPECT_EQ(mat_naive[i * col_b + j], mat_transpose[i * col_b + j])
                << "Error: element is not equal";
        }
    }
}

INSTANTIATE_TEST_SUITE_P(, matmul_transpose_test,
                         ::testing::ValuesIn(generate_tests_parametrs(10)));
