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

/*  Size of the output figure.                                                */
size(256);

/*  Default pen for drawing.                                                  */
defaultpen(black + linewidth(0.4pt));

pair X = (2.2, 0.0);
pair Y = (0.0, 2.9);
pair Z = (2.2, 2.9);
int n;
int N = 8;
real arsize = 5bp;
real r = 0.05;
pen axesp = black+linewidth(0.7pt);
pen dashp = black+linewidth(0.4pt)+linetype("4 4");
pen gridp = gray(0.5)+linewidth(0.4pt);

for (n = 0; n < N; ++n)
{
    draw((n, -0.3) -- (n, 7.9), gridp);
    draw((-0.3, n) -- (7.9, n), gridp);
}

draw(Label("$x$", position=1.0), (-0.3, 0.0) -- (8.4, 0.0), S, axesp, SharpArrow(arsize));
draw(Label("$y$", position=1.0), (0.0, -0.3) -- (0.0, 8.4), W, axesp, SharpArrow(arsize));
draw(X -- Z, dashp);
draw(Y -- Z, dashp);
filldraw(circle(X, r), black, black);
filldraw(circle(Y, r), black, black);
filldraw(circle(Z, r), black, black);

label("$(x,\,y)$", Z+N+E);

