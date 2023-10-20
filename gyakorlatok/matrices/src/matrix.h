#ifndef MATRIX_H
#define MATRIX_H

typedef float matrix[3][3];

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(matrix m);

/**
 * Initializes an identity matrix.
 * An Identity Matrix is a matrix with ones in the main diagonal, and zeros elsewhere.
 */
void init_identity_matrix(matrix m);

/**
 * Print the elements of the matrix.
 */
void print_matrix(const matrix m);

/**
 * Adds a matrix and b matrix together and puts it in result.
 */
void add_matrices(matrix result, const matrix a, const matrix b);

/**
 * Multiplies a matrix and b matrix together and puts it in result.
 */
void multiply_matrices(matrix result, const matrix a, const matrix b);

/**
 * Multiplies the matrix by scalar and puts it into result.
 */
void multiply_scalar_matrix(matrix result, const float scalar, const matrix m);

#endif // MATRIX_H

