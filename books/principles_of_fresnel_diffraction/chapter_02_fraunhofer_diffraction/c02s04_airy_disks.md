# Airy Disks
Now we consider a circular aperture. That is, we consider
$U^{\prime}(x^{\prime},\,y^{\prime},\,0)$ given by:

$$
    U^{\prime}(x^{\prime},\,y^{\prime},\,0)
    =\begin{cases}
        1,&x^{\prime\,2}+y^{\prime\,2}\leq{R}^{2}\\
        0,&\textrm{otherwise}
    \end{cases}
$$

where $R$ is a real positive number, the *radius* of the aperture.
We develop an exact solution by switching to polar coordinates.
$x^{\prime}$ and $y^{\prime}$ are replaced by:

$$
    \begin{array}{rcl}
        \displaystyle
        x^{\prime}
        &=&
        \displaystyle
        \rho^{\prime}\cos(\theta^{\prime})\\
        \displaystyle
        y^{\prime}
        &=&
        \displaystyle
        \rho^{\prime}\sin(\theta^{\prime})
    \end{array}
$$

The area differential is also changed
(using the Jabobian of our coordinate transformation):

$$
    \textrm{d}x\,\textrm{d}y
    =
    \rho^{\prime}\,
        \textrm{d}\rho^{\prime}\,
        \textrm{d}\theta^{\prime}
$$

The Fraunhofer integral then becomes:

$$
    U(\rho,\,\theta,\,z)
    =
    \frac{\exp(ikz)\exp\left(ik\frac{\rho^{2}}{2z}\right)}{i\lambda{z}}
    \int_{0}^{\infty}
        \int_{0}^{2\pi}
            U^{\prime}(\rho^{\prime},\,\theta^{\prime},\,0)
            \exp\left(
                \frac{-ik}{z}\left(
                    \rho\rho^{\prime}\cos(\theta)\cos(\theta^{\prime})
                    +\rho\rho^{\prime}\sin(\theta)\sin(\theta^{\prime})
                \right)
            \right)
            \rho^{\prime}\,
            \textrm{d}\theta^{\prime}\,
            \textrm{d}\rho^{\prime}
$$

Using the angle-difference formula, this simplifies to:

$$
    U(\rho,\,\theta,\,z)
    =
    \frac{\exp(ikz)\exp\left(ik\frac{\rho^{2}}{2z}\right)}{i\lambda{z}}
    \int_{0}^{\infty}
        \int_{0}^{2\pi}
            U^{\prime}(\rho^{\prime},\,\theta^{\prime},\,0)
            \exp\left(
                \frac{-ik}{z}\left(
                    \rho\rho^{\prime}\cos(\theta-\theta^{\prime})
                \right)
            \right)
            \rho^{\prime}\,
            \textrm{d}\theta^{\prime}\,
            \textrm{d}\rho^{\prime}
$$

For a circular aperture the function $U^{\prime}$ varies
independently of $\theta^{\prime}$. We may therefore factor it out
of the azimuthal integral:

$$
    U(\rho,\,\theta,\,z)
    =
    \frac{\exp(ikz)\exp\left(ik\frac{\rho^{2}}{2z}\right)}{i\lambda{z}}
    \int_{0}^{\infty}
        \rho^{\prime}U^{\prime}(\rho^{\prime})
        \int_{0}^{2\pi}
            \exp\left(
                \frac{-ik}{z}\left(
                    \rho\rho^{\prime}\cos(\theta-\theta^{\prime})
                \right)
            \right)
            \textrm{d}\theta^{\prime}\,
            \textrm{d}\rho^{\prime}
$$

Using the integral definition of $J_{0}$, and recalling that the intensity
is the square of the magnitude of $U$, we obtain:

$$
    \begin{array}{rcl}
        \displaystyle
        I(\rho,\,\theta,\,z)
        &=&
        \displaystyle
        \frac{1}{\lambda^{2}z^{2}}
        \left|
            \int_{0}^{\infty}
                \rho^{\prime}U^{\prime}(\rho^{\prime})
                \int_{0}^{2\pi}
                    \exp\left(
                        \frac{-ik}{z}\left(
                            \rho\rho^{\prime}\cos(\theta-\theta^{\prime})
                        \right)
                    \right)
                    \textrm{d}\theta^{\prime}\,
                    \textrm{d}\rho^{\prime}
        \right|^{2}\\
        &=&
        \displaystyle
        \frac{1}{\lambda^{2}z^{2}}
        \left|
            \int_{0}^{\infty}
                2\pi\rho^{\prime}U(\rho^{\prime})
                J_{0}\left(
                    \frac{k\rho\rho^{\prime}}{z}
                \right)\,
                \textrm{d}\rho^{\prime}
        \right|^{2}\\
        &=&
        \displaystyle
        \frac{4\pi^{2}}{\lambda^{2}z^{2}}
        \left|
            \int_{0}^{R}
                \rho^{\prime}
                J_{0}\left(
                    \frac{k\rho\rho^{\prime}}{z}
                \right)\,
                \textrm{d}\rho^{\prime}
        \right|^{2}
    \end{array}
$$

Now make the substitution $u=k\rho\rho^{\prime}/z$, meaning
$\textrm{d}\rho^{\prime}=\frac{z}{k\rho}\textrm{d}u$. We get:

$$
    \begin{array}{rcl}
        \displaystyle
        I(\rho,\,\theta,\,z)
        &=&
        \displaystyle
        \frac{4\pi^{2}}{\lambda^{2}z^{2}}
        \left|
            \int_{0}^{k\rho{R}/z}
                \frac{z^{2}}{k^{2}\rho^{2}}
                u\,J_{0}(u)\,
                \textrm{d}u
        \right|^{2}\\
        &=&
        \displaystyle
        \frac{4\pi^{2}}{\lambda^{2}z^{2}}
        \left|
            \int_{0}^{k\rho{R}/z}
                \frac{z^{2}}{k^{2}\rho^{2}}
                \frac{\textrm{d}}{\textrm{d}u}\left(
                    u\,J_{1}(u)
                \right)\,
                \textrm{d}u
        \right|^{2}\\
        &=&
        \displaystyle
        \frac{\lambda^{2}z^{2}}{4\pi^{2}\rho^{4}}
        \left|
            \int_{0}^{k\rho{R}/z}
                \frac{\textrm{d}}{\textrm{d}u}\left(
                    u\,J_{1}(u)
                \right)\,
                \textrm{d}u
        \right|^{2}\\
        &=&
        \displaystyle
        \frac{R^{2}}{\rho^{2}}
        J_{1}\left(
            \frac{2\pi\rho{R}}{\lambda{z}}
        \right)^{2}\\
        &=&
        \displaystyle
        \frac{4\pi^{2}R^{4}}{\lambda^{2}z^{2}}
        \left(
            \frac{J_{1}\left(2\pi\rho{R}/\lambda{z}\right)}{2\pi\rho{R}/\lambda{z}}
        \right)^{2}\\
        &=&
        \displaystyle
        I_{0}\left(
            \frac{J_{1}\left(2\pi\rho{R}/\lambda{z}\right)}{2\pi\rho{R}/\lambda{z}}
        \right)^{2}
    \end{array}
$$

Let's write this up.

```{literalinclude}  pysrc/fraunhofer_diffraction_airy_disks.py
:lang: python
:caption: Fraunhofer Diffraction Through a Circular Aperture
:start-line:31
```

:::{figure} images/fraunhofer_diffraction_airy_disks.png
Fraunhofer Diffraction - Airy Disks
:::
