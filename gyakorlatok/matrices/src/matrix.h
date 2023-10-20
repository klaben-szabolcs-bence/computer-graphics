#ifndef MATRIX_H
#define MATRIX_H

typedef float T_MATRIX[3][3];
typedef float T_POINT2D[3];

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(T_MATRIX m);

/**
 * Initializes an identity matrix.
 * An Identity Matrix is a matrix with ones in the main diagonal, and zeros elsewhere.
 */
void init_identity_matrix(T_MATRIX m);

/**
 * Print the elements of the matrix.
 */
void print_matrix(const T_MATRIX m);

/**
 * Print the elements of the point.
 */
void print_point(const T_POINT2D p);

/**
 *  Copies a matrix from one place to another.
 */
void copy_matrix(T_MATRIX to, const T_MATRIX from);

/**
 * Copies a point from one place to another.
 */
void copy_point(T_POINT2D to, const T_POINT2D from);

/**
 * Adds a matrix and b matrix together and puts it in result.
 */
void add_matrices(T_MATRIX result, const T_MATRIX a, const T_MATRIX b);

/**
 * Multiplies a matrix and b matrix together and puts it in result.
 */
void multiply_matrices(T_MATRIX result, const T_MATRIX a, const T_MATRIX b);

/**
 * Multiplies the matrix by scalar and puts it into result.
 */
void multiply_scalar_matrix(T_MATRIX result, const float scalar, const T_MATRIX m);

/**
 * Takes p point in the homogenous coordinate-system and applies the transformation matrix on it.
 */
void transform_point(T_POINT2D result, const T_POINT2D p, const T_MATRIX transformation);

#endif // MATRIX_H

