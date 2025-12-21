# Returning to Heat
Let us briefly return to heat. The solution is:

$$
    \displaystyle
    u(x,\,t)
    =\sum_{n=1}^{\infty}a_{n}
        \sin\left(\frac{n\pi{x}}{L}\right)
        \exp\left(-\frac{n^{2}\pi^{2}\alpha{t}}{L^{2}}\right)
$$

Given the *boundary condition* $u(x,\,0)=f(x)$, this reduces to:

$$
    \displaystyle
    f(x)
    =\sum_{n=1}^{\infty}a_{n}
        \sin\left(\frac{n\pi{x}}{L}\right)
$$

This is called a **Fourier series**. In particular, this is the Fourier
expansion for the function $f$. How do we determine what the coefficients are?
We first note that the sine function satisfies a certain *orthogonality condition*.
That is, for integers $m$ and $n$, we have:

$$
    \displaystyle
    \frac{2}{L}\int_{0}^{L}
        \sin\left(\frac{n\pi{x}}{L}\right)
        \sin\left(\frac{m\pi{x}}{L}\right)\,
        \textrm{d}x
    =\begin{cases}
        1,&m=n\\
        0,&m\ne{n}
    \end{cases}
$$

The right-hand side is common enough to warrant a notation.
The *Kronecker-$\delta$* function is defined via:

$$
    \displaystyle
    \delta_{m,\,n}
    =\begin{cases}
        1,&m=n\\
        0,&m\ne{n}
    \end{cases}
$$

We can use this property to develop a formula for the coefficients
of the Fourier expansion. First, we assume that $f$ is a *nice*
function, meaning we can swap sums and integrals at will. We write:

$$
    \begin{array}{lrcl}
        &
        \displaystyle
        f(x)\sin\left(\frac{m\pi{x}}{L}\right)
        &=&
        \displaystyle
        \sum_{n=1}^{\infty}
        a_{n}\sin\left(\frac{n\pi{x}}{L}\right)
            \sin\left(\frac{m\pi{x}}{L}\right)\\
        \Longrightarrow
        &
        \displaystyle
        \int_{0}^{L}f(x)
            \sin\left(\frac{m\pi{x}}{L}\right)\,
            \textrm{d}x
        &=&
        \displaystyle
        \int_{0}^{L}
            \sum_{n=1}^{\infty}
                a_{n}\sin\left(\frac{n\pi{x}}{L}\right)
                \sin\left(\frac{m\pi{x}}{L}\right)\,
                \textrm{d}x\\
        \Longrightarrow
        &
        \displaystyle
        \int_{0}^{L}f(x)
            \sin\left(\frac{m\pi{x}}{L}\right)\,
            \textrm{d}x
        &=&
        \displaystyle
        \sum_{n=1}^{\infty}
            a_{n}
            \int_{0}^{L}
                \sin\left(\frac{n\pi{x}}{L}\right)
                \sin\left(\frac{m\pi{x}}{L}\right)\,
                \textrm{d}x\\
        \Longrightarrow
        &
        \displaystyle
        \int_{0}^{L}f(x)
            \sin\left(\frac{m\pi{x}}{L}\right)\,
            \textrm{d}x
        &=&
        \displaystyle
        \sum_{n=1}^{\infty}a_{n}\frac{L\delta_{m,\,n}}{2}\\
        \Longrightarrow
        &
        \displaystyle
        a_{m}
        &=&
        \displaystyle
        \frac{2}{L}
        \int_{0}^{L}f(x)
            \sin\left(\frac{m\pi{x}}{L}\right)\,
            \textrm{d}x
    \end{array}
$$

So, does this work? Let's try an example.
Consider $f:[0,\,1]\rightarrow\mathbb{R}$ give by:

$$
    f(x)=x(1-x)
$$

Simple enough, and it satisfies $f(0)=0$ and $f(1)=0$.
The Fourier coefficients are then:

$$
    \begin{array}{rcl}
        \displaystyle
        a_{n}
        &=&
        \displaystyle
        2\int_{0}^{1}x(1-x)\sin(n\pi{x})\,
            \textrm{d}x\\
        \displaystyle
        &=&
        \displaystyle
        \frac{4}{\pi^{3}}
        \frac{1-(-1)^{n}}{n^{3}}
    \end{array}
$$

We can implement this in a short Python script.

