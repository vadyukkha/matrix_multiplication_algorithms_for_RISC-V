#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "matrix_operation.h"
#define BLOCK_SIZE 32

typedef struct {
    const int* a;
    const int* b_t;
    int* c;
    size_t row_a;
    size_t col_a;
    size_t col_b;
    int blocks_j;
    int blocks_k;
    atomic_int next_block_i;
    int total_blocks_i;
} ArgsForMatmul;

typedef struct {
    int* b_transpose;
    const int* b;
    size_t col_a;
    size_t col_b;
    atomic_int next_i;
    size_t total_i;
} ArgsForTranspose;

typedef struct {
    pthread_t* threads;
    int num_threads;
} ThreadPool;

void thread_pool_init(ThreadPool* pool, int num_threads) {
    pool->threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t));
    pool->num_threads = num_threads;
}

void thread_pool_add(ThreadPool* pool, void* (*task)(void*), void* arg) {
    for (int i = 0; i < pool->num_threads; i++) {
        pthread_create(&pool->threads[i], NULL, task, arg);
    }
}

void thread_pool_join(ThreadPool* pool) {
    for (int i = 0; i < pool->num_threads; i++) {
        pthread_join(pool->threads[i], NULL);
    }
}

void matmul_block(const int* a, const int* b_t, int* c, size_t row_a, size_t col_a, size_t col_b,
                  int block_i, int block_j, int block_k) {
    int start_i = block_i * BLOCK_SIZE;
    int start_j = block_j * BLOCK_SIZE;
    int start_k = block_k * BLOCK_SIZE;
    int end_i;
    int end_j;
    int end_k;
    if ((block_i + 1) * BLOCK_SIZE < row_a) {
        end_i = (block_i + 1) * BLOCK_SIZE;
    } else {
        end_i = row_a;
    }
    if ((block_j + 1) * BLOCK_SIZE < col_b) {
        end_j = (block_j + 1) * BLOCK_SIZE;
    } else {
        end_j = col_b;
    }
    if ((block_k + 1) * BLOCK_SIZE < col_a) {
        end_k = (block_k + 1) * BLOCK_SIZE;
    } else {
        end_k = col_a;
    }

    int local_c[BLOCK_SIZE * BLOCK_SIZE] = {0};

    for (int i = start_i; i < end_i; i++) {
        for (int k = start_k; k < end_k; k++) {
            int a_ik = a[i * col_a + k];
            for (int j = start_j; j < end_j; j++) {
                int idx = (i - start_i) * BLOCK_SIZE + (j - start_j);
                local_c[idx] += a_ik * b_t[j * col_a + k];
            }
        }
    }

    for (int i = start_i; i < end_i; i++) {
        for (int j = start_j; j < end_j; j++) {
            int idx = (i - start_i) * BLOCK_SIZE + (j - start_j);
            c[i * col_b + j] += local_c[idx];
        }
    }
}

void* multiply_thread(void* arg) {
    ArgsForMatmul* args = (ArgsForMatmul*)arg;
    int block_i;
    while (1) {
        block_i = atomic_fetch_add(&args->next_block_i, 1);
        if (block_i >= args->total_blocks_i) break;

        for (int block_j = 0; block_j < args->blocks_j; block_j++) {
            for (int block_k = 0; block_k < args->blocks_k; block_k++) {
                matmul_block(args->a, args->b_t, args->c, args->row_a, args->col_a, args->col_b,
                             block_i, block_j, block_k);
            }
        }
    }
    return NULL;
}

void* transpose_thread(void* arg) {
    ArgsForTranspose* args = (ArgsForTranspose*)arg;
    int i;
    while (1) {
        i = atomic_fetch_add(&args->next_i, 1);
        if (i >= args->total_i) break;

        for (size_t j = 0; j < args->col_b; j++) {
            args->b_transpose[j * args->col_a + i] = args->b[i * args->col_b + j];
        }
    }
    return NULL;
}

void matmul_block_transpose(const int* a, const int* b, int* c, size_t row_a, size_t col_a,
                            size_t col_b) {
    int* b_transpose = (int*)malloc(col_a * col_b * sizeof(int));
    int num_threads = sysconf(_SC_NPROCESSORS_ONLN);
    ThreadPool pool;
    thread_pool_init(&pool, num_threads);

    ArgsForTranspose args_t = {.b_transpose = b_transpose,
                               .b = b,
                               .col_a = col_a,
                               .col_b = col_b,
                               .next_i = 0,
                               .total_i = col_a};
    thread_pool_add(&pool, transpose_thread, &args_t);
    thread_pool_join(&pool);

    int blocks_i = (row_a + BLOCK_SIZE - 1) / BLOCK_SIZE;
    int blocks_j = (col_b + BLOCK_SIZE - 1) / BLOCK_SIZE;
    int blocks_k = (col_a + BLOCK_SIZE - 1) / BLOCK_SIZE;

    ArgsForMatmul args_m = {.a = a,
                            .b_t = b_transpose,
                            .c = c,
                            .row_a = row_a,
                            .col_a = col_a,
                            .col_b = col_b,
                            .blocks_j = blocks_j,
                            .blocks_k = blocks_k,
                            .next_block_i = 0,
                            .total_blocks_i = blocks_i};
    thread_pool_add(&pool, multiply_thread, &args_m);
    thread_pool_join(&pool);

    free(b_transpose);
    free(pool.threads);
}
