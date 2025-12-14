#include <stdio.h>
#include <math.h>
#include <complex.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* Implements f(x) = e^x / (sin(x)^3 + cos(x)^3) */
double complex cf(double complex x) {
    return cexp(x) / (cpow(csin(x), 3) + cpow(ccos(x), 3));
}

/* Bad implementation of f(x) that introduces numerical noise */
double complex cf_polluted(double complex x) {
    double complex perturbation = x + 1e-16 * I;
    double complex term1 = cf(perturbation);
    double complex term2 = cf(x);
    return term1 + term2 - term1;
}

/* Central Difference Approximation */
double central_diff(double complex (*f)(double complex), double x, double h) {
    double complex f_plus = f(x + h);
    double complex f_minus = f(x - h);
    return creal((f_plus - f_minus) / (2.0 * h));
}

/* Complex Step Approximation */
double complex_step(double complex (*f)(double complex), double x, double h) {
    double complex z = x + h * I;
    return cimag(f(z)) / h;
}

int main() {
    double x = M_PI / 4.0;
    double exact_derivative = sqrt(2.0) * exp(M_PI / 4.0);
    
    FILE *fp = fopen("numerical_diff.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    /* PART A: Clean Implementation */
    fprintf(fp, "--- PART A: Clean Implementation ---\n");
    fprintf(fp, "%-10s %-20s %-20s %-20s %-20s\n", 
            "h", "D_1(h)", "error(D_1)", "D_2(h)", "error(D_2)");
            
    for (double k = 1.0; k <= 16.0; k += 0.5) {
        double h = pow(10.0, -k);
        
        double d1 = central_diff(cf, x, h);
        double d2 = complex_step(cf, x, h);
        
        double err1 = fabs(d1 - exact_derivative);
        double err2 = fabs(d2 - exact_derivative);
        
        fprintf(fp, "%.5e % .15e %.15e % .15e %.15e\n", 
                h, d1, err1, d2, err2);
    }

    /* PART B: Polluted Implementation */
    fprintf(fp, "\n--- PART B: Polluted Implementation ---\n");
    fprintf(fp, "%-10s %-20s %-20s %-20s %-20s\n", 
            "h", "D_1(h)", "error(D_1)", "D_2(h)", "error(D_2)");

    for (double k = 1.0; k <= 16.0; k += 0.5) {
        double h = pow(10.0, -k);
        
        double d1 = central_diff(cf_polluted, x, h);
        double d2 = complex_step(cf_polluted, x, h);
        
        double err1 = fabs(d1 - exact_derivative);
        double err2 = fabs(d2 - exact_derivative);
        
        fprintf(fp, "%.5e % .15e %.15e % .15e %.15e\n", 
                h, d1, err1, d2, err2);
    }
    
    fclose(fp);
    printf("Results written to numerical_diff.txt\n");
    
    return 0;
}
