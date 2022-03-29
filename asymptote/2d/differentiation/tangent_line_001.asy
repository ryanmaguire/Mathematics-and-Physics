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
 *      Figure from a first semester calculus course. This shows the tangent  *
 *      line for a function at a point.                                       *
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

/*  The derivative of func.                                                   */
real func_prime(real x)
{
    real x2 = x*x;
    return 2.0 + x2*(-9.0 + 5.0*x2);
}

/*  Size of the image.                                                        */
size(256);

/*  Number of samples for the function.                                       */
int samples = 30;

/*  Start and end for the x and y axes.                                       */
real start = -0.2;
real end = 1.6;

/*  Start and end points for the function.                                    */
real fstart = 0.0;
real fend = 1.4;

/*  Start and end points for the tangent line.                                */
real fpstart = 0.2;
real fpend = 1.2;

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  The point we care about.                                                  */
real x0 = 1.0;
real y0 = func(x0);
pair P0 = (x0, y0);

/*  Variables for the tangent line.                                           */
pair Q0, Q1;

/*  Factors for the slope-intercept form of the tangent line.                 */
real m, b;

/*  Pens for the axes and function.                                           */
pen axesp = black + linewidth(1.0pt) + fontsize(12pt);
pen funcp = deepblue + linewidth(0.8pt);
pen drawp = black + linewidth(0.6pt);

/*  Labels for the axes.                                                      */
Label xl = Label("$x$", position = 1.0);
Label yl = Label("$y$", position = 1.0);

/*  Draw the axes.                                                            */
draw(xl, (start, 0.0) -- (end, 0.0), N, axesp, SharpArrow(arsize));
draw(yl, (0.0, start) -- (0.0, end), E, axesp, SharpArrow(arsize));

/*  And draw the function.                                                    */
draw(graph(func, fstart, fend, n=samples, operator ..), funcp);

/*  Compute the slope and y-intercept of the tangent line.                    */
m = func_prime(x0);
b = y0 - m*x0;

/*  Compute two points on the tangent line.                                   */
Q0 = (fpstart, m*fpstart + b);
Q1 = (fpend, m*fpend + b);

/*  Draw the tangent line.                                                    */
draw(Q0 -- Q1, drawp);
