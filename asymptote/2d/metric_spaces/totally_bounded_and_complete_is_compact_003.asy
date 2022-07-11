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
int n_dots = 30;
real radius = 0.7;
pen dpen = linewidth(0.5pt) + linetype("4 4");
pen fpen = cyan + opacity(0.3);

/*  Draw the manifold X, shifted over to the left.                            */
g = (0.0,  0.3){dir(100)}..(2.3,   1.2){dir(10)}..
    (4.0,  0.1){dir(-80)}..(2.1, -1.1){dir(165)}..
    (0.0, -1.2){dir(150)}..cycle;
draw(g);
filldraw(circle((2.1, 0.0), radius), fpen, dpen);
filldraw(circle((2.2, 0.1), 0.5*radius), fpen, dpen);
filldraw(circle((2.15, 0.0), 0.3*radius), fpen, dpen);
filldraw(circle((2.2, 0.0), 0.2*radius), fpen, dpen);
filldraw(circle((2.15, 0.0), 0.1*radius), fpen, dpen);

filldraw(circle((2.1, 0.0) + scale(0.6)*expi(0.27*pi), 0.01), black);
filldraw(circle((2.1, 0.0) + scale(0.4)*expi(0.27*pi), 0.01), black);
filldraw(circle((2.1, 0.0) + scale(0.21)*expi(0.27*pi), 0.01), black);
filldraw(circle((2.1, 0.0) + scale(0.12)*expi(0.27*pi), 0.01), black);
filldraw(circle((2.1, 0.0) + scale(0.05)*expi(0.27*pi), 0.01), black);

label("$X$", (1.0,  0.75));
