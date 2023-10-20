#include "matrix.h"

#include <stdio.h>

void init_zero_matrix(matrix m)
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            m[i][j] = 0.0;
        }
    }
}

void init_identity_matrix(matrix m)
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            if (i == j)
            {
                m[i][j] = 1.0;
            } else {
                m[i][j] = 0.0;
            }
        }
    }
}

void print_matrix(const matrix m)
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", m[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(matrix result, const matrix a, const matrix b)
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiply_matrices(matrix result, const matrix a, const matrix b)
{
    int i;
    int j;
    int k;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            int sum = 0;
            for (k = 0; k < 3; ++k) {
                sum = sum + a[i][k] * b [k][j];
            }
            result[i][j] = sum;
        }
    }
}

void multiply_scalar_matrix(matrix result, const float scalar, const matrix m)
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            result[i][j] = m[i][j] * scalar;
        }
    }
}