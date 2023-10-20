#include "matrix.h"

#include <stdio.h>

void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

void init_identity_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            if (i == j)
            {
                matrix[i][j] = 1.0;
            } else {
                matrix[i][j] = 0.0;
            }
        }
    }
}

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(const float result[3][3], const float a[3][3], float b[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiply_scalar_matrix(float result[3][3], float scalar, const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
}