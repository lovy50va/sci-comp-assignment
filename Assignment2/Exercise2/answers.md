# Exercise 2: Numerical Differentiation Observations

## Task a) Comparison of Central Difference and Complex Step

We evaluated the derivative of $f(x)$ at $x = \pi/4$ using two methods across step sizes $h = 10^{-1}$ to $10^{-16}$.

### Observations

*1. Central Difference Method ($D_1$):*
* *Behavior:* The error for the central difference method initially decreases as $h$ becomes smaller (from $10^{-1}$ down to approximately $10^{-8}$). However, after reaching a minimum error (optimal step size), the error drastically increases as $h$ continues to decrease towards $10^{-16}$.
* *Explanation:* This behavior creates a "V-shape" in the error plot.
    * [cite_start]*Regime 1 (Large $h$):* The error is dominated by *truncation error* ($O(h^2)$), which decreases as $h$ decreases[cite: 165].
    * *Regime 2 (Very small $h$):* The error is dominated by *rounding error* due to *subtractive cancellation*. The formula involves calculating $f(x+h) - f(x-h)$. As $h \to 0$, these two terms become nearly identical. [cite_start]Subtracting them in floating-point arithmetic causes a loss of significant digits, leading to large numerical errors[cite: 171].

*2. Complex Step Method ($D_2$):*
* *Behavior:* The error for the complex step method decreases monotonically as $h$ decreases, maintaining high accuracy even for extremely small step sizes like $h = 10^{-16}$.
* *Explanation:* The complex step approximation is $D_2(h) = \frac{Im(f(x+ih))}{h}$.
    * Unlike the central difference method, this formula *does not involve subtraction* in the numerator.
    * Therefore, it is not subject to subtractive cancellation errors. [cite_start]The method remains numerically stable and limited only by the machine precision, allowing it to achieve accuracy close to the floating-point limit[cite: 169].

### Conclusion
[cite_start]While both methods are theoretically second-order accurate ($O(h^2)$) in exact arithmetic[cite: 171], the *Complex Step method is numerically superior* for very small step sizes because it avoids the catastrophic cancellation inherent in finite difference methods.

## Task b) Bad Implementation

We repeated the experiment using a "polluted" function:
$f_{polluted}(x) = f(x+10^{-16}i) + f(x) - f(x+10^{-16}i)$.

### Observations

*1. Central Difference Method ($D_1$):*
* *Behavior:* The behavior is largely unchanged compared to Part A. It still exhibits the characteristic "V-shape" error curve.
* *Explanation:* The central difference method relies on the *real part* of the function values: $f(x+h) - f(x-h)$. Since the "pollution" mainly affects the imaginary part (or adds negligible noise to the real part relative to the step size $h$ until $h$ is extremely small), the central difference method is indifferent to this specific type of contamination.

*2. Complex Step Method ($D_2$):*
* *Behavior:* The accuracy is destroyed. Instead of the error decreasing monotonically to $10^{-16}$, it now follows a "V-shape" similar to or worse than the Central Difference method.
* *Explanation:*
    * The Complex Step method calculates $D_2(h) = Im(f(x+ih))/h$.
    * The "pollution" introduces a noise term of magnitude $\approx 10^{-16}$ into the imaginary part of $f(x)$.
    * When $h$ is large (e.g., $10^{-1}$), dividing this tiny noise by $h$ is negligible.
    * However, as $h$ becomes very small (e.g., $10^{-16}$), we are dividing the noise ($\approx 10^{-16}$) by $h$ ($\approx 10^{-16}$), resulting in an error of magnitude $O(1)$.
    * *Conclusion:* The Complex Step method is extremely sensitive to the implementation of the function $f$. It requires $f$ to be "analytic" in the coding sense—operations must not mix real and imaginary parts via noise or incorrect complex arithmetic.
    
## Task c) Forward Error Analysis

We analyze the total error, composed of *Truncation Error* (mathematical approximation) and *Forward Error* (floating-point rounding).

Let $u$ be the unit roundoff (approx. $1.11 \times 10^{-16}$ for double precision). We assume the standard model for function evaluation:
$fl(f(x)) = f(x)(1 + \delta)$, where $|\delta| \leq u$.

### 1. Central Difference Method ($D_1$)

*Forward Error Derivation:*
The computed central difference is:
$$\hat{D}_1(h) = \frac{fl(f(x+h)) - fl(f(x-h))}{2h} = \frac{f(x+h)(1+\delta_1) - f(x-h)(1+\delta_2)}{2h}$$
Rearranging the terms:
$$\hat{D}_1(h) = D_1(h) + \frac{f(x+h)\delta_1 - f(x-h)\delta_2}{2h}$$
Assuming $h$ is small, $f(x+h) \approx f(x-h) \approx f(x)$. The absolute forward error is bounded by:
$$|\hat{D}_1(h) - D_1(h)| \leq \frac{|f(x)|u + |f(x)|u}{2h} = \frac{|f(x)|u}{h}$$

*Total Error Bound:*
Combining with the truncation error ($Ch^2$), the total error is:
$$E_{total}^{(1)}(h) \approx Ch^2 + \frac{|f(x)|u}{h}$$

*Observation:*
As $h \to 0$, the truncation term ($Ch^2$) vanishes, but the rounding term ($\frac{|f(x)|u}{h}$) tends to infinity. This explains the "V-shape" and the explosion of error for very small $h$.

### 2. Complex Step Method ($D_2$)

*Forward Error Derivation:*
The computed complex step is:
$$\hat{D}_2(h) = \frac{Im(fl(f(x+ih)))}{h}$$
Using the standard model where the perturbation $\delta$ is real (as given in the handout hint):
$$fl(f(x+ih)) = f(x+ih)(1+\delta)$$
Taking the imaginary part:
$$Im(fl(f(x+ih))) = Im(f(x+ih)) + Im(f(x+ih))\delta$$
Substituting this back into the formula:
$$\hat{D}_2(h) = \frac{Im(f(x+ih))}{h} + \frac{Im(f(x+ih))\delta}{h} = D_2(h) + D_2(h)\delta$$
Since $D_2(h) \approx f'(x)$, the forward error is:
$$|\hat{D}_2(h) - D_2(h)| \approx |f'(x)\delta| \leq |f'(x)|u$$

*Total Error Bound:*
$$E_{total}^{(2)}(h) \approx Ch^2 + |f'(x)|u$$

*Observation:*
The rounding error term $|f'(x)|u$ is *independent of $h$*. As $h \to 0$, the error does not explode; it simply settles at the machine precision limit ($\approx 10^{-16}$). This explains why the Complex Step method is numerically stable for arbitrarily small $h$.

### 3. Optimal Step Size for Central Difference

To find the optimal $h$ for Central Difference, we minimize the total error $E(h) = Ch^2 + \frac{|f(x)|u}{h}$ with respect to $h$.
Setting the derivative to zero:
$$\frac{dE}{dh} = 2Ch - \frac{|f(x)|u}{h^2} = 0 \implies h_{opt} = \sqrt[3]{\frac{|f(x)|u}{2C}}$$

This implies that the optimal step size scales with the cube root of machine epsilon:
$$h_{opt} \sim u^{1/3} \approx (10^{-16})^{1/3} \approx 10^{-5.3}$$

*Conclusion:*
Our theoretical optimal step size is roughly $h \approx 10^{-5}$ to $10^{-6}$. This matches our numerical observations in Part a), where the error was lowest around $h = 10^{-5}$ before increasing again.
