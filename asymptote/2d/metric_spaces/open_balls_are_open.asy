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

/*  Variables for the dot x.                                                  */
real radius = 0.7;
real factor = 0.4;
pair A = (2.2, -0.1);
pair B = A + scale(radius)*expi(pi/6);
pair C = A + scale((1.0 - factor)*radius)*expi(0.75*pi);
pair D = C + (factor*radius)*expi(-0.2*pi);

/*  Pens used for filling and drawing.                                        */
pen cyanp = cyan + opacity(0.5);
pen redp = red + opacity(0.5);
pen dashp = linewidth(0.5pt) + linetype("8 4");

/*  Draw the manifold X, shifted over to the left.                            */
g = (0.0,  0.0){dir(90)}..(2.0,   1.0){dir(0)}..
    (4.0,  0.0){dir(-90)}..(2.0, -1.0){dir(180)}..
    (0.0, -1.0){dir(150)}..cycle;

draw(g);
filldraw(shift(A)*scale(radius)*unitcircle, cyanp, dashp);
dot(A);
label("$x$", A, SW);
draw("$r$", A--B);
label("$y$", C, NW);
draw("$\varepsilon$", C -- D);
filldraw(circle(C, factor*radius), redp, dashp);
dot(C);
label("$X$", (1.0,  0.4));
