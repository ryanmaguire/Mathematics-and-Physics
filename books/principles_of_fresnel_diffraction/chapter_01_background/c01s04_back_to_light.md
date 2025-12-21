# Back to Light
While it is worthwhile investigating thermodynamics
and the heat equation, our current objective is to solve the
*wave equation*, not the heat equation. We mimic Fourier's
method, now known as the method of *separation of variables*,
and try and derive a solution to the wave equation.

Let us shift the notation from $\mathbf{E}(\mathbf{r},\,t)$
and $\mathbf{B}(\mathbf{r},\,t)$, where
$\mathbf{r}=(x,\,y,\,z)$ denotes a point in space,
to a new variable $\psi$. The wave equation is:

$$
    \displaystyle
    \nabla^{2}\psi(\mathbf{r},\,t)
    -
    \frac{1}{c^{2}}
    \frac{\partial^{2}\psi}{\partial{t}^{2}}(\mathbf{r},\,t)
    =
    0
$$

We again try to use separation of variables, writing:

$$
    \psi(\mathbf{r},\,t)
    =U(\mathbf{r})T(t)
$$

Separating the wave equation, we obtain:

$$
    \frac{\nabla^{2}U(\mathbf{r})}{U(\mathbf{r})}
    =\frac{1}{c^{2}T(t)}
        \frac{\partial{T}}{\partial{t}}(t)
$$

We again argue that since the left side depends only on
$\mathbf{r}$, whereas the right-hand side varies only with
$t$, that both sides are indeed constant. We set this
constant to $-k^{2}$, and the spatial component
becomes:

$$
    \nabla^{2}U(\mathbf{r})+k^{2}U(\mathbf{r})=0
$$

This is the **Helmholtz Equation**, which is also known as the
**Time-Independent Wave Equation**. The are various methods of
tackling this problem, including using separation of variables
*again*. Depending on the coordinate system we use
(spherical, cylindrical, Cartesian, or other stranger systems),
we may arrive at a system of equations that are easier to handle.
*Bessel functions* arise naturally from this method.
