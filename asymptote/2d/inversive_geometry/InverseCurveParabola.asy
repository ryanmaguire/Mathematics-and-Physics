/* Make sure _custom_arrows.asy, _asy_preamble_2d, and _euc_geo_2d are in     *
 *  your ASYMPTOTE_DIR environment variable. These are found in the           *
 *  asymptote/ folder.                                                        */
import _asy_preamble_2d;
import _custom_arrows;
import _inversive;
import graph;

/* Size of the output figure.                                                 */
size(256);
real start, end, invstart, invend, lim, shiftval;
transform T;
pair[] XAxes, YAxes;
int samples;
path g, ginv, xaxis, yaxis, clippath;
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

start = -1.7;
invstart = -6.0;
end = -start;
invend = -invstart;
samples = 1000;
Lx = Label("$x$", position=1);
Ly = Label("$y$", position=1);

clippath = (-lim, -lim) -- (lim, -lim) -- (lim, lim) -- (-lim, lim) -- cycle;

/******************************************************************************
 ******************************************************************************
 *                    First Parabola: y = x^2 - 1.25                          *
 ******************************************************************************
 ******************************************************************************/
pair square(real t)
{
    return (t, t*t-1.25);
}

pair invsquare(real t)
{
    return InverseCurve(square, t);
}

T = shift(0.0, 0.0);

/* Draw the coordinate axes for the plane.                                    */
draw(Lx, T*xaxis, N, axesp, SharpArrow(arsize));
draw(Ly, T*yaxis, E, axesp, SharpArrow(arsize));

/* Plot the functions.                                                        */
g = graph(square, start, end, n=samples);
ginv = graph(invsquare, invstart, invend, n=samples);

draw(T*g, thinp);
draw(T*ginv, thinp);

/*  Draw the circle of inversion.                                             */
draw(T*circle((0.0, 0.0), 1.0), dashp);

/******************************************************************************
 ******************************************************************************
 *                     Second Parabola: y = x^2 - 0.5                         *
 ******************************************************************************
 ******************************************************************************/

pair square(real t)
{
    return (t, t*t-0.5);
}

pair invsquare(real t)
{
    return InverseCurve(square, t);
}

T = shift(shiftval, 0.0);

/* Draw the coordinate axes for the plane.                                    */
draw(Lx, T*xaxis, N, axesp, SharpArrow(arsize));
draw(Ly, T*yaxis, E, axesp, SharpArrow(arsize));

/* Plot the functions.                                                        */
g = graph(square, start, end, n=samples);
ginv = graph(invsquare, invstart, invend, n=samples);

draw(T*g, thinp);
draw(T*ginv, thinp);

/*  Draw the circle of inversion.                                             */
draw(T*circle((0.0, 0.0), 1.0), dashp);

/******************************************************************************
 ******************************************************************************
 *                       Third Parabola: y = x^2                              *
 ******************************************************************************
 ******************************************************************************/
pair square(real t)
{
    return (t, t*t);
}

pair invsquare(real t)
{
    return InverseCurve(square, t);
}

T = shift(0.0, -shiftval);

/* Draw the coordinate axes for the plane.                                    */
draw(Lx, T*xaxis, N, axesp, SharpArrow(arsize));
draw(Ly, T*yaxis, E, axesp, SharpArrow(arsize));

/* Plot the functions.                                                        */
g = graph(square, start, end, n=samples);
ginv = graph(invsquare, invstart, -0.4, n=samples);

draw(T*g, thinp);
draw(T*ginv, thinp);

ginv = graph(invsquare, 0.4, invend, n=samples);
draw(T*ginv, thinp);

/*  Draw the circle of inversion.                                             */
draw(T*circle((0.0, 0.0), 1.0), dashp);

/******************************************************************************
 ******************************************************************************
 *                      Fourth Parabola: y = x^2 + 1                          *
 ******************************************************************************
 ******************************************************************************/
pair square(real t)
{
    return (t, t*t+1.0);
}

pair invsquare(real t)
{
    return InverseCurve(square, t);
}

T = shift(shiftval, -shiftval);

/* Draw the coordinate axes for the plane.                                    */
draw(Lx, T*xaxis, N, axesp, SharpArrow(arsize));
draw(Ly, T*yaxis, E, axesp, SharpArrow(arsize));

/* Plot the functions.                                                        */
g = graph(square, start, end, n=samples);
ginv = graph(invsquare, invstart, invend, n=samples);

draw(T*g, thinp);
draw(T*ginv, thinp);

/*  Draw the circle of inversion.                                             */
draw(T*circle((0.0, 0.0), 1.0), dashp);
