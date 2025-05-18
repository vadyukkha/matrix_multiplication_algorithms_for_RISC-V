#ifndef RISCV

#include <immintrin.h>
#include <stdalign.h>
#include <stdlib.h>

// Realization of vectorize (x86) matrix multiplication function
void matmul_vectorize_x86(const int *a, const int *b, int *c, size_t row_a, size_t col_a,
                          size_t col_b) {
    int *b_transpose = (int *)malloc(col_a * col_b * sizeof(int));
    for (size_t i = 0; i < col_a; i++) {
        for (size_t j = 0; j < col_b; j++) {
            b_transpose[j * col_a + i] = b[i * col_b + j];
        }
    }

    for (size_t i = 0; i < row_a; ++i) {
        for (size_t j = 0; j < col_b; ++j) {
            const int *ptr_a = &a[i * col_a];
            const int *ptr_b = &b_transpose[j * col_a];
            size_t k = col_a;

            __m256i vec_sum = _mm256_setzero_si256();

            for (k = col_a; k >= 8; k -= 8, ptr_a += 8, ptr_b += 8) {
                __m256i vec_a = _mm256_loadu_si256((const __m256i *)ptr_a);
                __m256i vec_b = _mm256_loadu_si256((const __m256i *)ptr_b);

                vec_sum = _mm256_add_epi32(vec_sum, _mm256_mullo_epi32(vec_a, vec_b));
            }

            // Обрабатываем оставшиеся элементы (менее 8)
            int temp_sum = 0;
            for (size_t x = 0; x < k; x++) {
                temp_sum += ptr_a[x] * ptr_b[x];
            }

            alignas(32) int sum_array[8];
            _mm256_store_si256((__m256i *)sum_array, vec_sum);
            for (int x = 0; x < 8; x++) {
                temp_sum += sum_array[x];
            }

            c[i * col_b + j] = temp_sum;
        }
    }

    free(b_transpose);
}

#endif
