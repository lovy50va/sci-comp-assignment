#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "axpy.h"

double wtime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1e6;
}

#ifndef MEASUREMENTS
/* =======================
   Normal mode (Exercise 1b)
   ======================= */
int main(int argc, char *argv[])
{
    int n;
    int repetitions = 50;

    if (argc < 2) {
        printf("Usage: %s n\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    double *x = malloc(n * sizeof(double));
    double *y = malloc(n * sizeof(double));
    double *z = malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        x[i] = 1.0;
        y[i] = 2.0;
    }

    double alpha = 3.0;
    double min_time = 1e9;

    /* Warm-up */
    for (int i = 0; i < 5; i++)
        axpy(n, alpha, x, y, z);

    /* Timed runs */
    for (int i = 0; i < repetitions; i++) {
        double t0 = wtime();
        axpy(n, alpha, x, y, z);
        double t1 = wtime();
        if (t1 - t0 < min_time)
            min_time = t1 - t0;
    }

    printf("Minimum runtime: %f seconds\n", min_time);

    free(x); free(y); free(z);
    return 0;
}

#else
/* =======================
   Measurements mode (Exercise 1d)
   ======================= */
int main(void)
{
    FILE *fp = fopen("measurements.csv", "w");
    int repetitions = 50;
    double alpha = 3.0;

    for (int n = 1000; n <= 2000000; n += 1000) {

        double *x = malloc(n * sizeof(double));
        double *y = malloc(n * sizeof(double));
        double *z = malloc(n * sizeof(double));

        for (int i = 0; i < n; i++) {
            x[i] = 1.0;
            y[i] = 2.0;
        }

        double min_time = 1e9;

        /* Warm-up */
        for (int i = 0; i < 5; i++)
            axpy(n, alpha, x, y, z);

        /* Timed runs */
        for (int i = 0; i < repetitions; i++) {
            double t0 = wtime();
            axpy(n, alpha, x, y, z);
            double t1 = wtime();
            if (t1 - t0 < min_time)
                min_time = t1 - t0;
        }

        fprintf(fp, "%d,%f\n", n, min_time);

        free(x); free(y); free(z);
    }

    fclose(fp);
    return 0;
}
#endif
