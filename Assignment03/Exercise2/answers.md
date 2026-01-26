Task 2.b.3 — Discussion of the Weighted Jacobi Method

The weighted Jacobi method was tested using the provided sparse matrix
test_mat.txt, which was read using the supplied read_coo function. The
initial guess was chosen as the zero vector, and the right-hand side vector
b was set to the vector of all ones.

For ω = 1/3, the method converged, but the convergence was relatively slow.
The small relaxation parameter results in conservative updates of the
solution, which improves stability but increases the number of iterations.

For ω = 2/3, the convergence was significantly faster. In this case, the
relaxation parameter provides a good balance between stability and step size,
leading to a faster reduction of the residual norm.

For ω = 1, corresponding to the standard Jacobi method, the iteration showed
oscillatory behavior and did not converge within the maximum number of
iterations. This indicates that taking the full Jacobi step can lead to
overshooting, even for symmetric positive definite matrices.

These results show that the choice of the relaxation parameter ω has a strong
influence on the convergence behavior of the weighted Jacobi method.
