/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;
import graph;
import animation;

/*  Change the output to a "gif" for an animation.                            */
settings.outformat="gif";
size(1024);

// Necessary variables for drawing the surfaces and creating the .GIF file.
animation a;

real start, end, invstart, invend, lim, shiftval, y0, dy, y_finish;
pair[] XAxes, YAxes;
int samples, N_Figs, n;
path xaxis, yaxis, clippath;

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

bool3 branch(real x)
{
  static int lastsign=0;
  if(x == 0) return false;
  int sign=sgn(x);
  bool b=lastsign == 0 || sign == lastsign;
  lastsign=sign;
  return b ? true : default;
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

N_Figs = 60;
y0 = -1.5;
y_finish = -0.01;
dy = (y_finish-y0)/N_Figs;

arsize = 20bp;
axesp  = black + linewidth(1.4pt);
thinp  = black + linewidth(0.5pt);
clippath = (-lim, -lim) -- (lim, -lim) -- (lim, lim) -- (-lim, lim) -- cycle;

write("Running Computations...");
for (n=0; n<N_Figs; ++n)
{
    pair square(real t)
    {
        return (t, t*t + y0);
    }

    pair invsquare(real t)
    {
        return InverseCurve(square, t);
    }

    /* Create the image.                                                      */
    save();

    /* Draw the coordinate axes for the plane.                                */
    draw(xaxis, N, axesp, SharpArrow(arsize));
    draw(yaxis, E, axesp, SharpArrow(arsize));

    /* Plot the functions.                                                    */
    draw(graph(square, start, end, n=samples), red);
    draw(graph(invsquare, invstart, invend, n=samples), blue);

    /*  Draw the circle of inversion.                                         */
    draw(circle((0.0, 0.0), 1.0), thinp);
    clip(clippath, evenodd);

    a.add();
    restore();
    y0 += dy;
}

y0 = 0.01;
y_finish = 1.5;
dy = (y_finish-y0)/N_Figs;

pair square(real t)
{
    return (t, t*t + y0);
}

pair invsquare(real t)
{
    return InverseCurve(square, t);
}

for (n=0; n<N_Figs; ++n)
{
    /* Create the image.                                                      */
    save();

    /* Draw the coordinate axes for the plane.                                */
    draw(xaxis, N, axesp, SharpArrow(arsize));
    draw(yaxis, E, axesp, SharpArrow(arsize));

    /* Plot the functions.                                                    */
    draw(graph(square, start, end, n=samples), red);
    draw(graph(invsquare, invstart, invend, n=samples), blue);

    /*  Draw the circle of inversion.                                         */
    draw(circle((0.0, 0.0), 1.0), thinp);
    clip(clippath, evenodd);

    a.add();
    restore();
    y0 += dy;
}

// Render the gif.
write("Rendering GIF...");
a.movie(delay=20);
