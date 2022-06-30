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
 ******************************************************************************/

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(256);

/*  Default pen for drawings.                                                 */
defaultpen(black + linewidth(0.5pt));

/*  Needed for the use of mathbb and mathcal commands.                        */
texpreamble("\usepackage{amssymb}");

/*  Used for drawing paths.                                                   */
path g;

int n;
int n_dots = 12;

pair f(int n, pair P)
{
    real theta = 2.0*pi/(n+1);
    real factor = 1.0 / (n*n + 1.0);
    real x = cos(theta)*factor;
    real y = sin(theta)*factor;
    return (x, y) + P;
}

/*  Variables for the dot x.                                                  */
real radius = 0.002;
pair A = (0.5, -0.3);
pair B = A + scale(radius)*expi(pi/6);

/*  Pens used for filling and drawing.                                        */
pen fpen = red+0.3*white;
pen dpen = linewidth(0.5pt);

/*  Draw the manifold X, shifted over to the left.                            */
g = (0.0,  0.0){dir(90)}..(0.5,   0.2){dir(0)}..
    (1.0,  0.0){dir(-90)}..(0.5, -0.5){dir(180)}..
    (0.0, -0.5){dir(150)}..cycle;

draw(g, dpen);

/*  Pen for ball about the point x.                                           */
filldraw(circle(A, 3.0*radius), black, black);
label("$x$", A, SW);

for (n = 2; n < n_dots; ++n)
    filldraw(circle(f(n, A), radius), black, black);

/*  Add some labels.                                                          */
label("$X$", (0.4,  0.0));
label("$a_{n}$", (0.55, -0.15));
