# A Study of Heat
It would be great if we could simply *solve* the three dimensional
wave equation and obtain a nice formula for $\mathbf{E}$ and $\mathbf{B}$,
but such a problem isn't even *well-posed*. The solutions to these
equations are highly sensitive to the *initial conditions*, which are
values for $\mathbf{E}$ and $\mathbf{B}$ for all points in
space at a single given time moment $t_{0}$. But even with a chosen
set of initial conditions for $\mathbf{B}$ and $\mathbf{E}$, solving
these partial differential equations (in four variables!) is difficult.

We first resort to a slightly simpler problem, the idea of using mathematics
to model heat transfer. This was accomplished by Joseph Fourier in 1822,
and his methods led to the discovery of *Fourier analysis*,
*Fourier series*, and *Fourier transforms.* Astronomers and physicists make
frequent use of these ideas, and the equations we will describe later
concern the field of *Fourier optics.*

Fourier considers a bar of finite length $L$. The left and right
endpoints are held to fixed temperatures, $T_{L}$ and $T_{R}$,
respectively, and we do not require that $T_{L}=T_{R}$.
At time $t_{0}$ the heat distribution across the bar is given
by some smooth function $f(x)=u(x,\,t_{0})$. Fourier then derives
that $u$ satisfies the following partial differential equation:

\begin{equation}
    \frac{\partial{u}}{\partial{t}}
    =
    \alpha\frac{\partial^{2}u}{\partial{x}^{2}}
\end{equation}

Where $\alpha$ is some constant parameter.
Fourier then proposes the following solution.
Suppose $u$ can be written as the product of spatial and
temporal components. That is, suppose there are functions
$X$ and $T$ such that:

\begin{equation}
    u(x,\,t)
    =
    X(x)\,T(t)
\end{equation}

The heat equation then becomes (the $\Longrightarrow$ symbols reads as
*implies*):

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rrcl}
        &
        \displaystyle
        \frac{\partial{u}}{\partial{t}}
        \!\!
        &=&
        \!\!
        \displaystyle
        \alpha\frac{\partial^{2}u}{\partial{x}^{2}}\\
        \Longrightarrow
        &
        \displaystyle
        \frac{\partial}{\partial{t}}\left(
            X(x)\,T(t)
        \right)
        \!\!
        &=&
        \!\!
        \displaystyle
        \alpha
        \frac{\partial^{2}}{\partial{x}^{2}}\left(
            X(x)\,T(t)
        \right)\\
        \Longrightarrow
        &
        \displaystyle
        X(x)\,\frac{\textrm{d}T}{\textrm{d}t}(t)
        \!\!
        &=&
        \!\!
        \displaystyle
        \alpha{T}(t)\,
        \frac{\textrm{d}^{2}X}{\textrm{d}x^{2}}(x)\\
        \Longrightarrow
        &
        \displaystyle
        \frac{1}{\alpha{T}(t)}
        \frac{\textrm{d}T}{\textrm{d}t}(t)
        \!\!
        &=&
        \!\!
        \displaystyle
        \frac{1}{X(x)}
        \frac{\textrm{d}^{2}X}{\textrm{d}x^{2}}(x)
    \end{array}
\end{equation}

We note that the right-hand side is independent of $t$,
varying with $x$ only. Moreover, the left-hand side is
independent of $x$, varying with $t$ only. This can only
be true if both sides are constant! We label this constant
$-\lambda$ where $\lambda$ is some real number.
We then get the following
*system of ordinary differential equations*.

\begin{equation}
    \def\arraystretch{2.5em}
    \begin{array}{rcl}
        \displaystyle
        \frac{\textrm{d}T}{\textrm{d}t}(t)
        +
        \alpha\lambda{T}(t)
        \!\!
        &=&
        \!\!
        \displaystyle
        0\\
        \displaystyle
        \frac{\textrm{d}^{2}X}{\textrm{d}x^{2}}(x)
        +
        \lambda{X}(x)
        \!\!
        &=&
        \!\!
        \displaystyle
        0
    \end{array}
\end{equation}

Using methods from differential equations, we can solve these.
There will be some constants $A$, $B$, and $C$
such that:

\begin{equation}
    \def\arraystretch{2em}
    \begin{array}{rcl}
        \displaystyle
        T(t)
        \!\!
        &=&
        \!\!
        \displaystyle
        A\exp\left(-\lambda\alpha{t}\right)\\
        \displaystyle
        X(x)
        \!\!
        &=&
        \!\!
        \displaystyle
        B\cos(\sqrt{\lambda}x)
        +
        C\sin(\sqrt{\lambda}x)
    \end{array}
\end{equation}

If we set the initial temperatures $T_{L}$ and $T_{R}$ to zero
(the units we are working in do not matter), this simplifies further
since $C=0$ must be true. We can also show that $\lambda$ must
satisfy:

\begin{equation}
    \lambda
    =
    \frac{n^{2}\pi^{2}}{L^{2}}
\end{equation}

where $n$ is an integer.
The solution using this method yields:

\begin{equation}
    \displaystyle
    u(x,\,t)
    =
    a\sin\left(\frac{n\pi{x}}{L}\right)
    \exp\left(-\frac{n^{2}\pi^{2}\alpha{t}}{L^{2}}\right)
\end{equation}

where $a=AB$.
This is far too limiting. While this particular solution will
satisfy the initial conditions given by the endpoints, it will
probably *not* satisfy $u(x,\,t_{0})=f(x)$, our smooth function
that tells us how the heat was originally distributed across the bar.
Fourier notices that if $u_{0}$ and $u_{1}$ are solutions to the
heat equation, then so is $b_{0}u_{0}+b_{1}u_{1}$ for any real (or complex)
numbers $b_{0}$ and $b_{1}$. That is, the heat equation is a
*linear partial differential equation*. He the proposed summing
together *infinitely many* of these partial solutions to obtain the
solution $u$ that satisfies $u(x,\,t_{0})=f(x)$. That is:

\begin{equation}
    \displaystyle
    u(x,\,t)
    =
    \sum_{n=1}^{\infty}a_{n}
        \sin\left(\frac{n\pi{x}}{L}\right)
        \exp\left(-\frac{n^{2}\pi^{2}\alpha{t}}{L^{2}}\right)
\end{equation}

Fourier's work would be finished if he could somehow show that
*any* smooth function defined on the closed interval $[0,\,L]$
could be represented by a sum of sines. This is where
*Fourier analysis* begins.