```{literalinclude}  pysrc/fourier_series_example.py
:lang: python
:caption: Fourier Series in Python
:start-line:31
```

This produces the image below.

:::{figure} images/fourier_series_example.png
Fourier Series Example
:::

## The Validity of the Heat Equation

A slight digression, having now found the solution to the
heat equation, we may ask if it serves as a realistic model
for *heat*. The answer is **no**.
Suppose we start with a step function:

$$
    f(x)=
    \begin{cases}
        1,&0\leq{x}\leq\frac{L}{2}\\
        0,&\frac{L}{2}<x\leq{L}
    \end{cases}
$$

We can solve for $u$ using *finite-differences*.
The first partial derivative is numerically given by:

$$
    \frac{\partial{u}}{\partial{x}}
    \approx
    \frac{u(x+\Delta{x},\,t)}{\Delta{x}}
$$

where $\Delta{x}$ is a (relatively) small quantity.
The second partial derivative is then approximated
by the following:

$$
    \begin{array}{rcl}
        \displaystyle
        \frac{\partial^{2}u}{\partial{x}^{2}}
        &\approx&
        \displaystyle
        \frac{%
            \frac{u(x+\Delta{x},\,t)-u(x,\,t)}{\Delta{x}}%
            -\frac{u(x,\,t)-u(x-\Delta{x},\,t)}{\Delta{x}}%
        }{%
            \Delta{x}%
        }\\
        &=&
        \displaystyle
        \frac{%
            u(x+\Delta{x},\,t)-2u(x,\,t)+u(x-\Delta{x},\,t)
        }{%
            \Delta{x}^{2}%
        }
   \end{array}
$$

The heat equation then becomes:

$$
    \frac{\partial{u}}{\partial{t}}
    \approx
    \alpha\frac{%
       u(x+\Delta{x},\,t)-2u(x,\,t)+u(x-\Delta{x},\,t)
    }{%
        \Delta{x}^{2}%
    }
$$

Now we use the same approximation scheme for the
time derivative. We get:

$$
    \begin{array}{rcl}
        \displaystyle
        \alpha\frac{%
           u(x+\Delta{x},\,t)-2u(x,\,t)+u(x-\Delta{x},\,t)
        }{%
            \Delta{x}^{2}%
        }
        &\approx&
        \displaystyle
        \frac{\partial{u}}{\partial{t}}\\
        &\approx&
        \displaystyle
        \frac{u(x,\,t+\Delta{t})-u(x,\,t)}{\Delta{t}}
    \end{array}
$$

We now get the following approximation for
$u(x,\,t+\Delta{t})$ provided we know $u(x,\,t)$
for all $x\in[0,\,L]$:

$$
    u(x,\,t+\Delta{t})
    \approx
    \alpha\frac{%
        u(x+\Delta{x},\,t)-2u(x,\,t)+u(x-\Delta{x},\,t)
    }{%
        \Delta{x}^{2}%
    }
    \Delta{t}
    +u(x,\,t)
$$

To make this numerical, we sample the interval $[0,\,L]$
with points $0=x_{0}<x_{1}<\cdots<x_{M}=L$ and moments in
time $t_{0}<t_{1}<\cdots<t_{N}$, where the spatial components
are equally spaced with displacement $\Delta{x}$, and similarly
the time moments are equally spaced with step-size $\Delta{t}$.
We get the following *difference equation*.

$$
    u(x_{m},\,t_{n+1})
    =\frac{\alpha\Delta{t}}{\Delta{x}^{2}}
    \Big(
        u(x_{m+1},\,t_{n})-2u(x_{m},\,t_{n})+u(x_{m-1},\,t_{n})
    \Big)+u(x_{m},\,t_{n})
$$

This method is very concrete and can be implemented in just
a handful of lines.




```{literalinclude}  pysrc/numerical_solution_to_the_heat_equation.py
:lang: python
:caption: Numerical Solution to the Heat Equation
:start-line:31
```

:::{figure} images/numerical_solution_to_the_heat_equation.png
Numerical Solution to the Heat Equation
:::

The problem is that the heat from the left side of the bar
reaches the right side *instantly*. This violates special
relativity which prohibits information from traveling at speeds
greater than that of light. We correct for this by considering
the *relativistic heat equation*:

$$
    \frac{1}{v^{2}}
    \frac{\partial^{2}u}{\partial{t}^{2}}
    +\frac{1}{\alpha}\frac{\partial{u}}{\partial{t}}
    =\frac{\partial^{2}u}{\partial{x}^{2}}
