### Task 1.a — Mixed-Precision Iterative Refinement

The mixed-precision iterative refinement method was implemented using the
provided matrix utilities in matrix.h and matrix.c, as well as BLAS and
LAPACK routines. The given dense matrix was read from the file
dense_mat.txt in column-major order, as required by LAPACK.

In the implementation, the LU factorization and the corresponding linear
solves were performed in single precision in order to reduce computational
cost. The residual computation r = b − Ax and the update of the solution
vector were carried out in double precision to maintain numerical accuracy.
The input matrix A and vector b were not modified; instead, internal copies
were used.

The algorithm starts by computing an initial solution using a single-precision
LU factorization. In each iteration, the residual is computed in double
precision and its infinity norm is evaluated. If the residual norm falls
below the tolerance τ = 10⁻¹³, the iteration terminates. Otherwise, a
correction equation is solved in single precision and the solution is updated
in double precision.

For the given test case, the method converged within a small number of
iterations (at most 10). The relative backward error

‖x − x̃‖∞ / ‖x‖∞

was close to machine precision, where x̃ denotes the computed solution and
x is the exact solution consisting of all ones. This confirms that the
iterative refinement significantly improves the accuracy of the initial
single-precision solution while keeping the computational cost low.
