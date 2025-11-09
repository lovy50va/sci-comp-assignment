Answers

2b) Numerical Stability
At `x = 1.0`, both methods give the correct result: `-5.976000000000000e+03`.

At `x = 999.0`:
- Direct method: Produces incorrect result due to catastrophic cancellation.
- Horner method: Gives accurate result (near zero).

- Conclusion: Horner's method is numerically stable.