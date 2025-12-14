### Exercise 1(b)

Individual runtime measurements of the axpy operation vary due to factors such as
CPU frequency scaling, cache effects, operating system scheduling, and background
processes. Therefore, a single measurement is not reliable.

To obtain a single but trustworthy runtime measurement, the axpy function is
executed multiple times. First, several warm-up runs are performed without timing
to ensure that the data and instructions are loaded into the cache and the CPU
operates at a stable frequency.

After the warm-up phase, the execution time is measured repeatedly (50 times).
From these measurements, the minimum runtime is selected. The minimum value is
considered the most reliable estimate because it corresponds to a run with minimal
system interference.

This approach reduces the impact of external factors and yields a trustworthy
measurement of the axpy performance.

### Exercise 1(c)

From the plots, it can be observed that the runtime of the axpy operation increases
as the vector size n increases, but the increase is not linear. Instead, the plots
show different regions with distinct slopes.

For small vector sizes, the runtime grows slowly. This indicates that the data fits
entirely into the CPU cache (such as L1 or L2 cache), where memory access is very fast.
As the vector size increases beyond the cache capacity, the runtime increases more
rapidly. This change in slope suggests that data is fetched from slower levels of the
memory hierarchy, such as L3 cache or main memory (RAM).

The different plots show similar qualitative behavior but differ in absolute runtime
values. This is due to differences in hardware, such as CPU speed, cache sizes, and
memory bandwidth on the four computers. The different y-axis scales further emphasize
that each system has a different performance level.

It is possible to infer qualitative information about the memory hierarchy from the
plots, such as the presence of cache effects and memory bandwidth limitations.
However, exact cache sizes or memory specifications cannot be determined solely from
these plots.

Although the vector length increases linearly, the runtime does not increase linearly
because memory access time is not constant. Once the working data exceeds cache
capacity, memory accesses become slower, leading to a superlinear increase in runtime.
Additionally, effects such as memory bandwidth saturation and cache misses contribute
to this non-linear behavior.
