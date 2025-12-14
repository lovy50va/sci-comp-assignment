#include "axpy.h"

void axpy(int n, double alpha, double *x, double *y, double *z)
{
    for (int i = 0; i < n; i++) {
        z[i] = alpha * x[i] + y[i];
    }
}
