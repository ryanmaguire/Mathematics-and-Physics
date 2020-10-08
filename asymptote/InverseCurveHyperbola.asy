/* Make sure _custom_arrows.asy, _asy_preamble_2d, and _euc_geo_2d are in     *
 *  your ASYMPTOTE_DIR environment variable. These are found in the           *
 *  asymptote/ folder.                                                        */
import _asy_preamble_2d;
import _custom_arrows;
import _inversive;
import graph;

/* Size of the output figure.                                                 */
size(256);
real start, end, invstart, invend, lim, shiftval, a;
transform T;
pair[] XAxes, YAxes;
int samples;
path g, ginv, xaxis, yaxis;
Label Lx, Ly;

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
