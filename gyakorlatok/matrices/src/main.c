#include "matrix.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	float a[3][3] = {
        { 1.0f, -2.0f,  3.1f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
	float b[3][3];
	float c[3][3];

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

	return 0;
}

