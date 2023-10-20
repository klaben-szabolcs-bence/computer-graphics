#include "matrix.h"

#include <stdio.h>
#include <math.h>

void init_zero_matrix(T_MATRIX m)
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            m[i][j] = 0.0;
        }
    }
}

void init_identity_matrix(T_MATRIX m)
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

void print_matrix(const T_MATRIX m)
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

void print_point(const T_POINT2D p)
{
    int i;

    for (i = 0; i < 3; ++i) {
        printf("%4.4f ", p[i]);
    }
    printf(" ^ T\n");
}

void copy_matrix(T_MATRIX to, const T_MATRIX from)
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            to[i][j] = from[i][j];
        }
    }
}

void copy_point(T_POINT2D to, const T_POINT2D from)
{
    int i;
    for (i = 0; i < 3; ++i) {
        to[i] = from[i];
    }
}

void transpose_matrix(T_MATRIX result, const T_MATRIX m)
{
    int i;
    int j;
    T_MATRIX out;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            out[i][j] = m[j][i];
        }
    }

    copy_matrix(result, out);
}

void add_matrices(T_MATRIX result, const T_MATRIX a, const T_MATRIX b)
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiply_matrices(T_MATRIX result, const T_MATRIX a, const T_MATRIX b)
{
    int i;
    int j;
    int k;
    T_MATRIX out;

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

void multiply_scalar_matrix(T_MATRIX result, const float scalar, const T_MATRIX m)
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            result[i][j] = m[i][j] * scalar;
        }
    }
}

void transform_point(T_POINT2D result, const T_POINT2D p, const T_MATRIX transformation)
{
    int i;
    int k;
    T_POINT2D out;

    for (i = 0; i < 3; ++i) {
        int sum = 0;
        for (k = 0; k < 3; ++k) {
            sum = sum + transformation[i][k] * p[k];
        }
        out[i] = sum;
    }

    copy_point(result, out);
}

void make_scale_matrix(T_MATRIX m, const float x, const float y)
{
    m[0][0] = m[0][0] * x;
    m[1][1] = m[1][1] * y;
}

void make_shift_matrix(T_MATRIX m, const float x, const float y)
{
    m[0][2] = m[0][2] + x;
    m[1][2] = m[1][2] + y;
}

void make_rotate_matrix(T_MATRIX m, const float alpha)
{
    m[0][0] = cos(alpha);
    m[0][1] = sin(alpha);
    m[1][0] = -1 * sin(alpha);
    m[1][1] = cos(alpha);
}