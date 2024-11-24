#include <gtest/gtest.h>

#include "matrix_operation.h"

TEST(matmul_naive_test, equal_matrix) {
    int n = 2;
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
    free(a);
    free(b);
    free(c);
    free(correct_answer);
}

TEST(matmul_naive_test, little_matrix) {
    int n = 2;
    int* a = (int*)malloc(n * n * sizeof(int));
    int* b = (int*)malloc(n * n * sizeof(int));
    int* c = (int*)calloc(n * n, sizeof(int));
    for (int i = 1; i <= n * n; i++) {
        a[i - 1] = i * 2;
        b[i - 1] = i;
    }
    matmul_naive(a, b, c, n, n, n);
    int* correct_answer = (int*)calloc(n * n, sizeof(int));
    correct_answer[0] = 14;
    correct_answer[1] = 20;
    correct_answer[2] = 30;
    correct_answer[3] = 44;
    bool all_correct = true;
    for (int i = 0; i < n * n; i++) {
        if (c[i] != correct_answer[i]) {
            all_correct = false;
            break;
        }
    }
    EXPECT_EQ(all_correct, true);
    free(a);
    free(b);
    free(c);
    free(correct_answer);
}

TEST(matmul_naive_test, square) {
    int n = 3;
    int* a = (int*)malloc(n * n * sizeof(int));
    int* b = (int*)malloc(n * n * sizeof(int));
    int* c = (int*)calloc(n * n, sizeof(int));
    for (int i = 1; i <= n * n; i++) {
        a[i - 1] = (i + 2) * 2 + 5;
        b[i - 1] = i + 5;
    }
    matmul_naive(a, b, c, n, n, n);
    int* correct_answer = (int*)calloc(n * n, sizeof(int));
    correct_answer[0] = 363;
    correct_answer[1] = 402;
    correct_answer[2] = 441;
    correct_answer[3] = 525;
    correct_answer[4] = 582;
    correct_answer[5] = 639;
    correct_answer[6] = 687;
    correct_answer[7] = 762;
    correct_answer[8] = 837;
    bool all_correct = true;
    for (int i = 0; i < n * n; i++) {
        if (c[i] != correct_answer[i]) {
            all_correct = false;
            break;
        }
    }
    EXPECT_EQ(all_correct, true);
    free(a);
    free(b);
    free(c);
    free(correct_answer);
}

TEST(matmul_naive_test, non_square) {
    int n = 2;
    int m = 1;
    int* a = (int*)malloc(n * m * sizeof(int));
    int* b = (int*)malloc(m * n * sizeof(int));
    int* c = (int*)calloc(m * n, sizeof(int));
    for (int i = 1; i <= n * m; i++) {
        a[i - 1] = i + 3;
        b[i - 1] = i + 2;
    }
    matmul_naive(a, b, c, n, m, n);
    int* correct_answer = (int*)calloc(n * n, sizeof(int));
    correct_answer[0] = 12;
    correct_answer[1] = 16;
    correct_answer[2] = 15;
    correct_answer[3] = 20;
    bool all_correct = true;
    for (int i = 0; i < n * n; i++) {
        if (c[i] != correct_answer[i]) {
            all_correct = false;
            break;
        }
    }
    EXPECT_EQ(all_correct, true);
    free(a);
    free(b);
    free(c);
    free(correct_answer);
}

TEST(matmul_naive_test, negative_and_non_square) {
    int n = 2;
    int m = 3;
    int* a = (int*)malloc(n * m * sizeof(int));
    int* b = (int*)malloc(m * n * sizeof(int));
    int* c = (int*)calloc(m * n, sizeof(int));
    for (int i = 1; i <= n * m; i++) {
        a[i - 1] = -1 * i - 4;
        b[i - 1] = -1 * i;
    }
    matmul_naive(a, b, c, n, m, n);
    int* correct_answer = (int*)calloc(n * n, sizeof(int));
    correct_answer[0] = 58;
    correct_answer[1] = 76;
    correct_answer[2] = 85;
    correct_answer[3] = 112;
    bool all_correct = true;
    for (int i = 0; i < n * n; i++) {
        if (c[i] != correct_answer[i]) {
            all_correct = false;
            break;
        }
    }
    EXPECT_EQ(all_correct, true);
    free(a);
    free(b);
    free(c);
    free(correct_answer);
}
