/* Make sure _custom_arrows.asy, _asy_preamble_2d, and _euc_geo_2d are in     *
 *  your ASYMPTOTE_DIR environment variable. These are found in the           *
 *  asymptote/ folder.                                                        */
import _asy_preamble_2d;
import _custom_arrows;
import _inversive;
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

N_Figs = 80;
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

// Render the gif.
write("Rendering GIF...");
a.movie(delay=20);
