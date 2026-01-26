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

For the given test case, the method converged in *6 iterations*.
The relative backward error

‖x − x̃‖∞ / ‖x‖∞ = 1.256108816960477 × 10⁻⁸

where x̃ denotes the computed solution and x is the exact solution consisting
of all ones.

The first few entries of the computed solution were:

x̃[0] = 1.0000000008 
x̃[1] = 1.0000000051 
x̃[2] = 1.0000000008 
x̃[3] = 1.0000000075 
x̃[4] = 1.0000000060 

This confirms that the iterative refinement significantly improves the
accuracy of the initial single-precision solution while keeping the
computational cost low.

---

## Exercise 1.b — Runtime and Residual Comparison

In this part, we implemented two additional solvers:

- *basic_lu*: direct LU solve using DGETRF + DGETRS
- *basic_iter_refinement*: LU solve with double-precision iterative refinement using DGERFS

All three methods were compared on the provided dense matrix dense_mat.txt
in terms of runtime and relative backward error.

### Measurements

The results were written to measurements.csv in the required format:

| Function                 | Runtime (s) | Residual / Backward Error |
|--------------------------|------------:|--------------------------:|
| mp_iter_refinement       | 0.000579    | 1.256109 × 10⁻⁸          |
| basic_lu                 | 0.000654    | 1.736389 × 10⁻¹⁰         |
| basic_iter_refinement    | 0.000392    | 1.451731 × 10⁻¹⁰         |

### Observations

- The mixed-precision method converged quickly (6 iterations) and achieved
  a reasonable accuracy, but its residual was larger than the pure double-precision methods.

- The *basic LU solver* produced a more accurate solution than the mixed-precision
  method, with a residual on the order of 10⁻¹⁰.

- The *LAPACK iterative refinement solver* gave the smallest residual and was also
  the fastest in this test.

- Overall, iterative refinement improves numerical accuracy compared to a basic LU solve,
  while mixed precision provides a trade-off between speed and accuracy.
