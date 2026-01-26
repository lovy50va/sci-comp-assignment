#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <cblas.h>
#include "matrix.h"
#include "dense_solvers.h"
#include <math.h>
#include <lapacke.h>
#include <time.h>


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

/* =============================================== */
    /* Exercise 1.b – Compare 3 Dense Solvers */
    /* =============================================== */

    double *x_mp   = calloc(n, sizeof(double));
    double *x_lu   = calloc(n, sizeof(double));
    double *x_ref  = calloc(n, sizeof(double));

    if (!x_mp || !x_lu || !x_ref) return 1;

    clock_t start, end;
    double t_mp, t_lu, t_ref;

    /* ---------- Solver 1: Mixed Precision ---------- */
    start = clock();
    mp_iter_refinement(n, A.data, b.data, x_mp, 20);
    end = clock();
    t_mp = (double)(end - start) / CLOCKS_PER_SEC;

    /* ---------- Solver 2: Basic LU Solve ---------- */
    start = clock();
    basic_lu(n, A.data, b.data, x_lu);
    end = clock();
    t_lu = (double)(end - start) / CLOCKS_PER_SEC;

    /* ---------- Solver 3: LAPACK Iter Refinement ---------- */
    start = clock();
    basic_iter_refinement(n, A.data, b.data, x_ref);
    end = clock();
    t_ref = (double)(end - start) / CLOCKS_PER_SEC;

    /* ---------- Compute backward error ---------- */
    double err_mp = 0.0, err_lu = 0.0, err_ref = 0.0;

    for (int i = 0; i < n; i++) {
        err_mp  = fmax(err_mp,  fabs(x_mp[i]  - 1.0));
        err_lu  = fmax(err_lu,  fabs(x_lu[i]  - 1.0));
        err_ref = fmax(err_ref, fabs(x_ref[i] - 1.0));
    }

    /* ---------- Write measurements.csv ---------- */
    FILE *fp = fopen("measurements.csv", "w");
    if (!fp) {
        printf("Error: could not open measurements.csv\n");
        return 1;
    }

    fprintf(fp, "function,runtime in s,residual\n");
    fprintf(fp, "mp_iter_refinement,%f,%e\n", t_mp, err_mp);
    fprintf(fp, "basic_lu,%f,%e\n", t_lu, err_lu);
    fprintf(fp, "basic_iter_refinement,%f,%e\n", t_ref, err_ref);

    fclose(fp);

    printf("\n=== Exercise 1.b Results ===\n");
    printf("Measurements written to measurements.csv\n");

    printf("mp_iter_refinement: runtime = %f s, residual = %e\n", t_mp, err_mp);
    printf("basic_lu          : runtime = %f s, residual = %e\n", t_lu, err_lu);
    printf("basic_iter_refine : runtime = %f s, residual = %e\n", t_ref, err_ref);

    /* Free solver arrays */
    free(x_mp);
    free(x_lu);
    free(x_ref);

    free_matrix(&A);
    free_matrix(&x);
    free_matrix(&b);

    return 0;
}
