/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;
import graph;

/* Size of the output figure.                                                 */
size(256);
real start, end, invstart, invend, lim, shiftval, a;
transform T;
pair[] XAxes, YAxes;
int samples;
path g, ginv, xaxis, yaxis;
Label Lx, Ly;

pen axesp = black + linewidth(0.7pt);
pen thinp = black + linewidth(0.4pt);
pen dashp = black + linewidth(0.5pt) + linetype("4 4");
real arsize = 5bp;

real EuclideanNorm2D(pair P)
{
    return sqrt(P.x*P.x + P.y*P.y);
}

pair InverseCurve(pair f(real), real t)
{
    /*  Declare necessary variables.                                          */
    real X, Y, Px, Py, normsq;
    pair P, invP;

    /*  Compute the point from the given function f and the value t.          */
    P = f(t);

    /*  If P is the origin, the inverse of it is the point "at infinity" so   *
     *  we'll return the pair (inf, inf).                                     */
    normsq = EuclideanNorm2D(P);
    if (normsq == 0.0)
        return (inf, inf);

    /*  Otherwise, square the current value to get normsq.                    */
    else
        normsq = normsq*normsq;

    /*  Extract the x and y values from P.                                    */
    Px = P.x;
    Py = P.y;

    /*  Compute the inverse X and Y values with respect to the unit circle.   */
    X = Px/normsq;
    Y = Py/normsq;

    /*  The inverse of P is just (X, Y) so compute this and return.           */
    invP = (X, Y);
    return invP;
}

/* Points used to define the x and y axes.                                    */
lim = 2.5;
XAxes[0] = (-lim, 0.0);
XAxes[1] = (+lim, 0.0);
YAxes[0] = (0.0, -lim);
YAxes[1] = (0.0, +lim);
shiftval = 5.4;

xaxis = XAxes[0]--XAxes[1];
yaxis = YAxes[0]--YAxes[1];

start = -1.0;
end = -start;
invstart = -6.0;
invend = -invstart;
samples = 1000;
Lx = Label("$x$", position=1);
Ly = Label("$y$", position=1);

/******************************************************************************
 ******************************************************************************
 *                       First Hyperbola: a = 1.5                             *
 ******************************************************************************
 ******************************************************************************/

a = 1.5;
T = shift(0.0, 0.0);

pair hyperbolaright(real t)
{
    return (a*cosh(t), sinh(t));
}

pair invhyperbolaright(real t)
{
    return InverseCurve(hyperbolaright, t);
}

pair hyperbolaleft(real t)
{
    return (-a*cosh(t), sinh(t));
}

pair invhyperbolaleft(real t)
{
    return InverseCurve(hyperbolaleft, t);
}

/* Draw the coordinate axes for the plane.                                    */
draw(Lx, T*xaxis, N, axesp, SharpArrow(arsize));
draw(Ly, T*yaxis, E, axesp, SharpArrow(arsize));

/* Plot the functions.                                                        */
draw(T*graph(hyperbolaright, start, end, n=samples), thinp);
draw(T*graph(hyperbolaleft, start, end, n=samples), thinp);
draw(T*graph(invhyperbolaright, invstart, invend, n=samples), thinp);
draw(T*graph(invhyperbolaleft, invstart, invend, n=samples), thinp);

/*  Draw the circle of inversion.                                             */
draw(T*circle((0.0, 0.0), 1.0), dashp);

/******************************************************************************
 ******************************************************************************
 *                      Second Hyperbola: a = 1.0                             *
 ******************************************************************************
 ******************************************************************************/

a = 1.0;
T = shift(shiftval, 0.0);
start = -1.5;
end = -start;

pair hyperbolaright(real t)
{
    return (a*cosh(t), sinh(t));
}

pair invhyperbolaright(real t)
{
    return InverseCurve(hyperbolaright, t);
}

pair hyperbolaleft(real t)
{
    return (-a*cosh(t), sinh(t));
}

pair invhyperbolaleft(real t)
{
    return InverseCurve(hyperbolaleft, t);
}

/* Draw the coordinate axes for the plane.                                    */
draw(Lx, T*xaxis, N, axesp, SharpArrow(arsize));
draw(Ly, T*yaxis, E, axesp, SharpArrow(arsize));

/* Plot the functions.                                                        */
draw(T*graph(hyperbolaright, start, end, n=samples), thinp);
draw(T*graph(hyperbolaleft, start, end, n=samples), thinp);
draw(T*graph(invhyperbolaright, invstart, invend, n=samples), thinp);
draw(T*graph(invhyperbolaleft, invstart, invend, n=samples), thinp);

/*  Draw the circle of inversion.                                             */
draw(T*circle((0.0, 0.0), 1.0), dashp);

/******************************************************************************
 ******************************************************************************
 *                       Third Hyperbola: a = 0.5                             *
 ******************************************************************************
 ******************************************************************************/

a = 0.5;
T = shift(0, -shiftval);
start = -1.5;
end = -start;

pair hyperbolaright(real t)
{
    return (a*cosh(t), sinh(t));
}

pair invhyperbolaright(real t)
{
    return InverseCurve(hyperbolaright, t);
}

pair hyperbolaleft(real t)
{
    return (-a*cosh(t), sinh(t));
}

pair invhyperbolaleft(real t)
{
    return InverseCurve(hyperbolaleft, t);
}

/* Draw the coordinate axes for the plane.                                    */
draw(Lx, T*xaxis, N, axesp, SharpArrow(arsize));
draw(Ly, T*yaxis, E, axesp, SharpArrow(arsize));

/* Plot the functions.                                                        */
draw(T*graph(hyperbolaright, start, end, n=samples), thinp);
draw(T*graph(hyperbolaleft, start, end, n=samples), thinp);
draw(T*graph(invhyperbolaright, invstart, invend, n=samples), thinp);
draw(T*graph(invhyperbolaleft, invstart, invend, n=samples), thinp);

/*  Draw the circle of inversion.                                             */
draw(T*circle((0.0, 0.0), 1.0), dashp);

/******************************************************************************
 ******************************************************************************
 *                       Fourth Hyperbola: a = 0.0                            *
 ******************************************************************************
 ******************************************************************************/

T = shift(shiftval, -shiftval);

/*  Draw the circle of inversion.                                             */
draw(T*circle((0.0, 0.0), 1.0), dashp);

/* Draw the coordinate axes for the plane.                                    */
draw(Lx, T*xaxis, N, axesp, SharpArrow(arsize));
draw(Ly, T*yaxis, E, axesp, SharpArrow(arsize));
