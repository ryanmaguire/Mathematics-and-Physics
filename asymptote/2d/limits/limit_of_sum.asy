/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of Mathematics-and-Physics.                             *
 *                                                                            *
 *  Mathematics-and-Physics is free software: you can redistribute it and/or  *
 *  modify it under the terms of the GNU General Public License as published  *
 *  by the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  Mathematics-and-Physics is distributed in the hope that it will be useful *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with Mathematics-and-Physics.  If not, see                          *
 *  <https://www.gnu.org/licenses/>.                                          *
 ******************************************************************************/

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Used for plotting functions.                                              */
import graph;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the graph.                                                        */
size(256);

/*  Default pen for the function.                                             */
defaultpen(black + linewidth(0.4pt));

/*  Pen for the axes.                                                         */
pen apen = black + linewidth(0.7pt);

/*  Dashed pen for the sequence.                                              */
pen dpen = black + linewidth(0.2pt) + linetype("4 4");

/*  Radii of small and big dots.                                              */
real rsmall = 0.04;

/*  Integer for indexing.                                                     */
int n;

/*  Number of samples in the drawings.                                        */
int n_samples = 100;

/*  Values for looping over the points in the graph.                          */
pair X, Y, XY;
real xval, yval;

/*  Number of dots to draw.                                                   */
int N = 7;

/*  Start and end values for the axes.                                        */
real start = -1.5;
real end = 10.0;

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  Labels for the axes.                                                      */
Label x_label = Label("$x$", position = 1.0);
Label y_label = Label("$y$", position = 1.0);

/*  The first function in the sum.                                            */
real f(real x)
{
    return 1.0 + sqrt(x+1.0) + sin(x);
}

/*  The second function.                                                      */
real g(real x)
{
    /*  Evaluate the polynomial via Horner's method.                          */
    return 4.0 + x*x*(1.0 + x*(-0.333333 + 0.025*x));
}

/*  The sum of f and g.                                                       */
real h(real x)
{
    return f(x) + g(x);
}

/*  Draw the axes.                                                            */
draw(x_label, (start, 0.0) -- (end, 0.0), (0, 1), apen, SharpArrow(arsize));
draw(y_label, (0.0, start) -- (0.0, end), (1, 0), apen, SharpArrow(arsize));

/*  Loop over the points getting closer to x_0.                               */
for (n = 0; n < N; ++n)
{
    /*  Compute the current point.                                            */
    xval = 0.5*end - 0.25*end/2^n;
    yval = h(xval);

    /*  Projection onto the x and y axes.                                     */
    X = (xval, 0.0);
    Y = (0.0, yval);

    /*  The actual point.                                                     */
    XY = (xval, yval);

    /*  Draw in the projections on the x and y axes, and the point.           */
    filldraw(circle(X, rsmall), black, black);
    filldraw(circle(Y, rsmall), black, black);
    filldraw(circle(XY, rsmall), black, black);

    /*  Draw dashed lines indicating the projections.                         */
    draw(X -- XY -- Y, dpen);
}

/*  Draw the functions.                                                       */
draw(graph(f, 0.0, end, n=n_samples), blue);
draw(graph(g, 0.0, end, n=n_samples), red);
draw(graph(h, 0.0, end, n=n_samples));

/*  Label the functions.                                                      */
label("$f(x)$", (0.1*end, 0.2*end), blue);
label("$g(x)$", (0.75*end, 0.2*end), red);
label("$f(x)+g(x)$", (0.7*end, 0.7*end));

/*  Crop the drawing.                                                         */
scale(false);
xlimits(1.05*start, 1.05*end);
ylimits(1.05*start, 1.05*end);
crop();
