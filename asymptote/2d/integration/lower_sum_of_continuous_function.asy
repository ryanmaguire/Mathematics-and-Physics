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
size(128);

/*  Default pen for drawings.                                                 */
defaultpen(black + linewidth(0.6pt));

/*  Pens used throughout the drawing.                                         */
pen axesp = black + linewidth(0.8pt);
pen thinp = black + linewidth(0.5pt);
pen funcfill = blue;
pen minfill = red;
pen maxfill = green;
pen fillp = gray(0.7);

real xstart = 0.0;
real xend = 1.0;
real start = -0.1;
real end = 1.1;
real arsize = 5bp;

real func(real x)
{
    return x*x*x - x + 1.0;
}

real xmin = 1.0 / sqrt(3.0);
real ymin = func(xmin);

path g;

int n;
int n_rectangles = 20;

real x0 = xstart;
real dx = (xend - xstart) / n_rectangles;
real x1, y;

Label xl = Label("$x$", (end, 0.0), position = 1.0);
Label yl = Label("$y$", (0.0, end), position = 1.0);

draw(xl, (start, 0.0) -- (end, 0.0), N, axesp, SharpArrow(arsize));
draw(yl, (0.0, start) -- (0.0, end), E, axesp, SharpArrow(arsize));

for (n = 0; n < n_rectangles; ++n)
{
    x1 = x0 + dx;
    if (x0 < xmin && x1 > xmin)
        y = ymin;
    else if (x0 < xmin)
        y = func(x1);
    else
        y = func(x0);

    g = (x0, 0.0) -- (x0, y) -- (x1, y) -- (x1, 0.0) -- cycle;
    filldraw(g, fillp, black);
    x0 = x1;
}

g = (xstart, 0.0) -- graph(func, xstart, xend) -- (xend, 0.0) -- cycle;
draw(g);