$$

where $v$ is the *second sound velocity*. It is interesting to note that
this is a combination of the heat equation and the wave equation.
For large $\alpha$ one may thus approximate heat using waves,
and so this equation predicts the existence of *thermal waves*.

## Sturm-Liouville Theory and Bessel Functions

Returning to the normal heat equation, we now have a means of
solving it using **Fourier series**, and can compute the
coefficients using the integral formula:

$$
    a_{n}
    =\frac{2}{L}
    \int_{0}^{L}f(x)\sin\left(
        \frac{n\pi{x}}{L}
    \right)\,\textrm{d}x
$$


There are issues about convergence, swapping integrals and sums, etc.,
but such problems reside in Fourier analysis. Surprising as it may be,
the real reason this works is that the sine function satisfies the
following differential equation.

$$
    y^{\prime\prime}(x)+y(x)=0
$$

We can consider a more general differential equation,
called the **Sturm-Liouvile Equation**:

$$
    \frac{\textrm{d}}{\textrm{d}x}
    \left(
        \alpha(x)
        \frac{\textrm{d}y}{\textrm{d}x}
    \right)
    +\big(
        \lambda{w}(x)+\beta(x)
    \big)y(x)
    =0
$$

where $\alpha$, $\beta$, and $w$ are smooth functions
defined on an interval $[a,\,b]$, and where $\alpha$ and
$w$ are *positive* on this interval as well.
Given such a problem, there are positive real numbers
$0<\lambda_{0}<\lambda_{1}<\cdots$ called *eigenvalues*
and corresponding functions $\varphi_{n}$ called
*eigenfunctions* satisfying the
differential equation, and such that for any
piece-wise continuous
(not necessarily differentiable, or even continuous!)
function $f:[a,\,b]\rightarrow\mathbb{R}$, $f$ can be
written as a sum:

$$
    f(x)=\sum_{n=0}^{\infty}a_{n}\varphi_{n}(x)
$$

and the coefficients are given by:

$$
    a_{n}=\int_{a}^{b}
        f(x)\varphi_{n}(x)w(x)\,
        \textrm{d}x
$$

and moreover, the eigenfunctions are *orthogonal*
with respect to $w$:

$$
    \int_{a}^{b}
        \varphi_{m}(x)\varphi_{n}(x)w(x)\,
        \textrm{d}x
    =\delta_{m,\,n}
$$

Fourier series arise as a special case of Sturm-Liouville
theory by setting $\alpha(x)=w(x)=1$ and $\beta(x)=0$.
We could also consider the following differential equation:

$$
    x^{2}y^{\prime\prime}(x)+
    xy^{\prime}(x)+
    (x^{2}-\lambda^{2})y(x)
    =0
$$

This is the **Bessel equation** and the solutions are
used to model acoustics, heat, and *electromagnetic waves*
(we'll return to these soon). The solution is given by a
power series:

$$
    J_{n}(x)
    =\sum_{k=0}^{\infty}
        \frac{(-1)^{k}}{k!(n+k)!}\left(
            \frac{x}{2}
        \right)^{2k+n}
$$

`tmpyl` provides $J_{0}$ and $J_{1}$.

```{literalinclude}  pysrc/bessel_functions_example.py
:lang: python
:caption: Bessel Functions Example
:start-line:31
```

:::{figure} images/bessel_functions_example.png
Plotting the Bessel Functions
:::

The rest of the Bessel functions can be computed
using a *recursion* relation. The Bessel functions satisfy
the following:

$$
    J_{n+2}(x)
    =\frac{2(n+1)}{x}J_{n+1}(x)-J_{n}(x)
$$

Another useful relation relates the derivatives
of the Bessel functions:

$$
    \frac{\textrm{d}}{\textrm{d}x}
    \left(
        x^{n+1}J_{n+1}(x)
    \right)
    =x^{n+1}J_{n}(x)
$$

Lastly, we will make use of the Bessel integral formula:

$$
    J_{0}(x)=
    \frac{1}{2\pi}
    \int_{0}^{2\pi}\exp\big(ix\cos(t)\big)\,\textrm{d}t
$$

Our first application of all of this is in deriving a formula
for the intensity of light through a cylindrically symmetric
aperture in the Fraunhofer limit. In the case of a circle, we
obtain *Airy disks*.
