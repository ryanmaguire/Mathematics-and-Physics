# The Stationary Phase Approximation
The Fresnel approximation produces an integral expression that involves
a highly oscillatory integrand. Namely:

$$
    \int_{0}^{2\pi}
        \exp\left(
            \frac{ik\rho\rho^{\prime}}{z}
            \cos\left(\theta-\theta^{\prime}\right)
        \right)\,
        \textrm{d}\theta^{\prime}\,
        \textrm{d}\rho^{\prime}
$$

The value $k$ is quite large, meaning most of the contribution from
the integral occurs where the graph of
$\frac{k\rho\rho^{\prime}}{z}\cos(\theta-\theta^{\prime})$ is flat,
with respect to $\theta$. That is, where $\cos(\theta-\theta^{\prime})$
is *stationary*. Differentiating, we get:

$$
    \frac{\textrm{d}}{\textrm{d}\theta}\Big(
        \cos(\theta-\theta^{\prime})
    \Big)
    =-\sin(\theta-\theta^{\prime})
$$

Solving for $0$ we obtain $\theta=\theta^{\prime}$.
The stationary phase approximation allows us to approximate
this integral as follows. In general, if we have
smooth functions $f$ and $g$ defined on $[0,\,2\pi]$,
if $x_{0}\in[0,\,2\pi]$ is the only stationary point for $f$,
and crucially if $f^{\prime\prime}(x_{0})$ is non-zero, then:

$$
    \int_{0}^{2\pi}
        g(x)\exp\Big(ikf(x)\Big)\,\textrm{d}x
    \approx
    g(x_{0})
    \exp\Big(
        \pm\frac{i\pi}{4}
    \Big)
    \exp\Big(
        ikf(x_{0})
    \Big)
    \sqrt{\frac{2\pi}{k|f^{\prime\prime}(x_{0})|}}
$$

where the $\pm$ is determined by the sign of
$f^{\prime\prime}(x_{0})$. Applying this to our cylindrical
Fresnel transform, we have $g(\theta)=1$, and
$f(\theta)=\frac{\rho\rho^{\prime}}{z}\cos(\theta-\theta^{\prime})$.
This integral becomes:

$$
    \begin{array}{rcl}
        \displaystyle
        \int_{0}^{2\pi}
            \exp\left(
                \frac{ik\rho\rho^{\prime}}{z}
                \cos\left(\theta-\theta^{\prime}\right)
            \right)\,
            \textrm{d}\theta^{\prime}\,
            \textrm{d}\rho^{\prime}
        &\approx&
        \displaystyle
        \exp\left(-\frac{i\pi}{4}\right)
        \exp\left(
            \frac{ik\rho\rho^{\prime}}{z}
        \right)
        \sqrt{\frac{2\pi}{k\rho\rho^{\prime}/z}}
    \end{array}
$$
