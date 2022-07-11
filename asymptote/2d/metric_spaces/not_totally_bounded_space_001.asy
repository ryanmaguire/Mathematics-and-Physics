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
real radius = 0.3;
pair A, B;

/*  Pens used for filling and drawing.                                        */
pen fpen = cyan;
pen dpen = linewidth(0.5pt);

/*  Draw the manifold X, shifted over to the left.                            */
g = (0.0,  0.0){dir(80)}..(2.3,   1.2){dir(10)}..
    (4.0,  0.1){dir(-80)}..(2.1, -1.1){dir(175)}..
    (0.0, -1.2){dir(150)}..cycle;

draw(g, dpen);

A = (0.3, -0.5);
B = A + scale(radius)*expi(pi/6);

filldraw(shift(A)*scale(radius)*unitcircle, fpen, dpen+linetype("8 4"));
dot(A);
label("$a_{0}$", A, SW);
draw("$\varepsilon$", A -- B, dpen);

A = (1.1, 0.0);
B = A + scale(radius)*expi(pi/6);

filldraw(shift(A)*scale(radius)*unitcircle, fpen, dpen+linetype("8 4"));
dot(A);
label("$a_{1}$", A, SW);
draw("$\varepsilon$", A -- B, dpen);

label(rotate(25.0)*"$\cdots$", (1.7, 0.32));

A = (2.35, 0.6);
B = A + scale(radius)*expi(pi/6);

filldraw(shift(A)*scale(radius)*unitcircle, fpen, dpen+linetype("8 4"));
dot(A);
label("$a_{n}$", A, SW);
draw("$\varepsilon$", A -- B, dpen);

A = (2.9, 0.0);
B = A + scale(radius)*expi(pi/6);

filldraw(shift(A)*scale(radius)*unitcircle, fpen, dpen+linetype("8 4"));
dot(A);
label("$a_{n+1}$", A, S);
draw("$\varepsilon$", A -- B, dpen);

/*  Add some labels.                                                          */
label("$X$", (1.0,  0.75));
