#ifndef MATRIX_H
#define MATRIX_H

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(float matrix[3][3]);

/**
 * Initializes an identity matrix.
 * An Identity Matrix is a matrix with ones in the main diagonal, and zeros elsewhere.
 */
void init_identity_matrix(float matrix[3][3]);

/**
 * Print the elements of the matrix.
 */
void print_matrix(const float matrix[3][3]);

/**
 * Adds a matrix and b matrix together and puts it in result.
 */
void add_matrices(const float result[3][3], const float a[3][3], float b[3][3]);

/**
 * Multiplies the matrix by scalar and puts it into result.
 */
void multiply_scalar_matrix(float result[3][3], float scalar, const float matrix[3][3]);

#endif // MATRIX_H

