#ifdef RISCV

#include <riscv_vector.h>
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix_operation.h"

// void matmul_vectorization(const int *a, const int *b, int *c, size_t row_a,
//                           size_t col_a, size_t col_b) {
//   // Транспонируем матрицу B для удобства доступа
//   int *b_transpose = (int *)malloc(col_a * col_b * sizeof(int));
//   for (size_t i = 0; i < col_a; i++) {
//     for (size_t j = 0; j < col_b; j++) {
//       b_transpose[j * col_a + i] = b[i * col_b + j];
//     }
//   }

//   // Устанавливаем длину вектора один раз
//   size_t vl = __riscv_vsetvl_e32m4(8);  // VL для 8 элементов типа int

//   for (size_t i = 0; i < row_a; i++) {
//     for (size_t j = 0; j < col_b; j++) {
//       const int *ptr_a = &a[i * col_a];
//       const int *ptr_b = &b_transpose[j * col_a];
//       size_t k = col_a;

//       vint32m4_t vec_sum = __riscv_vmv_v_x_i32m4(0, vl);

//       // Обрабатываем данные в блоках по VL элементов
//       for (size_t i = 0; i < row_a; i++) {
//         for (size_t j = 0; j < col_b; j++) {
//           const int *ptr_a = &a[i * col_a];
//           const int *ptr_b = &b_transpose[j * col_a];

//           size_t k = col_a;  // Количество элементов в строке и столбце

//           // Обработка основного блока
//           while (k >= vl) {
//             // Обрабатываем основной блок
//             vint32m4_t vec_a = __riscv_vle32_v_i32m4(ptr_a, vl);
//             vint32m4_t vec_b = __riscv_vle32_v_i32m4(ptr_b, vl);
//             vec_sum = __riscv_vmacc_vv_i32m4(vec_sum, vec_a, vec_b, vl);

//             k -= vl;
//             ptr_a += vl;
//             ptr_b += vl;
//             printf("VL = %d\n", vl);
//             printf("Remaining k: %zu\n", k);  // Для диагностики
//           }

//           // Если осталось меньше, чем длина вектора, обрабатываем хвост
//           if (k > 0) {
//             size_t tail_vl = __riscv_vsetvl_e32m4(
//                 k);  // Устанавливаем нужную длину для хвоста
//             vint32m4_t vec_a_tail = __riscv_vle32_v_i32m4(ptr_a, tail_vl);
//             vint32m4_t vec_b_tail = __riscv_vle32_v_i32m4(ptr_b, tail_vl);
//             vec_sum = __riscv_vmacc_vv_i32m4(vec_sum, vec_a_tail, vec_b_tail,
//                                              tail_vl);
//             printf("Tail k: %zu\n", k);  // Для диагностики
//           }

//           // Суммирование элементов вектора
//           int sum_array[vl];
//           __riscv_vse32_v_i32m4(sum_array, vec_sum, vl);
//           int temp_sum = 0;
//           for (size_t x = 0; x < vl; x++) {
//             temp_sum += sum_array[x];
//           }

//           c[i * col_b + j] = temp_sum;
//         }
//       }
//     }
//   }

//   free(b_transpose);
// }

// void matmul_vectorization(const int *a, const int *b, int *c, size_t row_a,
//                           size_t col_a, size_t col_b) {
//   int *b_transpose = (int *)malloc(col_a * col_b * sizeof(int));
//   for (size_t i = 0; i < col_a; i++) {
//     for (size_t j = 0; j < col_b; j++) {
//       b_transpose[j * col_a + i] = b[i * col_b + j];
//     }
//   }

//   const size_t vl = __riscv_vsetvlmax_e32m4();  // Устанавливаем длину
//   вектора для 8 элементов 32-битных целых чисел vint32m4_t vec_sum;
//   vint32m4_t vec_a;
//   vint32m4_t vec_b;
//   for (size_t i = 0; i < row_a; i++) {
//     for (size_t j = 0; j < col_b; j++) {
//       const int *ptr_a = &a[i * col_a];
//       const int *ptr_b = &b_transpose[j * col_a];
//       size_t k = col_a;

//       vec_sum = __riscv_vmv_v_x_i32m4(0, vl);

//       for (k = col_a; k >= vl; k -= vl, ptr_a += vl, ptr_b += vl) {
//         vec_a = __riscv_vle32_v_i32m4(ptr_a, vl);
//         vec_b = __riscv_vle32_v_i32m4(ptr_b, vl);
//         vec_sum = __riscv_vmacc_vv_i32m4(vec_sum, vec_a, vec_b, vl);
//       }

//       // Обработка хвоста скалярно
//       int temp_sum = 0;
//       for (size_t x = 0; x < k; x++) {
//         temp_sum += ptr_a[x] * ptr_b[x];
//       }

//       // Добавлние суммы элементов вектора
//       int sum_array[vl];
//       __riscv_vse32_v_i32m4(sum_array, vec_sum, vl);
//       for (int x = 0; x < vl; x++) {
//         temp_sum += sum_array[x];
//       }

//       c[i * col_b + j] = temp_sum;
//     }
//   }
// }

// Realization of vectorization (RISC-V) matrix multiplication function

void matmul_vectorization(const int *a, const int *b, int *c, size_t row_a, size_t col_a,
                          size_t col_b) {
    // Транспонируем матрицу B для удобства доступа
    int *b_transpose = (int *)malloc(col_a * col_b * sizeof(int));
    for (size_t i = 0; i < col_a; i++) {
        for (size_t j = 0; j < col_b; j++) {
            b_transpose[j * col_a + i] = b[i * col_b + j];
        }
    }

    size_t vl_max = __riscv_vsetvlmax_e32m8();
    for (size_t i = 0; i < row_a; i++) {
        for (size_t j = 0; j < col_b; j++) {
            const int *cur_a = &a[i * col_a];
            const int *cur_b = &b_transpose[j * col_a];
            vint32m8_t v_sum = __riscv_vmv_v_x_i32m8(0, vl_max);
            size_t k = col_a;
            for (; k >= vl_max; k -= vl_max, cur_a += vl_max, cur_b += vl_max) {
                vint32m8_t v_a = __riscv_vle32_v_i32m8(cur_a, vl_max);
                vint32m8_t v_b = __riscv_vle32_v_i32m8(cur_b, vl_max);
                v_sum = __riscv_vmacc_vv_i32m8(v_sum, v_a, v_b, vl_max);
            }

            vint32m1_t v_cur_c_el = __riscv_vmv_v_x_i32m1(0, 1);
            v_cur_c_el = __riscv_vredsum_vs_i32m8_i32m1(v_sum, v_cur_c_el, vl_max);

            int tail_dot = 0;
            for (; k > 0; k--, cur_a++, cur_b++) {
                tail_dot += (*cur_a) * (*cur_b);
            }
            c[i * col_b + j] = __riscv_vmv_x_s_i32m1_i32(v_cur_c_el) + tail_dot;
        }
    }

    free(b_transpose);
}

#endif
