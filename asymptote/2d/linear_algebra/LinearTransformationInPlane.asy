/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;
import graph;

// Size of the output figure.
size(256);

pair T(real x, real y)
{
    return (x+y, -x + 2*y);
}

int n, N;
pair A, B;
real arsize = 5bp;

N = 10;

for (n=-N; n<=N; ++n)
{
    A = (n, -10);
    B = (n, 10);
    draw(A--B);

    A = (-10, n);
    B = (10, n);
    draw(A--B);
}

// Plot the axes.
draw((0, 0)--(1,0), linewidth(0.5pt), SharpArrow(arsize));
draw((0, 0)--(0,1), linewidth(0.5pt), SharpArrow(arsize));
filldraw(circle((0, 0), 0.05pt), black);

filldraw((0, 0) -- (3, 0) -- (3, 2) -- (0, 2) -- cycle, deepblue);

for (n=-N; n<=N; ++n)
{
    A = shift(35, 0)*T(n, -10);
    B = shift(35, 0)*T(n, 10);
    draw(A--B);

    A = shift(35, 0)*T(-10, n);
    B = shift(35, 0)*T(10, n);
    draw(A--B);
}

draw((35, 0)--shift(35, 0)*T(1,0), linewidth(0.5pt), SharpArrow(arsize));
draw((35, 0)--shift(35, 0)*T(0,1), linewidth(0.5pt), SharpArrow(arsize));

filldraw(shift(35, 0)*T(0, 0) -- shift(35, 0)*T(3, 0) -- shift(35, 0)*T(3, 2) -- shift(35, 0)*T(0, 2) -- cycle, deepred);
filldraw(circle((35, 0), 0.05pt), black);
