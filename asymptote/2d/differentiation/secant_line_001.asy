/******************************************************************************
 *                                  LICENSE                                   *
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
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 6, 2021                                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Figure from a first semester calculus course. This shows a secant     *
 *      line approximating the derivative at a particular point.              *
 ******************************************************************************/

/*  Graphing tools are here.                                                  */
import graph;

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  The function being plotted.                                               */
real func(real x)
{
    real x2 = x*x;
    return x*(2.0 + x2*(-3.0 + x2));
}

/*  Size of the image.                                                        */
size(256);

/*  Number of samples for the function.                                       */
int samples = 30;

/*  Start and end for the x and y axes.                                       */
real start = -0.2;
real end = 1.6;

/*  Start and end points for the function.                                    */
real fstart = -0.1;
real fend = 1.35;

/*  Size of a dot.                                                            */
real rDot = 0.012;

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  The point we care about.                                                  */
real x0 = 1.0;
real y0 = func(x0);
pair P0 = (x0, y0);

/*  Variables for the secant line.                                            */
pair P1, Q0, Q1;

/*  Displacement for the secant line.                                         */
real dx = 0.2;

/*  Factors for the slope-intercept form of the secant line.                  */
real m, b;

/*  Pens for the axes and function.                                           */
pen axesp = black + linewidth(1.0pt) + fontsize(12pt);
pen drawp = black + linewidth(0.6pt);
pen funcp = deepblue + linewidth(0.8pt);
pen dashp = black + linewidth(0.6pt) + linetype("4 4");

/*  Labels for the axes.                                                      */
Label xl = Label("$x$", position = 1.0);
Label yl = Label("$y$", position = 1.0);

/*  Draw the axes.                                                            */
draw(xl, (start, 0.0) -- (end, 0.0), N, axesp, SharpArrow(arsize));
draw(yl, (0.0, start) -- (0.0, end), E, axesp, SharpArrow(arsize));

/*  And draw the function.                                                    */
draw(graph(func, fstart, fend, n=samples, operator ..), funcp);

/*  Compute the other point for the secant line.                              */
P1 = (x0 + dx, func(x0 + dx));

/*  Compute the slope and y-intercept of the secant line.                     */
m = (P1.y - P0.y)/(P1.x - P0.x);
b = y0 - m*x0;

/*  Compute two points on the secant line.                                    */
Q0 = (fstart, m*fstart + b);
Q1 = (fend, m*fend + b);

/*  Draw the dots.                                                            */
filldraw(circle((P1.x, P0.y), rDot), black, black);
filldraw(circle(P0, rDot), black, black);
filldraw(circle(P1, rDot), black, black);
draw(P0 -- (P1.x, y0) -- P1, dashp);

/*  Draw the secant line.                                                     */
draw(Q0 -- Q1, drawp);
