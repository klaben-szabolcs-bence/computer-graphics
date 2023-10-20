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

void print_point(const point p)
{
    int i;

    for (i = 0; i < 3; ++i) {
        printf("%4.4f ", p[i]);
    }
    printf(" ^ T\n");
}

void copy_matrix(matrix to, const matrix from)
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            to[i][j] = from[i][j];
        }
    }
}

void copy_point(point to, const point from)
{
    int i;
    for (i = 0; i < 3; ++i) {
        to[i] = from[i];
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
    matrix out;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            int sum = 0;
            for (k = 0; k < 3; ++k) {
                sum = sum + a[i][k] * b [k][j];
            }
            out[i][j] = sum;
        }
    }

    copy_matrix(result, out);
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

void transform_point(point result, const point p, const matrix transformation)
{
    int i;
    int k;
    point out;

    for (i = 0; i < 3; ++i) {
        int sum = 0;
        for (k = 0; k < 3; ++k) {
            sum = sum + transformation[i][k] * p[k];
        }
        out[i] = sum;
    }

    copy_point(result, out);
}