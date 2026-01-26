#include <stdlib.h>
#include "solvers.h"

int w_jacobi(const COOMatrix *A, const double *b,
             double omega, double *x, double *res)
{
    int n = A->nrows;

    double *Ax = malloc(n * sizeof(double));
    double *r  = malloc(n * sizeof(double));
    double *D  = malloc(n * sizeof(double));

    coo_extract_diag(A, D);

    for (int it = 0; it < 5000; it++)
    {
        spmv(A, x, Ax);

        for (int i = 0; i < n; i++)
            r[i] = b[i] - Ax[i];

        *res = norm2(r, n);
        if (*res < 1e-6)
        {
            free(Ax); free(r); free(D);
            return it;
        }

        for (int i = 0; i < n; i++)
            x[i] += omega * r[i] / D[i];
    }

    free(Ax); free(r); free(D);
    return 5000;
}
