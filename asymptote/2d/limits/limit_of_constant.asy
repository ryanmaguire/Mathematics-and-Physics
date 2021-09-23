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
real rsmall = 0.008;
real rbig = 0.015;

/*  Integer for indexing.                                                     */
int n;

/*  Values for looping over the points in the graph.                          */
pair X, XY;
real val;

/*  The constant the function is equal to.                                    */
real c = 0.6;

/*  Number of dots to draw.                                                   */
int N = 7;

/*  Start and end values for the axes.                                        */
real start = -1.2;
real end = 1.5;

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  Labels for the axes.                                                      */
Label x_label = Label("$x$", position = 1.0);
Label y_label = Label("$y$", position = 1.0);

/*  Draw the axes.                                                            */
draw(x_label, (start, 0.0) -- (end, 0.0), (0, 1), apen, SharpArrows(arsize));
draw(y_label, (0.0, start) -- (0.0, end), (1, 0), apen, SharpArrows(arsize));

/*  Loop over the points getting closer to x_0.                               */
for (n = 0; n < N; ++n)
{
    /*  Compute the current point.                                            */
    val = 1.0 - 1.0/2^n;

    /*  Projection onto the x axes.                                           */
    X = (val, 0.0);

    /*  The actual point.                                                     */
    XY = (val, c);

    /*  Draw in the projection on the x axis and the point.                   */
    filldraw(circle(X, rsmall), black, black);
    filldraw(circle(XY, rsmall), black, black);

    /*  Draw dashed lines indicating the projection.                          */
    draw(X -- XY, dpen);
}

/*  Label x_0.                                                                */
val = 1.0;
X = (val, 0.0);
XY = (val, c);
filldraw(circle(X, rbig), black, black);
filldraw(circle(XY, rbig), black, black);
draw(X -- XY, dpen);
label("$x_{0}$", (1.0, -0.1));
label("$f(x_{0})$", (-0.2, c + 0.1));

/*  Draw the function f(x) = c.                                               */
draw((start, c) -- (end, c));

/*  Label the function.                                                       */
label("$f(x)=c$", (0.4*end, 0.8*end));
