#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <cblas.h>
#include "matrix.h"


int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    if (argc != 2) return 1;
    Matrix A;
    if (parse_matrix(argv[1], &A)) {
        fprintf(stderr, "Matrix file '%s' is invalid or does not exist.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    assert(A.ncols == A.nrows);
    int n = A.nrows;

    // init vector x
    Matrix x;
    x.nrows=n; x.ncols=1;
    x.data = malloc(n*sizeof(double));
    if (!x.data) return 1;
    for (int i=0; i<n; i++) x.data[i] = 1;

    // init vector b
    Matrix b;
    b.nrows=n;
    b.ncols=1;
    b.data = malloc(n*sizeof(double));
    if (!b.data) return 1;

    cblas_dgemv(CblasColMajor, CblasNoTrans, n, n, 1, A.data, n, x.data, 1, 0, b.data, 1);

    // your implementation

    print_matrix("A", &A);
    print_matrix("x", &x);
    print_matrix("b", &b);

    free_matrix(&A);
    free_matrix(&x);
    free_matrix(&b);

    return 0;
}