# Rectangular Aperture
Suppose that $U^{\prime}$ evaluates to one in a rectangle around the
origin, and zero everywhere else. That is, suppose there are positive
real numbers $W$ and $H$ such that:

$$
    U^{\prime}(x^{\prime},\,y^{\prime},\,0)
    =\begin{cases}
        1,&|x^{\prime}|\leq\frac{W}{2}
            \textrm{ and }|y^{\prime}|\leq\frac{H}{2}\\
        0,&\textrm{otherwise}
    \end{cases}
$$

The intensity formula in the Fraunhofer limit then becomes:

$$
        I(x,\,y,\,z)
        =
        \frac{1}{\lambda^{2}z^{2}}
        \left|
            \int_{-H/2}^{H/2}\int_{-W/2}^{W/2}
                \exp\left(\frac{-ik}{z}(xx^{\prime}+yy^{\prime})\right)\,
                    \textrm{d}x^{\prime}\,\textrm{d}y^{\prime}
        \right|^{2}
$$

This can be integrated directly using some exponential rules and
elementary calculus. To simplifiy the length of the equations,
let's denote this final integral by $V$. That is:

$$
    V(x,\,y)
    =\int_{-H/2}^{H/2}\int_{-W/2}^{W/2}
        \exp\left(\frac{-ik}{z}(xx^{\prime}+yy^{\prime})\right)\,
            \textrm{d}x^{\prime}\,\textrm{d}y^{\prime}
$$

We then have:

$$
    \begin{array}{rcl}
        \displaystyle
        V(x,\,y)
        &=&
        \displaystyle
        \int_{-H/2}^{H/2}\int_{-W/2}^{W/2}
            \exp\left(\frac{-ikxx^{\prime}}{z}\right)
            \exp\left(\frac{-ikyy^{\prime}}{z}\right)\,
                \textrm{d}x^{\prime}\,\textrm{d}y^{\prime}\\
        &=&
        \displaystyle
        \left(
            \int_{-H/2}^{H/2}\exp\left(\frac{-ikyy^{\prime}}{z}\right)\,
                \textrm{d}y^{\prime}
        \right)
        \left(
            \int_{-W/2}^{W/2}\exp\left(\frac{-ikxx^{\prime}}{z}\right)\,
               \textrm{d}x^{\prime}
        \right)
    \end{array}
$$

Now we invoke Euler's formula, which says:

$$
    \exp(i\theta)=\cos(\theta)+i\sin(\theta)
$$

Integrating $\sin(\theta)$ about symmetric limits results in zero
since $\sin$ is an odd function. Only the cosine portion remains,
simplifying our calculation to the following:

$$
    \begin{array}{rcl}
        \displaystyle
        V(x,\,y)
        &=&
        \displaystyle
        \left(
            \int_{-H/2}^{H/2}\cos\left(\frac{kyy^{\prime}}{z}\right)\,
                \textrm{d}y^{\prime}
        \right)
        \left(
            \int_{-W/2}^{W/2}\cos\left(\frac{kxx^{\prime}}{z}\right)\,
               \textrm{d}x^{\prime}
        \right)\\
        &=&
        \displaystyle
        \left(
            \frac{2z}{ky}\sin\left(\frac{kyH}{2z}\right)
        \right)
        \left(
            \frac{2z}{kx}\sin\left(\frac{kxW}{2z}\right)
        \right)\\
        &=&
        \displaystyle
        WH
        \frac{\sin\left(\frac{\pi{x}W}{\lambda{z}}\right)}{\frac{\pi{x}W}{\lambda{z}}}
        \frac{\sin\left(\frac{\pi{y}H}{\lambda{z}}\right)}{\frac{\pi{y}H}{\lambda{z}}}
    \end{array}
$$

where we have used $k=2\pi/\lambda$ in our final simplification.
The $\textrm{sinc}$ function is common in signal processing and optics,
and is defined as:

$$
    \textrm{sinc}(x)
    =\begin{cases}
        \frac{\sin(x)}{x},&x\ne{0}\\
        1,&x=0
    \end{cases}
$$

Using this, our formula becomes:

$$
    V(x,\,y)
    =WH\;\textrm{sinc}\left(
        \frac{\pi{x}W}{\lambda{z}}
    \right)
    \textrm{sinc}\left(
        \frac{\pi{y}W}{\lambda{z}}
    \right)
$$

The intensity is then:

$$
    \begin{array}{rcl}
        \displaystyle
        I(x,\,y,\,z)
        &=&
        \displaystyle
        \frac{1}{\lambda^{2}z^{2}}V(x,\,y)^{2}\\
        &=&
        \displaystyle
        \frac{W^{2}H^{2}}{\lambda^{2}z^{2}}
        \textrm{sinc}\left(
            \frac{\pi{x}W}{\lambda{z}}
        \right)^{2}
        \textrm{sinc}\left(
            \frac{\pi{y}W}{\lambda{z}}
        \right)^{2}
    \end{array}
$$

If we fix our detector at a constant $z$ value, this factor
in the front is a constant which we may label as $I_{0}$. It is
the intensity at the origin of this constant $z$ plane.
That is, the intensity at $(0,\,0,\,z)$. We have:

$$
    I(x,\,y,\,z)
    =I_{0}\;
    \textrm{sinc}\left(
        \frac{\pi{x}W}{\lambda{z}}
    \right)^{2}
    \textrm{sinc}\left(
        \frac{\pi{y}W}{\lambda{z}}
    \right)^{2}
$$

Let's test our derivation in Python.

```{literalinclude} pysrc/fraunhofer_diffraction_rectangular_aperture.py
:lang: python
:caption: Fraunhofer Diffraction in Python
:start-line:31
```

If we save this to `fraunhofer_diffraction_rectangular_aperture.py` and then
run:

```bash
python3 fraunhofer_diffraction_rectangular_aperture.py
```

we'll obtain the image below.

:::{figure} images/fraunhofer_diffraction_rectangular_aperture.png
Fraunhofer Diffraction - Rectangular Aperture
:::
