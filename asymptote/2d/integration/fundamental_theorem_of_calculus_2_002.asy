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

/*  Used for graphing functions.                                              */
import graph;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(256);

/*  Default pen for drawings.                                                 */
defaultpen(black + linewidth(0.6pt));

/*  Pens used throughout the drawing.                                         */
pen axesp = black + linewidth(0.8pt);
pen thinp = black + linewidth(0.5pt) + fontsize(7pt);

real func(real x)
{
    return x*x*x - x*x + 0.2*x + 1.0;
}

real tan_line(real x, real x0)
{
    real h = 1.0e-8;
    real dfunc = (func(x0+h)-func(x0))/h;
    return dfunc*(x-x0) + func(x0);
}

real xstart = 0.0;
real xend = 1.0;
real start = -0.1;
real end = 1.1;
real arsize = 5bp;

int n_samples = 9;
int n;
real dx = (xend - xstart)/n_samples;
real xa, xb, ya, yb;

Label xl = Label("$x$", (end, 0.0), position = 1.0);
Label yl = Label("$y$", (0.0, end), position = 1.0);

xa = xstart;
ya = func(xa);
for (n = 0; n < n_samples; ++n)
{
    xb = xa + dx;
    yb = tan_line(xb, xa);
    draw((xa, ya) -- (xb, yb), blue, SharpArrow(arsize));
    xa = xb;
    ya = yb;
}

draw(graph(func, xstart, xend));
draw(xl, (start, 0.0) -- (end, 0.0), N, axesp, SharpArrow(arsize));
draw(yl, (0.0, start) -- (0.0, end), E, axesp, SharpArrow(arsize));
draw((xend, func(xend)) -- (xend, 0.0));
