#include <stdio.h>
#include <math.h>

double eval_poly(int n, double *a, double x) {
    double r = 0.0;
    for (int i = 0; i <= n; i++) r += a[i] * pow(x, i);
    return r;
}

double eval_horner(int n, double *a, double x) {
    double r = a[n];
    for (int i = n-1; i >= 0; i--) r = r * x + a[i];
    return r;
}

int main() {
    double c[] = {-998,-998,-998,-998,-998,-998,1};
    printf("x=1.0:\n  Direct: %.15e\n  Horner: %.15e\n",
           eval_poly(6,c,1.0), eval_horner(6,c,1.0));
    printf("x=999.0:\n  Direct: %.15e\n  Horner: %.15e\n",
           eval_poly(6,c,999.0), eval_horner(6,c,999.0));
    return 0;
}