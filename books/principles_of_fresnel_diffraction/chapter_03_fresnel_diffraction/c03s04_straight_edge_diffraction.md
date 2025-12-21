# Straight Edge Diffraction
The diffraction pattern for a straight edge is given by:

$$
    \hat{T}(\rho_{0})
    =
    \frac{1+i}{2F}
    \int_{-\infty}^{\infty}
        T(\rho)
        \exp\left(
            i\frac{\pi}{2}\left(
                \frac{\rho-\rho_{0}}{F}
            \right)^{2}
        \right)\,\textrm{d}\rho
    =
    \frac{1+i}{2F}
    \int_{R}^{\infty}
        \exp\left(
            i\frac{\pi}{2}
            \left(
                \frac{\rho-\rho_{0}}{F}
            \right)^{2}
        \right)\,\textrm{d}\rho
$$

where $R>0$ is a positive real number, the radius where the straight
edge occurs. Using Euler's formula, this becomes:

$$
    \hat{T}(\rho_{0})
    =\frac{1+i}{2F}\int_{R}^{\infty}\left(
        \cos\left(\frac{\pi}{2}\left(\frac{\rho-\rho_{0}}{F}\right)^{2}\right)
        +i\sin\left(\frac{\pi}{2}\left(\frac{\rho-\rho_{0}}{F}\right)^{2}\right)
    \right)\,\textrm{d}\rho
$$

The **normalized Fresnel integrals** are defined via:

$$
    C(x)=\int_{0}^{x}\cos\left(\frac{\pi}{2}t^{2}\right)\,\textrm{d}t,
    \quad\quad
    S(x)=\int_{0}^{x}\sin\left(\frac{\pi}{2}t^{2}\right)\,\textrm{d}t
$$

These are provided by `tmpyl`, see the example above.
Use these to write out explicit formulas for the diffraction pattern
and plot them using Python.
