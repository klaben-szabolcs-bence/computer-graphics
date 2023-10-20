#ifndef MATRICES_MATRIX_STACK_H
#define MATRICES_MATRIX_STACK_H

#include "matrix.h"
#include "stdlib.h"

/**
 * Data structure to represent a stack.
 */
struct stack
{
    int top;
    T_MATRIX* items;
};

/**
 * Utility function to initialize a stack.
 * @return Pointer to a stack
 */
struct stack* init_matrix_stack();

/**
 * Utility function to return the size of the stack.
 */
int matrix_stack_size(struct stack *pt);

/**
 * Utility function to check if the stack is empty.
 * @return bool
 */
int is_matrix_stack_empty(struct stack* pt);

/**
 * Utility function to check if the stack is full.
 * @return bool
 */
int is_matrix_stack_full(struct stack* pt);

/**
 * Function to push a matrix onto the stack.
 * @param pt Pointer to stack
 * @param m The matrix to push
 */
void push_matrix(struct stack* pt, T_MATRIX m);

/**
 * Function to pop a matrix of the stack.
 * @param pt Pointer to the stack
 * @param m Place to put the popped of matrix
 */
void pop_matrix(struct  stack* pt, T_MATRIX m);

#endif //MATRICES_MATRIX_STACK_H
