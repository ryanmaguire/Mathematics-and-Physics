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
pen funcfill0 = blue + opacity(0.5);
pen funcfill1 = red + opacity(0.5);

real func(real x)
{
    return x*(1.0 + x*x*(-1.0+x*x));
}

real xstart = 0.3;
real xend = 1.0;
real start = -0.1;
real end = 1.3;
real arsize = 5bp;
real ystart = func(xstart);
real yend = func(xend);

Label xl = Label("$x$", (end, 0.0), position = 1.0);
Label yl = Label("$y$", (0.0, end), position = 1.0);

path g = graph(func, xstart, xend);

filldraw((xstart, 0.0) -- g -- (xend, 0.0) -- cycle, funcfill0, black);
filldraw((0.0, ystart) -- g -- (0.0, yend) -- cycle, funcfill1, black);

g = (0.0, 0.0) -- (xstart, 0.0) -- (xstart, ystart) -- (0.0, ystart) -- cycle;
filldraw(g, gray(0.7), black);

draw(xl, (start, 0.0) -- (end, 0.0), N, axesp, SharpArrow(arsize));
draw(yl, (0.0, start) -- (0.0, end), E, axesp, SharpArrow(arsize));

label("$a$", (xstart, -0.05));
label("$b$", (xend, -0.05));
label("$f(a)$", (-0.08, ystart));
label("$f(b)$", (-0.08, yend));
label("$\displaystyle{\int_{a}^{b}y(x)\;\textrm{d}x}$", (0.65, 0.2));
label("$\displaystyle{\int_{f(a)}^{f(b)}x(y)\;\textrm{d}y}$", (0.25, 0.6));
label("$y=f(x)$", (0.85, 0.5));
label("$x=f^{-1}(y)$", (0.7, 0.8));
