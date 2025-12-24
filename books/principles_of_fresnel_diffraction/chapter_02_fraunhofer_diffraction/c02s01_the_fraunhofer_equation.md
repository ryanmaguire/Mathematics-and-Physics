# The Fraunhofer Equation
Given $U^{\prime}$, our goal is to compute $U$.
There are many ways to do this *directly*, but
first let's do it *indirectly* by approximating bits of this equation.
Suppose the observer at the point $\mathbf{r}=(x,\,y,\,z)$
is far away from the plane, so that
$z>>\|(x^{\prime},\,y^{\prime},\,0)\|$.
Furthermore, suppose that $U^{\prime}$ is
only non-zero in a small region $R$ near the origin of the $xy$ plane.
The only contribution to the integral occurs in the region,
meaning we may replace $\mathbb{R}^{2}$ with $R$ in our formula.

If $z$ is much larger than the diameter of $R$ (where *diameter*
means the maximum distance between two points in $R$), then
we may apply the following approximation:

\begin{equation}
    \frac{z}{r}
    \approx
    1
\end{equation}

The integral equation for $U$ becomes:

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rcl}
        \displaystyle
        U(x,\,y,\,z)
        \!\!
        &\approx&
        \!\!
        \displaystyle
        \frac{1}{i\lambda}\iint_{R}
            U^{\prime}(x^{\prime},\,y^{\prime})
            \frac{\exp(ikr)}{z}\,
            \textrm{d}x^{\prime}\,\textrm{d}y^{\prime}\\
        \!\!
        &=&
        \!\!
        \displaystyle
        \frac{1}{i\lambda{z}}
        \iint_{R}U(x^{\prime},\,y^{\prime})
            \exp(ikr)\,
            \textrm{d}x^{\prime}\,\textrm{d}y^{\prime}
    \end{array}
\end{equation}

Now we examine $r$. We rewrite it as follows:

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rcl}
        \displaystyle
        r
        \!\!
        &=&
        \!\!
        \displaystyle
        \sqrt{(x-x^{\prime})^{2}+(y-y^{\prime})^{2}+z^{2}}\\
        \!\!
        &=&
        \!\!
        \displaystyle
        z\sqrt{
            1+
            \left(\frac{x-x^{\prime}}{z}\right)^{2}+
            \left(\frac{y-y^{\prime}}{z}\right)^{2}
        }\\
        &\approx&
        \displaystyle
        z\left(
            1+\frac{1}{2}\left(
                \frac{x-x^{\prime}}{z}
            \right)^{2}+
            \frac{1}{2}\left(
                \frac{y-y^{\prime}}{z}
            \right)^{2}
        \right)
    \end{array}
\end{equation}

where this final approximation comes from the multi-variable
Taylor expansion for $r$ in $x^{\prime}$ and $y^{\prime}$, centered
about $x$ and $y$, respectively. Expanding the quadratics, we get:

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rcl}
        \displaystyle
        r
        \!\!
        &\approx&
        \!\!
        \displaystyle
        z
        +
        \frac{x^{2}-2xx^{\prime}+x^{\prime\,2}}{2z}
        +
        \frac{y^{2}-2yy^{\prime}+y^{\prime\,2}}{2z}\\
        \!\!
        &=&
        \!\!
        \displaystyle
        \left(z+\frac{x^{2}}{2z}+\frac{y^{2}}{2z}\right)
        +
        \left(
            \frac{x^{\prime\,2}-2xx^{\prime}}{2z}
            +
            \frac{y^{\prime\,2}-2yy^{\prime}}{2z}
        \right)
    \end{array}
\end{equation}

This final expression separates the quantities being integrated
over ($x^{\prime}$ and $y^{\prime}$) from the constants
($x$, $y$, and $z$). Now we recall that by hypothesis the
value $z$ is far greater in magnitude than $x^{\prime}$ or
$z^{\prime}$. We may treat the ratios $x^{\prime\,2}/z$ and
$y^{\prime\,2}/z$ as zero. We then obtain:

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rcl}
        \displaystyle
        r
        \!\!
        &\approx&
        \!\!
        \displaystyle
        \left(z+\frac{x^{2}}{2z}+\frac{y^{2}}{2z}\right)
        -\left(
            \frac{xx^{\prime}+yy^{\prime}}{z}
        \right)
    \end{array}
\end{equation}

We've done quite a bit of approximating, but note that the main
requirement is that $z$ is much greater than the *characteristic scale*
of the region $R$ where $U^{\prime}$ is non-zero (we referred to this as the
*diameter* in a previous paragraph). The physical interpretation is that
$U^{\prime}$ describes an *aperture*, and where it is non-zero is where light
is allowed to pass through. Points $(x^{\prime},\,y^{\prime})$ satisfying
$U^{\prime}(x^{\prime},\,y^{\prime},\,0)=0$ are those where light is completely
blocked.

The **Fraunhofer Diffraction Formula** is then obtain from the
Rayleigh-Sommerfeld formula by substituting our new approximation for $r$.
In the expression for $r$ we have that $x$, $y$, and $z$ are constant, as far
as the integral is concerned. The integrand simplifies and we obtain:

\begin{equation}
    V(x,\,y)
    =
    \iint_{R}U^{\prime}(x^{\prime},\,y^{\prime},\,0)
        \exp\left(\frac{-ik}{z}(xx^{\prime}+yy^{\prime})\right)\,
            \textrm{d}x^{\prime}\,\textrm{d}y^{\prime}
\end{equation}

The Fraunhofer approximation is then:

\begin{equation}
    \displaystyle
    U(x,\,y,\,z)
    \approx
    \displaystyle
    \frac{\exp(ikz)\exp\left(ik\frac{x^{2}+y^{2}}{2z}\right)}{i\lambda{z}}
    V(x,\,y)
\end{equation}

The *intensity* of the solution is the square of the magnitude of
$U$ (possibly with some *normalizing factor*, depending on author).
We have:

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rcl}
        \displaystyle
        I(x,\,y,\,z)
        \!\!
        &=&
        \!\!
        \displaystyle
        \left|
            U(x,\,y,\,z)
        \right|^{2}\\
        \!\!
        &=&
        \!\!
        \displaystyle
        \left|
            \frac{
                \exp(ikz)\exp\left(ik\frac{x^{2}+y^{2}}{2z}\right)
            }{
                i\lambda{z}
            }
            V(x,\,y)
        \right|^{2}\\
        \!\!
        &=&
        \!\!
        \displaystyle
        \frac{1}{\lambda^{2}z^{2}}
        \left|
            \iint_{R}U^{\prime}(x^{\prime},\,y^{\prime},\,0)
                \exp\left(\frac{-ik}{z}(xx^{\prime}+yy^{\prime})\right)\,
                    \textrm{d}x^{\prime}\,\textrm{d}y^{\prime}
        \right|^{2}\\
        \!\!
        &=&
        \!\!
        \displaystyle
        \frac{1}{\lambda^{2}z^{2}}
        \left|
            V(x,\,y)
        \right|^{2}
    \end{array}
\end{equation}

where we have used the fact that $\exp(i\theta)$ describes a
point on the unit circle
(using Euler's formula, since $\exp(i\theta)=\cos(\theta)+i\sin(\theta)$),
and hence $|\exp(i\theta)|^{2}=1$. This is the
*intensity formula in the Fraunhofer limit*.
