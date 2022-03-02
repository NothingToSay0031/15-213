/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
/*
 * Some attempt
void transpose_submatrix(int *a, int *b, int from_row, int to_row, int from_col, int to_col, int col, int row) {
    int tmp, blockHeight, blockLength;
    if ((to_col - from_col) > 8) {
        blockHeight = 8;
    } else {
        blockHeight = (to_col - from_col);
    }
    if ((to_row - from_row) > 8) {
        blockLength = 8;
    } else {
        blockLength = (to_row - from_row);
    }
    for (int i = from_col; i < (to_col - from_col) / 2; ++i) {
        for (int j = (to_row - from_row) / 2; j < row; ++j) {
            for (int k = 0; k < blockLength && i + k < col; ++k) {
                for (int l = 0; l < blockHeight && j + l < row; ++l) {
                    tmp = *(a + (i + k) * col + j + l);
                    *(b + (j + l) * col + i + k) = tmp;
                }
            }
        }
    }
    for (int i = from_row; i < (to_row - from_row) / 2; ++i) {
        for (int j = 0; j < (to_col - from_col) / 2; ++j) {
            for (int k = 0; k < blockLength && i + k < col; ++k) {
                for (int l = 0; l < blockHeight && j + l < row; ++l) {
                    tmp = *(a + (i + k) * col + j + l);
                    *(b + (j + l) * col + i + k) = tmp;
                }
            }
        }
    }
}
*/

/**
 * @source https://yangtau.me/computer-system/csapp-cache.html
 * @source http://doraemonzzz.com/2020/07/22/CMU%2015-213%20Lab4%20Cache%20Lab/#64-times-64
 */
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
    int i, j, k, l;
    int t0, t1, t2, t3, t4, t5, t6, t7;
    if (M == 32) {
        for (i = 0; i < N; i += 8) {
            for (j = 0; j < M; j += 8) {
                for (k = i; k < i + 8; k++) {
                    t0 = A[k][j];
                    t1 = A[k][j + 1];
                    t2 = A[k][j + 2];
                    t3 = A[k][j + 3];
                    t4 = A[k][j + 4];
                    t5 = A[k][j + 5];
                    t6 = A[k][j + 6];
                    t7 = A[k][j + 7];
                    B[j][k] = t0;
                    B[j + 1][k] = t1;
                    B[j + 2][k] = t2;
                    B[j + 3][k] = t3;
                    B[j + 4][k] = t4;
                    B[j + 5][k] = t5;
                    B[j + 6][k] = t6;
                    B[j + 7][k] = t7;
                }
            }
        }
    } else if (M == 61) {
        for (i = 0; i < N; i += 17) {
            for (j = 0; j < M; j += 17) {
                for (k = i; k < i + 17 && k < N; k++) {
                    for (l = j; l < j + 17 && l < M; l++) {
                        B[l][k] = A[k][l];
                    }
                }
            }
        }
    } else if (M == 64) {
        // Divide the 8*8 matrix into 4 blocks: A11,A12,A21,A22
        for (i = 0; i < N; i += 8) {
            for (j = 0; j < M; j += 8) {
                for (k = 0; k < 4; k++) {
                    t0 = A[i + k][j + 0];
                    t1 = A[i + k][j + 1];
                    t2 = A[i + k][j + 2];
                    t3 = A[i + k][j + 3];
                    t4 = A[i + k][j + 4];
                    t5 = A[i + k][j + 5];
                    t6 = A[i + k][j + 6];
                    t7 = A[i + k][j + 7];
                    // B11 = A11^T
                    B[j + 0][i + k] = t0;
                    B[j + 1][i + k] = t1;
                    B[j + 2][i + k] = t2;
                    B[j + 3][i + k] = t3;
                    // B12 = A12^T
                    B[j + 0][i + k + 4] = t4;
                    B[j + 1][i + k + 4] = t5;
                    B[j + 2][i + k + 4] = t6;
                    B[j + 3][i + k + 4] = t7;
                }
                for (k = 4; k < 8; k++) {
                    // Save B12
                    t0 = B[j + k - 4][i + 0 + 4];
                    t1 = B[j + k - 4][i + 1 + 4];
                    t2 = B[j + k - 4][i + 2 + 4];
                    t3 = B[j + k - 4][i + 3 + 4];
                    // B12 = A21^T
                    for (l = 0; l < 4; l++) {
                        B[j + k - 4][i + l + 4] = A[i + l + 4][j + k - 4];
                    }
                    // B21 = B12 = A12^T
                    B[j + k][i + 0] = t0;
                    B[j + k][i + 1] = t1;
                    B[j + k][i + 2] = t2;
                    B[j + k][i + 3] = t3;
                    // B22 = A22^T
                    for (l = 4; l < 8; l++) {
                        B[j + k][i + l] = A[i + l][j + k];
                    }
                }
            }
        }
    }
}
/*
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started.
 */

/*
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";

void trans(int M, int N, int A[N][M], int B[M][N]) {
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions() {
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N]) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

