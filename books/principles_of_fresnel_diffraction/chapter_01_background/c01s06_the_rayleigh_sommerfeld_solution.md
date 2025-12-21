# The Rayleigh-Sommerfeld Solution
Our method of solution transforms this differential equation
into an *integral equation*. If we know
$U^{\prime}(x^{\prime},\,y^{\prime},\,0)$ for each
$(x^{\prime},\,y^{\prime})$ in the $z=0$ plane, then the
solution for $U(x,\,y,\,z)$ is:

$$
    \begin{array}{rcl}
        \displaystyle
        U(\mathbf{r})
        &=&
        \displaystyle
        \frac{1}{i\lambda}
        \iint_{\mathbb{R}^{2}}
            U^{\prime}(x^{\prime},\,y^{\prime},\,0)
            \frac{z\exp\left(ikr\right)}{r^{2}}
            \left(1-\frac{1}{kr}\right)
                \,\textrm{d}x^{\prime}\,\textrm{d}y^{\prime}\\
        &=&
        \displaystyle
        \frac{1}{i\lambda}
        \int_{0}^{\infty}\int_{0}^{2\pi}
            U^{\prime}(\rho^{\prime},\,\phi^{\prime})
            \frac{z\rho^{\prime}\exp\left(ikr\right)}{r^{2}}
            \left(1-\frac{1}{kr}\right)
                \,\textrm{d}\phi^{\prime}\textrm{d}\rho^{\prime}\\
    \end{array}
$$

where this second integral simply swaps from Cartesian
coordinates to cylindrical, and where $r$ is given by:

$$
    \begin{array}{rcl}
        \displaystyle
        r
        &=&
        \|\mathbf{r}-\mathbf{r}^{\prime}\|\\
        &=&
        \displaystyle
        \|(x-x^{\prime},\,y-y^{\prime},\,z)\|\\
        &=&
        \displaystyle
        \sqrt{(x-x^{\prime})^{2}+(y-y^{\prime})^{2}+z^{2}}
    \end{array}
$$

The parameter $\lambda$ is the *wavelength* of the wave, and
$k$ is the *wavenumber*:

$$
    k=\frac{2\pi}{\lambda}
$$

In practice, $\lambda$ is very small, meaning $k$ is quite large.
Since $r$ is also big in most circumstances, the contribution
to the integral from the $1/kr$ term is negligible and may be
omitted for numerical purposes. Our approximate solution is then:

$$
    \begin{array}{rcl}
        \displaystyle
        U(\mathbf{r})
        &\approx&
        \displaystyle
        \frac{1}{i\lambda}
        \iint_{\mathbb{R}^{2}}
            U^{\prime}(x^{\prime},\,y^{\prime},\,0)
            \frac{z\exp\left(ikr\right)}{r^{2}}
                \,\textrm{d}x^{\prime}\,\textrm{d}y^{\prime}\\
        &=&
        \displaystyle
        \frac{1}{i\lambda}
        \int_{0}^{\infty}\int_{0}^{2\pi}
            U^{\prime}(\rho^{\prime},\,\phi^{\prime})
            \frac{z\rho^{\prime}\exp\left(ikr\right)}{r^{2}}
                \,\textrm{d}\phi^{\prime}\textrm{d}\rho^{\prime}\\
    \end{array}
$$
