# Arago Spot
Switching to polar coordinates, the Fresnel approximation becomes:

$$
    U(\mathbf{r})
    \approx
    \frac{\exp(ikz)}{i\lambda{z}}
    \int_{0}^{\infty}
        \int_{0}^{2\pi}
            U^{\prime}(r^{\prime},\,\theta^{\prime},\,0)
            \exp\left(
                \frac{ik}{2z}\left(
                    \rho^{\prime\,2}-
                    2\rho\rho^{\prime}
                    \cos\left(\theta-\theta^{\prime}\right)
                    +\rho^{2}
                \right)
            \right)
            \rho^{\prime}\,
            \textrm{d}\theta^{\prime}\,
            \textrm{d}\rho^{\prime}
$$

For a circular aperture this reduces to the following:

$$
    U(\mathbf{r})
    \approx
    \frac{
        \exp(ikz)
        \exp\left(\frac{ik\rho^{2}}{2z}\right)
    }{
        i\lambda{z}
    }
    \int_{0}^{R}
        \rho^{\prime}
        \exp\left(
            \frac{ik\rho^{\prime\,2}}{2z}
        \right)
        \int_{0}^{2\pi}
            \exp\left(
                \frac{ik\rho\rho^{\prime}}{z}
                \cos\left(\theta-\theta^{\prime}\right)
            \right)\,
            \textrm{d}\theta^{\prime}\,
            \textrm{d}\rho^{\prime}
$$

We again use Bessel's integral formula to obtain:

$$
    U(\mathbf{r})
    \approx
    \frac{
        \exp(ikz)
        \exp\left(\frac{ik\rho^{2}}{2z}\right)
    }{
        i\lambda{z}
    }
    \int_{0}^{R}
        \rho^{\prime}
        \exp\left(
            \frac{ik\rho^{\prime\,2}}{2z}
        \right)
        2\pi{J}_{0}\left(\frac{k\rho\rho^{\prime}}{z}\right)
            \textrm{d}\rho^{\prime}
$$

Ignoring the outside terms, and replacing $k$ with $\lambda$, we obtain
the new function:

$$
    \tilde{A}(\rho)
    =
    \int_{0}^{R}
        \rho^{\prime}
        \exp\left(
            \frac{i\pi\rho^{\prime\,2}}{\lambda{z}}
        \right)
        {J}_{0}\left(\frac{2\pi\rho\rho^{\prime}}{\lambda{z}}\right)
            \textrm{d}\rho^{\prime}
$$

If we make the substitution $u^{\prime}=\rho^{\prime}/\sqrt{\lambda{z}}$
and $u=2\pi\rho/\sqrt{\lambda{z}}$, then
(up to some multiplicative factor involving $\lambda{z}$)
our integral becomes:

$$
    A_{\nu}(u)
    =
    \int_{0}^{\nu}
        u^{\prime}
        J_{0}(uu^{\prime})
        \exp\left(i\pi{u}^{\prime\,2}\right)\,
        \textrm{d}u^{\prime}
$$

A bit difficult to tackle, let's try setting $f=J_{0}(uu^{\prime})$
and $\textrm{d}g=u\exp(i\pi{u}^{2})\,\textrm{d}u$.
Integration by parts then produces:

$$
    A_{\nu}(u)
    =
    \frac{1}{2\pi{i}}
    J_{0}\left(u\nu\right)
    \exp\left(i\pi\nu^{2}\right)
    +\frac{u}{2\pi{i}}
    \int_{0}^{\nu}J_{1}(u{u}^{\prime})
        \exp\left(i\pi{u}^{\prime\,2}\right)\,
        \textrm{d}u^{\prime}
$$

From the definition, $u$ is a scaled version of $\rho$,
and $\nu$ is a scaled version of the radius. If $u\nu$
is small (say, less than $1$), then we may use the
Maclaurin series for $J_{1}(uu^{\prime})$ in $u^{\prime}$
to numerically integrate.
