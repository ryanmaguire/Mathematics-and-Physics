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
pen thinp = black + linewidth(0.5pt);
pen funcfill = gray(0.7);

real xstart = 0.0;
real xend = 1.0;
real start = -0.1;
real end = 1.3;
real arsize = 5bp;
real xs = 1.8;

real f0(real x)
{
    return x*x*x - x*x + 0.2*x + 1.0;
}

real g0(real x)
{
    return x*x*x - x*x + 0.2*x + 0.7;
}

real f1(real x)
{
    return f0(x) - 0.4*sin(pi*x);
}

real g1(real x)
{
    return g0(x) - 0.4*sin(pi*x);
}

Label xl = Label("$x$", (end, 0.0), position = 1.0);
Label yl = Label("$y$", (0.0, end), position = 1.0);

path g = graph(f0, xstart, xend) -- reverse(graph(g0, xstart, xend)) -- cycle;
filldraw(g, funcfill, black);

draw(xl, (start, 0.0) -- (end, 0.0), N, axesp, SharpArrow(arsize));
draw(yl, (0.0, start) -- (0.0, end), E, axesp, SharpArrow(arsize));
draw((xend, f0(xend)) -- (xend, 0.0), thinp);

path g = graph(f1, xstart, xend) -- reverse(graph(g1, xstart, xend)) -- cycle;
filldraw(shift(xs, 0.0)*g, funcfill, black);
draw(shift(xs, 0.0)*((xend, f0(xend)) -- (xend, 0.0)), thinp);

draw(xl, (start+xs, 0.0) -- (end+xs, 0.0), N, axesp, SharpArrow(arsize));
draw(yl, (xs, start) -- (xs, end), E, axesp, SharpArrow(arsize));
