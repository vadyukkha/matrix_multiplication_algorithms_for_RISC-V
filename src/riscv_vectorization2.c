#ifdef RISCV

#include <riscv_vector.h>
#include <stdlib.h>
#include <stdio.h>

#include "matrix_operation.h"

// Realization of vectorization (RISC-V) matrix multiplication function
void matmul_vectorization(const int *a, const int *b, int *c, size_t row_a, size_t col_a,
                          size_t col_b) {
    int *b_transpose = (int *)malloc(col_a * col_b * sizeof(int));
    for (size_t i = 0; i < col_a; i++) {
        for (size_t j = 0; j < col_b; j++) {
            b_transpose[j * col_a + i] = b[i * col_b + j];
        }
    }

    size_t vlmax = __riscv_vsetvlmax_e32m1();

    int vl = __riscv_vsetvl_e32m1(col_a);

    for (int i = 0; i < row_a; ++i) {
        for (int j = 0; j < col_b; ++j) {
            const int *ptr_a = &a[i * col_a];
            const int *ptr_b = &b_transpose[j * col_a];
            int k = col_a;
            vint32m1_t vec_s = __riscv_vmv_v_x_i32m1(0, vlmax);
            vint32m1_t vec_zero = __riscv_vmv_v_x_i32m1(0, vlmax);
            for (int c = col_a / vl ; c > 0; c--, ptr_a += vl, ptr_b += vl) {
                vint32m1_t vec_a = __riscv_vle32_v_i32m1(ptr_a, vl);
                vint32m1_t vec_b = __riscv_vle32_v_i32m1(ptr_b, vl);

                vec_s = __riscv_vmacc_vv_i32m1(vec_s, vec_a, vec_b, vl);
            }

            if (col_a % vl != 0) {
                int tailvl = __riscv_vsetvl_e32m1(col_a % vl);
                vint32m1_t vec_a = __riscv_vle32_v_i32m1(ptr_a, tailvl);
                vint32m1_t vec_b = __riscv_vle32_v_i32m1(ptr_b, tailvl);
                vec_s = __riscv_vmacc_vv_i32m1(vec_s, vec_a, vec_b, tailvl);
            }

            vint32m1_t vec_sum = __riscv_vredsum_vs_i32m1_i32m1(vec_s, vec_zero, vlmax);
            int sum = __riscv_vmv_x_s_i32m1_i32(vec_sum);
            c[i * col_b + j] = sum;
        }
    }

    free(b_transpose);
}

#endif
