#include <gtest/gtest.h>

#include "matrix_operation.h"

TEST(matmul_naive_test, equal_matrix) {
    size_t n = 2;
    int* a = (int*)malloc(n * n * sizeof(int));
    int* b = (int*)malloc(n * n * sizeof(int));
    int* c = (int*)calloc(n * n, sizeof(int));
    for (int i = 1; i <= n * n; i++) {
        a[i - 1] = i;
        b[i - 1] = i;
    }
    matmul_naive(a, b, c, n, n, n);
    int* correct_answer = (int*)calloc(n * n, sizeof(int));
    correct_answer[0] = 7;
    correct_answer[1] = 10;
    correct_answer[2] = 15;
    correct_answer[3] = 22;
    bool all_correct = true;
    for (int i = 0; i < n * n; i++) {
        if (c[i] != correct_answer[i]) {
            all_correct = false;
            break;
        }
    }
    EXPECT_EQ(all_correct, true);
}

TEST(matmul_naive_test, test2) {
    size_t row_a = 2;
    size_t col_a = 3;

    size_t row_b = 3;
    size_t col_b = 2;

    int* a = (int*)malloc(row_a * col_a * sizeof(int));
    int* b = (int*)malloc(row_b * col_b * sizeof(int));
    int* c = (int*)calloc(row_a * col_b, sizeof(int));

    for (int i = 1; i <= row_a * col_a; i++) {
        a[i - 1] = i;
    }

    for (int i = 1; i <= row_b * col_b; i++) {
        b[i - 1] = i;
    }

    matmul_naive(a, b, c, row_a, col_a, col_b);
    int* correct_answer = (int*)calloc(row_a * col_b, sizeof(int));
    correct_answer[0] = 22;
    correct_answer[1] = 28;
    correct_answer[2] = 49;
    correct_answer[3] = 64;
    bool all_correct = true;
    for (int i = 0; i < row_a * col_b; i++) {
        EXPECT_EQ(c[i], correct_answer[i]) << "Error: element is not equal";
        if (c[i] != correct_answer[i]) {
            all_correct = false;
            break;
        }
    }
}
