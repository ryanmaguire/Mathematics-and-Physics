# Fresnel Diffraction: Theory
Let's return to the Arnold-Sommerfeld solution. We have:

$$
    U(\mathbf{r})
    \approx
    \displaystyle
    \frac{1}{i\lambda}
    \iint_{\mathbb{R}^{2}}
        U^{\prime}(x^{\prime},\,y^{\prime},\,0)
        \frac{z\exp\left(ikr\right)}{r^{2}}
            \,\textrm{d}x^{\prime}\,\textrm{d}y^{\prime}
$$

To obtain the Fraunhofer approximation, we simply truncated
$r$ to the terms that vary lineary with $x^{\prime}$ and $y^{\prime}$.
We can improve this approximation by considering the quadratic terms.
We have:

$$
    \begin{array}{rcl}
        \displaystyle
        r
        &=&
        \displaystyle
        \sqrt{(x-x^{\prime})^{2}+(y-y^{\prime})^{2}+z^{2}}\\
        &=&
        \displaystyle
        z\sqrt{
            \left(\frac{x-x^{\prime}}{z}\right)^{2}+
            \left(\frac{y-y^{\prime}}{z}\right)^{2}+
            1
        }\\
        &\approx&
        \displaystyle
        z+\frac{(x-x^{\prime})^{2}+(y-y^{\prime})^{2}}{2z}
    \end{array}
$$

Let's also suppose that the characteristic size of the
aperture is signficantly smaller than the distance from it
to the observer, and furthermore that $\lambda$, the wavelength,
is significantly smaller than this distance as well. The
ratio $z/r$ can be approximated as 1, and we end up with
the **Fresnel approximation**:

$$
    U(\mathbf{r})
    \approx
    \frac{\exp(ikz)}{i\lambda{z}}
    \iint_{\mathbb{R}^{2}}
        U^{\prime}(x^{\prime},\,y^{\prime},\,0)
        \exp\left(
            \frac{ik}{2z}\left(
                \left(x-x^{\prime}\right)^{2}+
                \left(y-y^{\prime}\right)^{2}
            \right)
        \right)\,
        \textrm{d}x^{\prime}\,\textrm{d}y^{\prime}
$$
