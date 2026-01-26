#ifndef DENSE_SOLVERS_H
#define DENSE_SOLVERS_H

/**
 * Mixed-precision iterative refinement solver.
 *
 * Solves Ax = b using LU factorization in float precision
 * and iterative refinement in double precision.
 *
 * Parameters:
 *   n       - dimension of A (n x n)
 *   A       - dense matrix (column-major), NOT modified
 *   b       - right-hand side vector, NOT modified
 *   x       - output solution vector (size n)
 *   maxiter - maximum refinement iterations
 *
 * Returns:
 *   0 on success, non-zero on failure.
 */
int mp_iter_refinement(int n, double *A, double *b, double *x, int maxiter);

int basic_lu(int n, double *A, double *b, double *x);

int basic_iter_refinement(int n, double *A, double *b, double *x);

#endif
