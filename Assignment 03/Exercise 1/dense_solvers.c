#include <stdlib.h>
#include <math.h>
#include <cblas.h>
#include <lapacke.h>
#include "dense_solvers.h"

int mp_iter_refinement(int n, double *A, double *b, double *x, int maxiter)
{
    const double tau = 1e-13;

    /* Make copies of A and b (must not modify originals) */
    double *A_d = malloc(n * n * sizeof(double));
    double *b_d = malloc(n * sizeof(double));
    for (int i = 0; i < n * n; i++) A_d[i] = A[i];
    for (int i = 0; i < n; i++) b_d[i] = b[i];

    /* Convert to single precision */
    float *A_s = malloc(n * n * sizeof(float));
    float *b_s = malloc(n * sizeof(float));
    LAPACKE_dlag2s(LAPACK_COL_MAJOR, n, n, A_d, n, A_s, n);
    LAPACKE_dlag2s(LAPACK_COL_MAJOR, n, 1, b_d, n, b_s, n);

    /* LU factorization (single precision) */
    int *ipiv = malloc(n * sizeof(int));
    if (LAPACKE_sgetrf(LAPACK_COL_MAJOR, n, n, A_s, n, ipiv) != 0)
        return 1;

    /* Initial solve */
    if (LAPACKE_sgetrs(LAPACK_COL_MAJOR, 'N',
                       n, 1, A_s, n, ipiv, b_s, n) != 0)
        return 2;

    /* Convert initial solution to double */
    LAPACKE_slag2d(LAPACK_COL_MAJOR, n, 1, b_s, n, x, n);

    double *r = malloc(n * sizeof(double));
    float  *r_s = malloc(n * sizeof(float));
    float  *d_s = malloc(n * sizeof(float));
    double *d   = malloc(n * sizeof(double));

    for (int it = 0; it < maxiter; it++)
    {
        /* r = b - A*x */
        for (int i = 0; i < n; i++)
            r[i] = b[i];

        cblas_dgemv(CblasColMajor, CblasNoTrans,
                    n, n, -1.0, A, n, x, 1, 1.0, r, 1);

        /* Infinity norm */
        double norm_inf = 0.0;
        for (int i = 0; i < n; i++)
            norm_inf = fmax(norm_inf, fabs(r[i]));

        if (norm_inf < tau)
            break;

        /* Solve Ad = r in single precision */
        LAPACKE_dlag2s(LAPACK_COL_MAJOR, n, 1, r, n, r_s, n);
        for (int i = 0; i < n; i++)
            d_s[i] = r_s[i];

        LAPACKE_sgetrs(LAPACK_COL_MAJOR, 'N',
                       n, 1, A_s, n, ipiv, d_s, n);

        LAPACKE_slag2d(LAPACK_COL_MAJOR, n, 1, d_s, n, d, n);

        /* Update x */
        for (int i = 0; i < n; i++)
            x[i] += d[i];
    }

    free(A_d); free(b_d); free(A_s); free(b_s);
    free(ipiv); free(r); free(r_s); free(d_s); free(d);
    return 0;
}
