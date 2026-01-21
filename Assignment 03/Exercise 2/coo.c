void spmv(const COOMatrix *A, const double *x, double *y)
{
    for (int i = 0; i < A->nrows; i++)
        y[i] = 0.0;

    for (int k = 0; k < A->nnz; k++)
        y[A->row[k]] += A->val[k] * x[A->col[k]];
}

void coo_extract_diag(const COOMatrix *A, double *d)
{
    for (int i = 0; i < A->nrows; i++)
        d[i] = 0.0;

    for (int k = 0; k < A->nnz; k++)
        if (A->row[k] == A->col[k])
            d[A->row[k]] = A->val[k];
}

double norm2(const double *x, int n)
{
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += x[i] * x[i];
    return sqrt(sum);
}

void zeros(double *x, int n)
{
    for (int i = 0; i < n; i++)
        x[i] = 0.0;
}

void ones(double *x, int n)
{
    for (int i = 0; i < n; i++)
        x[i] = 1.0;
}
