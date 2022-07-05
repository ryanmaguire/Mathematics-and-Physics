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
real radius = 0.25;
pair A = (2.8, -0.3);
pair B = A + scale(radius)*expi(pi/6);

/*  Pens used for filling and drawing.                                        */
pen fpen = red+0.3*white;
pen dpen = linewidth(0.5pt);

/*  Draw the manifold X, shifted over to the left.                            */
g = (0.0,  0.0){dir(90)}..(2.0,   1.0){dir(0)}..
    (4.0,  0.0){dir(-90)}..(2.0, -1.0){dir(180)}..
    (0.0, -1.0){dir(150)}..cycle;

draw(g, dpen);

/*  Draw a cyan blob for U.                                                   */
fpen = red;

g = (2.0, 0.0){dir(30)}.. (2.7,  0.5){dir(0)}..
    (3.5, 0.0){dir(-90)}..(3.2, -0.6){dir(180)}..
    (2.2, -0.8){dir(150)}..cycle;

filldraw(g, fpen, defaultpen);

/*  Pen for ball about the point x.                                           */
fpen = cyan;

g = A + (0.4, 0.3) .. (A + (0.5, -0.1)) .. (A + (0.0, -0.2)) ..
    (A + (-0.3, -0.12)) .. (A + (-0.3, 0.2)) .. cycle; 
filldraw(g, fpen, dpen+linetype("8 4"));
dot(A);
label("$x$", A, SW);

/*  Add some labels.                                                          */
label("$K$", (3.1, 0.25));
label("$X$", (1.0,  0.4));
label("$\mathcal{U}$", A, NE);
