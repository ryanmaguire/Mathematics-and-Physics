# Electricity and Magnetism
The playing field is now set. In the 1800's physicists knew that
light travels at a finite speed, and they have reasonable measurements
of this value. In 1873, James Clerk Maxwell writes his
*Treatise on Electricity and Magnetism.* He describes a mathematical
formulation of electricity and magnetism by writing down the
*Maxwell Equations:*

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rclll}
        \displaystyle
        \nabla\cdot\mathbf{E}
        \!\!
        &=&
        \!\!
        \displaystyle
        \frac{\rho}{\epsilon_{0}}
        &&
        (\textrm{Gauss' Law})\\
        \displaystyle
        \nabla\times\mathbf{E}
        \!\!
        &=&
        \!\!
        \displaystyle
        -\frac{\partial\mathbf{B}}{\partial{t}}
        &&
        (\textrm{Faraday's Law of Induction})\\
        \displaystyle
        \nabla\cdot\mathbf{B}
        \!\!
        &=&
        \!\!
        \displaystyle
        0
        &&
        (\textrm{Gauss' Law of Magnetism})\\
        \displaystyle
        \nabla\times\mathbf{B}
        \!\!
        &=&
        \!\!
        \displaystyle
        \mu_{0}\mathbf{J}+\frac{\partial\mathbf{E}}{\partial{t}}
        &&
        (\textrm{Amp\`{e}re-Maxwell Law})
    \end{array}
\end{equation}

where $\mathbf{E}$ and $\mathbf{B}$ are the *electric*
and *magnetic* fields, respectively, $\rho$ and $\mathbf{J}$
are *charge* and *current* densities, respectively, and where
$\epsilon_{0}$ and $\mu_{0}$ are constants.
Maxwell's original notation precedes that of modern vector
calculus, which comes from Willard Gibbs and Oliver Heaviside
a few decades later. His original writings involve over a
dozen equations.

To proceed, we need the following fact from vector calculus.
If $\mathbf{F}$ is *sufficiently smooth*, then:

\begin{equation}
    \def\arraystretch{2.0em}
    \label{eqn:curl_of_a_curl_formula}
    \begin{array}{rcl}
        \displaystyle
        \nabla\times(\nabla\times\mathbf{F})
        \!\!
        &=&
        \!\!
        \displaystyle
        \nabla(\nabla\cdot\mathbf{F})-(\nabla\cdot\nabla)\mathbf{F}\\
        \!\!
        &=&
        \!\!
        \displaystyle
        \nabla(\nabla\cdot\mathbf{F})-\nabla^{2}\mathbf{F}
    \end{array}
\end{equation}

Applying this to the electric field, we get:

\begin{equation}
    \def\arraystretch{2.3em}
    \begin{array}{rclll}
        \displaystyle
        \nabla\times(\nabla\times\mathbf{E})
        \!\!
        &=&
        \!\!
        \displaystyle
        \nabla\left(
            \nabla\cdot\mathbf{E}
        \right)
        -
        \nabla^{2}\mathbf{E}
        &&
        (\textrm{Curl of a curl formula})\\
        \!\!
        &=&
        \!\!
        \displaystyle
        \nabla\left(\frac{\rho}{\epsilon_{0}}\right)
        -
        \nabla^{2}\mathbf{E}
        &&
        (\textrm{Gauss' Law})
    \end{array}
\end{equation}

We may use this on the magnetic field as well, obtaining:

\begin{equation}
    \def\arraystretch{2.3em}
    \begin{array}{rclll}
        \displaystyle
        \nabla\times(\nabla\times\mathbf{B})
        \!\!
        &=&
        \!\!
        \displaystyle
        \nabla\left(
            \nabla\cdot\mathbf{B}
        \right)
        -
        \nabla^{2}\mathbf{B}
        &&
        (\textrm{Curl of a curl formula})\\
        \!\!
        &=&
        \!\!
        \displaystyle
        -\nabla^{2}\mathbf{B}
        &&
        (\textrm{Gauss' Law of Magnetism})
    \end{array}
\end{equation}

Applying the Maxwell equations, we may expand the left-hand
sides of these equations. We assume that the electric and
magnetic fields $\mathbf{E}$ and $\mathbf{B}$ are sufficiently
smooth so that we may rearrange the order of differentiation
at will. This is a valid assumption in practice.

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rclll}
        \displaystyle
        \nabla\times(\nabla\times\mathbf{E})
        \!\!
        &=&
        \!\!
        \displaystyle
        \nabla\times\left(
            -\frac{\partial\mathbf{B}}{\partial{t}}
        \right)
        &&
        (\textrm{Faraday's Law})\\
        \!\!
        &=&
        \!\!
        \displaystyle
        -\frac{\partial}{\partial{t}}
        \left(
            \nabla\times\mathbf{B}
        \right)
        &&
        (\textrm{Rearrange derivatives})\\
        \!\!
        &=&
        \!\!
        \displaystyle
        -\frac{\partial}{\partial{t}}
        \left(
            \mu_{0}\mathbf{J}
            +
            \mu_{0}\epsilon_{0}
                \frac{\partial\mathbf{E}}{\partial{t}}
        \right)
        &&
        (\textrm{Amp\`{e}re-Maxwell Law})\\
        \!\!
        &=&
        \!\!
        \displaystyle
        -\mu_{0}\frac{\partial\mathbf{J}}{\partial{t}}
        -
        \mu_{0}\epsilon_{0}
            \frac{\partial^{2}\mathbf{E}}{\partial^{2}t}
        &&
        (\textrm{Distribute derivative})
    \end{array}
\end{equation}

The magnetic field can be dealt with similarly.

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rclll}
        \displaystyle
        \nabla\times\left(
            \nabla\times\mathbf{B}
        \right)
        \!\!
        &=&
        \!\!
        \displaystyle
        \nabla\times\left(
            \mu_{0}\mathbf{J}
            +
            \mu_{0}\epsilon_{0}
            \frac{\partial\mathbf{E}}{\partial{t}}
        \right)
        &&
        (\textrm{Amp\`{e}re-Maxwell Law})\\
        \!\!
        &=&
        \!\!
        \displaystyle
        \mu_{0}\nabla\times\mathbf{J}
        +
        \mu_{0}\epsilon_{0}
        \frac{\partial}{\partial{t}}
        \left(
            \nabla\times\mathbf{E}
        \right)
        &&
        (\textrm{Rearrange derivatives})\\
        \!\!
        &=&
        \!\!
        \displaystyle
        \mu_{0}
        \nabla\times\mathbf{J}
        -
        \mu_{0}\epsilon_{0}
        \frac{\partial^{2}\mathbf{B}}{\partial{t}^{2}}
        &&
        (\textrm{Faraday's Law})
    \end{array}
\end{equation}

Let's combine all of this together.

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rcl}
        \displaystyle
        \nabla^{2}\mathbf{E}
        \!\!
        &=&
        \!\!
        \displaystyle
        \nabla\left(\frac{\rho}{\epsilon_{0}}\right)
        +
        \mu_{0}\frac{\partial\mathbf{J}}{\partial{t}}
        +
        \mu_{0}\epsilon_{0}
        \frac{\partial^{2}\mathbf{E}}{\partial^{2}t}\\
        \displaystyle
        \nabla^{2}\mathbf{B}
        \!\!
        &=&
        \!\!
        \displaystyle
        \mu_{0}\epsilon_{0}
        \frac{\partial^{2}\mathbf{B}}{\partial{t}^{2}}
        -
        \mu_{0}\nabla\times\mathbf{J}
    \end{array}
\end{equation}

Not much we can do with this, so let's simplify our setting.
We now work in a *vacuum*. That is, $\rho=0$ and
$\mathbf{J}=\mathbf{0}$. The Maxwell equations are then:

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rclll}
        \displaystyle
        \nabla\cdot\mathbf{E}
        \!\!
        &=&
        \!\!
        \displaystyle
        0
        &&
        (\textrm{Gauss's Law in Vacuum})\\
        \displaystyle
        \nabla\times\mathbf{E}
        \!\!
        &=&
        \!\!
        \displaystyle
        -\frac{\partial\mathbf{B}}{\partial{t}}
        &&
        (\textrm{Faraday's Law in Vacuum})\\
        \displaystyle
        \nabla\cdot\mathbf{B}
        \!\!
        &=&
        \!\!
        0
        &&
        (\textrm{Faraday's Law in Vacuum})\\
        \displaystyle
        \nabla\times\mathbf{B}
        \!\!
        &=&
        \!\!
        \displaystyle
        \mu_{0}\epsilon_{0}
        \frac{\partial\mathbf{E}}{\partial{t}}
        &&
        (\textrm{Amp\`{e}re-Maxwell Law in Vacuum})\\
    \end{array}
\end{equation}

Gauss' law of magnetism and Faraday's law are unchanged in a vacuum, but
the other two laws have simplified quite a bit.
Our previous calculations simplify and become:

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rcl}
        \displaystyle
        \nabla^{2}\mathbf{E}
        \!\!
        &=&
        \!\!
        \displaystyle
        \mu_{0}\epsilon_{0}
            \frac{\partial^{2}\mathbf{E}}{\partial{t}^{2}}\\
        \displaystyle
        \nabla^{2}\mathbf{B}
        \!\!
        &=&
        \!\!
        \displaystyle
        \mu_{0}\epsilon_{0}
        \frac{\partial^{2}\mathbf{B}}{\partial{t}^{2}}
    \end{array}
\end{equation}

The quantity $\epsilon_{0}$ had measured values at the time of
Maxwell's work, and it was known to be non-zero and positive.
Similarly, $\mu_{0}$ is positive, meaning $\mu_{0}\epsilon_{0}$ is a
positive value. But then there is some positive real number $c$ satisfying:

\begin{equation}
    c^{2}
    =
    \frac{1}{\mu_{0}\epsilon_{0}}
\end{equation}

Using this quantity $c$, the previous equations become:

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rcl}
        \displaystyle
        \nabla^{2}\mathbf{E}
        \!\!
        &=&
        \!\!
        \displaystyle
        \frac{1}{c^{2}}
            \frac{\partial^{2}\mathbf{E}}{\partial{t}^{2}}\\
        \displaystyle
        \nabla^{2}\mathbf{B}
        \!\!
        &=&
        \!\!
        \displaystyle
        \frac{1}{c^{2}}
            \frac{\partial^{2}\mathbf{B}}{\partial{t}^{2}}
    \end{array}
\end{equation}

Over a hundred years prior, Leonhard Euler showed that
these types of equations describe *waves*. These are examples
of the *three dimensional wave equation*. The measured quantities
$\mu_{0}$ and $\epsilon_{0}$ give an agreement with the
measured value of the speed of light, which is the new variable
$c$. Maxwell proposed that **light is an electromagnetic wave.**
