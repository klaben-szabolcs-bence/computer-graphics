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
 * Transposes the given matrix.
 */
void transpose_matrix(T_MATRIX result, const T_MATRIX m);

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

/**
 * Takes a transformation matrix and applies scaling to it.
 * @warning They stack on top of each other.
 * @param x Scaling factor on the x-asis. (lambda)
 * @param y Scaling factor on the y-axis. (mu)
 */
void make_scale_matrix(T_MATRIX m, const float x, const float y);

/**
 * Takes a transformation matrix and applies shifting to it.
 * @warning They stack on top of each other.
 * @param x Shifting distance on the x-asis.
 * @param y Shifting distance on the y-axis.
 */
void make_shift_matrix(T_MATRIX m, const float x, const float y);

/**
 * Takes a transformation matrix and applies rotation to it.
 * @warning This shouldn't be used together with the others, as it overwrites the matrix.
 * @param alpha in radians (Reminder: counter-clockwise is positive)
 */
void make_rotate_matrix(T_MATRIX m, const float alpha);
#endif // MATRIX_H

