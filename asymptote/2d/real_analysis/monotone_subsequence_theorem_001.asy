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

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(512);

/*  Default pen for drawings.                                                 */
defaultpen(black + linewidth(0.7pt));
pen dpen = black + linewidth(0.4pt) + linetype("4 4");

real arsize = 5bp;
pair X0 = (-0.1, 0.0);
pair X1 = (1.2, 0.0);
pair Y0 = (0.0, -0.1);
pair Y1 = (0.0, 1.2);

int n_dots = 5;
int n;
pair[] A = {(0.2, 0.3), (0.4, 0.1), (0.6, 0.7), (0.8, 0.4), (1.0, 0.5)};

pair B0 = (-1.2, 0.4);
pair B1 = (-1.2, 0.6);
pair B2 = (-0.8, 0.6);
pair B3 = (-0.8, 0.4);

pair C0 = (-0.6, 0.7);
pair C1 = (-0.6, 0.3);
pair C2 = (-0.2, 0.3);
pair C3 = (-0.2, 0.7);

draw(Label("$x$", position=1.0), X0 -- X1, N, SharpArrow(arsize));
draw(Label("$y$", position=1.0), Y0 -- Y1, E, SharpArrow(arsize));

axialshade(C0 -- C1 -- C2 -- C3 -- cycle, yellow, (-0.6, 0.5), white, (-0.2, 0.5));
filldraw(B0 -- B1 -- B2 -- B3 -- cycle, black, black);
filldraw(B2{N} .. {E}C0 -- C1{W} .. {N}B3 -- cycle);
filldraw(ellipse((-1.0, 0.5), 0.07, 0.05), gray(0.5));
filldraw(A[0] -- (A[0].x, 0.0) -- (A[2].x, 0.0) -- (A[2].x, A[0].y) -- cycle, gray(0.5) + opacity(0.5), invisible);
filldraw(A[2] -- (A[2].x, 0.0) -- (1.14, 0.0) -- (1.14, A[2].y) -- cycle, gray(0.5) + opacity(0.5), invisible);

for (n = 0; n < n_dots; ++n)
{
    dot(A[n]);
    draw(A[n] -- (A[n].x, 0.0));
}
