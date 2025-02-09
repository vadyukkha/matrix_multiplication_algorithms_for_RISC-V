# Compute matmul(...) using algorithm below
#
# void matmul(const int *a, const int *b, int *c, size_t row_a, size_t col_a, size_t col_b) {
#     for (size_t i = 0; i < row_a; i++) {
#         for (size_t j = 0; j < col_b; j++) {
#             for (size_t k = 0; k < col_a; k++) {
#                 c[i * col_b + j] += a[i * col_a + k] * b[k * col_b + j];
#             }
#         }
#     }
# }

    .globl matmul_vectorization_asm
    .type matmul_vectorization_asm, @function
    .section .text
matmul_vectorization_asm:
    # a0 - matrix A
    # a1 - matrix B
    # a2 - matrix C (result)
    # a3 - row_a
    # a4 - col_a - row
    # a5 - col_b - col

# === First step is transpose of matrix B ===
    addi    sp, sp, -16                  # Allocate stack frame
    sw      s1, 12(sp)                   # Save s1
    sw      s2, 8(sp)                   # Save s2
    sw      s3, 4(sp)                   # Save s3
    sw      s4, 0(sp)                   # Save s4

    mul t0, a4, a5                      # Вычисляем количество элементов: rows * cols
    slli t0, t0, 2                      # Умножаем на 4 (размер int)
    sub sp, sp, t0                      # Выделяем память на стеке
    mv s1, sp                           # s1 теперь указывает на начало массива
    mv s4, t0                           # s4 = t0

    mv s2, a0                           # s2 = a0 (pointer to start matrix A)
    mv s3, s1                           # s3 = s1 (pointer to start matrix B)
    li t0, 0                            # j = 0
column_loop:
    bge  t0, a5, multiply               # if j >= col, move to multiplication
    li   t1, 0                          # i = 0
row_loop:
    bge  t1, a4, next_column            # if i >= row, move to next column

    sub  t2, a4, t1                     # t2 = row - i
    vsetvli t3, t2, e32, m1             # VL = min(t2, VLEN)

    # index-vector for gather
    vid.v v4                            # v4 = [0, 1, 2, ..., VL-1]
    slli t4, a5, 2                      # t4 = col * 4 (offset in bytes)
    vmul.vx v4, v4, t4                  # v4 = v4 * (col * 4)

    # calc offset
    mul  t5, t1, a5                     # t5 = i * col (line start pos)
    add  t5, t5, t0                     # t5 = i * col + j (offset)
    slli t5, t5, 2                      # t5 *= 4 (offset in bytes)
    add  t6, a1, t5                     # t6 = &B[i][j]
    
    # load column j from B
    vluxei32.v v0, (t6), v4             # load {B[i][j], B[i+1][j], ...}

    # calc offset
    mul  t5, t0, a4                     # t5 = j * row (line start pos)
    add  t5, t5, t1                     # t5 = j * row + i (offset)
    slli t5, t5, 2                      # t5 *= 4 (offset in bytes)
    add  t6, s1, t5                     # t6 = &B_transpose[j][i]

    # store
    vse32.v v0, (t6)                 

    add  t1, t1, t3                     # i += VL
    j    row_loop                       # repeat

next_column:
    addi t0, t0, 1                      # j++
    j column_loop                       # move to next column

# === Second step is matrix multiplication ===
multiply:
    mv a0, s2                           # a0 = s2 (matrix A)
    mv s1, s3                           # s1 = a0 (matrix B_transpose)

    li   t0, 0                          # i = 0
row_loop2:
    bge  t0, a3, done                   # if i >= row, exit
    li   t1, 0                          # j = 0
column_loop2:
    bge  t1, a5, next_row2              # if j >= col, move to next row
    mv   t2, a4                         # k = col_a
    vsetvli t3, t2, e32, m1             # VL = min(t2, VLEN)
    vmv.v.i v2, 0                       # v2 = 0 (vector sum)

    # calc offset
    mul t5, t0, a4                      # t5 = i * col_a
    slli t5, t5, 2                      # t5 *= 4
    add a0, s2, t5                      # a0 = &A[i][0]

    mul t5, t1, a4                      # t5 = j * col_a
    slli t5, t5, 2                      # t5 *= 4
    add s1, s3, t5                      # s1 = &B_transpose[j][0]

inner_loop2:
    blez t2, next_column2               # if k <= 0, move to next column
    vsetvli t3, t2, e32, m1             # VL = min(t2, VLEN)

    vle32.v v0, (a0)                    # load el from A
    vle32.v v1, (s1)                    # load el from B_transpose

    vmacc.vv v2, v0, v1                 # v2 += v0 * v1

    sub t2, t2, t3                      # size -= vl
    slli t4, t3, 2                      # t4 = t3 * 4
    add a0, a0, t4                      # move to next element A
    add s1, s1, t4                      # move to next element B_transpose

    j inner_loop2                       # repeat
next_column2:
    vsetvli t3, a4, e32, m1             # VL = min(t2, VLEN)
    # reduction
    vmv.v.i v3, 0
    vredsum.vs v3, v2, v3
    vmv.x.s t5, v3

    # calc offset
    mul t6, t0, a5                      # t6 = i * col_b
    add t6, t6, t1                      # t6 = i * col_b + j
    slli t6, t6, 2                      # t6 *= 4
    add t6, a2, t6                      # t6 = &C[i][j]
    
    # store result
    sw t5, 0(t6)

    addi t1, t1, 1                      # j++
    j column_loop2                      # move to next column

next_row2:
    addi t0, t0, 1                      # i++
    li t1, 0                            # j = 0
    j row_loop2                         # repeat
done:
    add sp, sp, s4                      # Освобождаем выделенную память
    lw s4, 0(sp)
    lw s3, 4(sp)                        # Restore s3
    lw s2, 8(sp)                        # Restore s2
    lw s1, 12(sp)                        # Restore s1
    addi sp, sp, 16                     # Deallocate stack frame
    ret
