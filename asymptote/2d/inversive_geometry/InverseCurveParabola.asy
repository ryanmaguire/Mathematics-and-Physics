/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;
import graph;

/* Size of the output figure.                                                 */
size(256);
real start, end, invstart, invend, lim, shiftval;
transform T;
pair[] XAxes, YAxes;
int samples;
path g, ginv, xaxis, yaxis, clippath;
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
