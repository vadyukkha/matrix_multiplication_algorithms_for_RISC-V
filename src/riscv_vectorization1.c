#ifdef RISCV

#include <riscv_vector.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdalign.h>

#include "matrix_operation.h"

void matmul_vectorization(const int *a, const int *b, int *c, size_t row_a,
                          size_t col_a, size_t col_b) {
  int *b_transpose = (int *)malloc(col_a * col_b * sizeof(int));
  for (size_t i = 0; i < col_a; i++) {
    for (size_t j = 0; j < col_b; j++) {
      b_transpose[j * col_a + i] = b[i * col_b + j];
    }
  }

  size_t vl = __riscv_vsetvl_e32m8(8);  // Устанавливаем длину вектора для 8 элементов 32-битных целых чисел

  for (size_t i = 0; i < row_a; i++) {
    for (size_t j = 0; j < col_b; j++) {
      const int *ptr_a = &a[i * col_a];
      const int *ptr_b = &b_transpose[j * col_a];
      size_t k = col_a;

      vint32m8_t vec_sum = __riscv_vmv_v_x_i32m8(0, vl);

      for (k = col_a; k >= vl; k -= vl, ptr_a += vl, ptr_b += vl) {
        vint32m8_t vec_a = __riscv_vle32_v_i32m8(ptr_a, vl);
        vint32m8_t vec_b = __riscv_vle32_v_i32m8(ptr_b, vl);
        vec_sum = __riscv_vmacc_vv_i32m8(vec_sum, vec_a, vec_b, vl);
      }

      int temp_sum = 0;
      for (size_t x = 0; x < k; x++) {
        temp_sum += ptr_a[x] * ptr_b[x];
      }
      
      alignas(32) int sum_array[8];
      __riscv_vse32_v_i32m8(sum_array, vec_sum, vl);
      for (int x = 0; x < 8; x++) {
        temp_sum += sum_array[x];
      }

      c[i * col_b + j] = temp_sum;
    }
  }
}

#endif
