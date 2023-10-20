#include "matrix.h"
#include <math.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	T_MATRIX a = {
        { 1.0f, -2.0f,  3.1f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
	T_MATRIX b;
	T_MATRIX c;

    init_zero_matrix(b);
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;

    printf("Matrix a:\n");
    print_matrix(a);
    printf("Matrix b:\n");
    print_matrix(b);
    
    add_matrices(c, a, b);
    printf("The a and b matrices added together and stored in c:\n");
    print_matrix(c);

    init_identity_matrix(a);
    printf("Identity matrix stored in a:\n");
    print_matrix(a);

    multiply_scalar_matrix(b, 1000, b);
    printf("The b matrix multiplied by scalar and stored in b:\n");
    print_matrix(b);

    multiply_matrices(a, b, c);
    printf("The b and c matrices multiplied together and stored in a:\n");
    print_matrix(a);

    transpose_matrix(a, a);
    printf("The a matrix transposed and stored in a:\n");
    print_matrix(a);

    T_POINT2D p = {3, 2, 1};
    printf("The p point:\n");
    print_point(p);

    transform_point(p, p, a);
    printf("The p point transposed by a:\n");
    print_point(p);

    p[0] = 2;
    p[1] = 2;
    p[2] = 1;
    printf("Set p point to:\n");
    print_point(p);

    T_MATRIX transformation_matrix;
    init_identity_matrix(transformation_matrix);
    make_scale_matrix(transformation_matrix, 2, 4);
    transform_point(p, p, transformation_matrix);
    printf("The p point scaled by 2 on x and by 4 on the y axis,\n"
           "and stored in p:\n");
    print_point(p);

    init_identity_matrix(transformation_matrix);
    make_shift_matrix(transformation_matrix, 4, 2);
    transform_point(p, p, transformation_matrix);
    printf(
           "The p point shifted by 4 on the x and by 2 on the y axis,\n"
           "and stored in p:\n");
    print_point(p);

    init_identity_matrix(transformation_matrix);
    make_rotate_matrix(transformation_matrix, 1.0471975512);
    print_matrix(transformation_matrix);
    transform_point(p, p, transformation_matrix);
    printf("The p point rotated by 60 degrees around origin,\n"
           "and stored in p:\n");
    print_point(p);
    printf("This should be [-4.6603, 11.9282, 1]^T, but sometimes computers are worse at math than humans.\n");

	return 0;
}

