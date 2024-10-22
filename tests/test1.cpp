#include "../include/naive.h"
#include <gtest/gtest.h>

TEST(matmul_naive_test, equal_matrix) {
    size_t n = 2;
    float* a = (float*)malloc(n * n * sizeof(float));
    float* b = (float*)malloc(n * n * sizeof(float));
    float* c = (float*)calloc(n * n, sizeof(float));
    for (int i = 1; i <= n*n; i++) {
        a[i-1] = i;
        b[i-1] = i;
    }
    matmul_naive(a, b, c, n);
    float* correct_answer = (float*)calloc(n * n, sizeof(float));
    correct_answer[0] = 7;
    correct_answer[1] = 10;
    correct_answer[2] = 15;
    correct_answer[3] = 22;
    bool all_correct = true;
    for (int i = 0; i < n*n; i++) {
        if (c[i] != correct_answer[i]){
            all_correct = false;
            break;
        }
    }
    EXPECT_EQ(all_correct, true);
}
