#include "matrix_stack.h"
#include <stdio.h>

struct stack* init_matrix_stack()
{
    struct stack *pt = (struct stack*)malloc(sizeof(struct stack));

    pt->top = -1;

    /* If one float is 4 bytes, then a 3x3 matrix is 36 bytes.
    * That means our stack will be 36 * 28 = 1008 bytes, just shy of 1KB.
    * And we will have place for that extra int.
    */
    pt->items = (T_MATRIX*)malloc(sizeof(T_MATRIX) * 28);

    return pt;
}

void free_matrix_stack(struct stack* pt)
{
    free(pt->items);
    free(pt);
}

int matrix_stack_size(struct stack *pt)
{
    return pt->top + 1;
}

int is_matrix_stack_empty(struct stack* pt)
{
    return pt->top == -1;
}

int is_matrix_stack_full(struct stack* pt)
{
    return pt->top == 27;
}

void push_matrix(struct stack* pt, T_MATRIX m)
{
    if (is_matrix_stack_full(pt))
    {
        printf("Matrix Stack Overflow\nProgram Terminated\n");
        fprintf(stderr, "Matrix Stack Overflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    copy_matrix(pt->items[++pt->top], m);
}

void pop_matrix(struct stack* pt, T_MATRIX m)
{
    if (is_matrix_stack_empty(pt))
    {
        printf("Matrix Stack Underflow\nProgram Terminated\n");
        fprintf(stderr, "Matrix Stack Underflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    copy_matrix(m, pt->items[pt->top--]);
}