# Rectangular Aperture
Let's repeat the computation for a rectangular aperture, but now
we shall apply the Fresnel approximation instead of the Fraunhofer one.
We get:

$$
    \begin{array}{rcl}
        \displaystyle
        U(\mathbf{r})
        &\approx&
        \displaystyle
        \iint_{\mathbb{R}^{2}}
            U^{\prime}(x^{\prime},\,y^{\prime},\,0)
            \exp\left(
                \frac{ik}{2z}\left(
                    \left(x-x^{\prime}\right)^{2}+
                    \left(y-y^{\prime}\right)^{2}
                \right)
            \right)\,
            \textrm{d}x^{\prime}\,\textrm{d}y^{\prime}\\
        &=&
        \displaystyle
        \frac{\exp(ikz)}{i\lambda{z}}
        \int_{-H}^{H}\int_{-W}^{W}
            \exp\left(
                \frac{ik}{2z}\left(
                    \left(x-x^{\prime}\right)^{2}+
                    \left(y-y^{\prime}\right)^{2}
                \right)
            \right)\,
            \textrm{d}x^{\prime}\,\textrm{d}y^{\prime}\\
        &=&
        \displaystyle
        \frac{\exp(ikz)}{i\lambda{z}}
        \left(
            \int_{-H}^{H}\exp\left(
                \frac{ik}{2z}(y-y^{\prime})^{2}
            \right)\,
            \textrm{d}y^{\prime}
        \right)
        \left(
            \int_{-W}^{W}\exp\left(
                \frac{ik}{2z}(x-x^{\prime})^{2}
            \right)\,
            \textrm{d}x^{\prime}
        \right)
    \end{array}
$$

Applying Euler's formula, we are led to the following integrals:

$$
    \begin{array}{rcl}
        \displaystyle
        f(t)
        &=&
        \displaystyle
        \int_{-t}^{t}
            \cos\left(
                \frac{\pi}{\lambda{z}}\tau^{2}
            \right)\,
            \textrm{d}\tau\\
        \displaystyle
        g(t)
        &=&
        \displaystyle
        \int_{-t}^{t}
            \sin\left(
                \frac{\pi}{\lambda{z}}\tau^{2}
            \right)\,
            \textrm{d}\tau
    \end{array}
$$

These are closely related to very well-studied functions,
the **normalized Fresnel integrals**. They are defined by:

$$
    \begin{array}{rcl}
        \displaystyle
        C(x)
        &=&
        \displaystyle
        \int_{0}^{x}
            \cos\left(\frac{\pi}{2}t^{2}\right)\,
            \textrm{d}t\\
        \displaystyle
        S(x)
        &=&
        \displaystyle
        \int_{0}^{x}
            \sin\left(\frac{\pi}{2}t^{2}\right)\,
            \textrm{d}t
    \end{array}
$$

Note, the *unnormalized* Fresnel integrals are quite
common in mathematics and physics, and are defined by:

$$
    \begin{array}{rcl}
        \displaystyle
        \hat{C}(x)
        &=&
        \displaystyle
        \int_{0}^{x}
            \cos\left(t^{2}\right)\,
            \textrm{d}t\\
        \displaystyle
        \hat{S}(x)
        &=&
        \displaystyle
        \int_{0}^{x}
            \sin\left(t^{2}\right)\,
            \textrm{d}t
    \end{array}
$$

Both the normalized and unnormalized Fresnel integrals
are provided by `tmpyl`.

```{literalinclude}  pysrc/fresnel_sine_and_cosine.py
:lang: python
:caption: Fresnel Sine and Cosine
:start-line:31
```

:::{figure} images/fresnel_sine_and_cosine.png
Fresnel Sine and Cosine
:::

```{literalinclude}  pysrc/normalized_fresnel_sine_and_cosine.py
:lang: python
:caption: Normalized Fresnel Sine and Cosine
:start-line:31
```

:::{figure} images/normalized_fresnel_sine_and_cosine.png
Normalized Fresnel Sine and Cosine
:::

Let's use these to craft a solution.

```{literalinclude}  pysrc/fresnel_diffraction_rectangular_aperture.py
:lang: python
:caption: Fresnel Diffraction - Rectangular Aperture
:start-line:31
```

:::{figure} images/fresnel_diffraction_rectangular_aperture.png
Fresnel Diffraction - Rectangular Aperture
:::

If we decrease the aperture size we return to the Fraunhofer limit.
The product of the $\textrm{sinc}$ functions start to approximate
the Fresnel functions, as shown below.

```{literalinclude}  pysrc/fresnel_diffraction_rectangular_fraunhofer_limit.py
:lang: python
:caption: Fresnel Diffraction - Rectangular Aperture
:start-line:31
```

:::{figure} images/fresnel_diffraction_rectangular_fraunhofer_limit.png
Fresnel Diffraction - Rectangular Aperture
:::
