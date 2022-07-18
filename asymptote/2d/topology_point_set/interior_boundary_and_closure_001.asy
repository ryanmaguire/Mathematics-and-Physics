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
defaultpen(black + linewidth(0.7pt));

/*  Needed for the use of mathbb and mathcal commands.                        */
texpreamble("\usepackage{amssymb}");

/*  Used for drawing paths.                                                   */
path g0, g1;
transform T;

/*  Variables for the dot x.                                                  */
real radius = 0.25;
pair A = (2.8, -0.3);
pair B = A + scale(radius)*expi(pi/6);

/*  Pens used for filling and drawing.                                        */
pen cyanp = cyan + opacity(0.5);
pen redp = red + opacity(0.5);
pen bluep = blue + opacity(0.5);
pen dashp = linewidth(0.7pt) + linetype("4 4");

/*  Draw the manifold X, shifted over to the left.                            */
g0 = (0.0,  0.0){dir(100)}..(2.0,   1.0){dir(0)}..
     (4.0,  0.0){dir(-90)}..(2.0, -1.0){dir(180)}..
     (0.0, -1.0){dir(100)}..cycle;

/*  Draw a cyan blob for U.                                                   */
g1 = (1.6, 0.0){dir(35)}.. (2.7,  0.5){dir(10)}..
     (3.5, 0.2){dir(-100)}..(3.2, -0.7){dir(190)}..
     (2.0, -0.8){dir(140)}..cycle;

draw(g0);
filldraw(g1, cyanp, invisible);
draw(subpath(g1, 1, 5), dashp);
draw(subpath(g1, 0, 1));
label("$A$", (2.5, -0.3));
label("$X$", (1.0,  0.4));

T = shift(4.5, 0.0);
draw(T*g0);
filldraw(T*g1, redp, black);
label("$\textrm{Cl}_{\tau}(A)$", T*(2.5, -0.3));
label("$X$", T*(1.0,  0.4));

T = shift(0.0, -3.0);
draw(T*g0);
filldraw(T*g1, bluep, dashp);
label("$\textrm{Int}_{\tau}(A)$", T*(2.5, -0.3));
label("$X$", T*(1.0,  0.4));

T = shift(4.5, -3.0);
draw(T*g0);
draw(T*g1, black);
label("$\partial_{\tau}(A)$", T*(2.5, -0.3));
label("$X$", T*(1.0,  0.4));

