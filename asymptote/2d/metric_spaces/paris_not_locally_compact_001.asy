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
size(256);
pen dashp = black + linewidth(0.5pt) + linetype("4 4");
pen axesp = black + linewidth(0.8pt);

int n;
int n_samples = 8;
real rDot = 0.01;

real arsize = 5bp;
pair X0 = (-1.6, 0.0);
pair X1 = (1.6, 0.0);
pair Y0 = (0.0, -1.6);
pair Y1 = (0.0, 1.6);

draw(Label("$x$", position=1.0), X0 -- X1, N, axesp, SharpArrow(arsize));
draw(Label("$y$", position=1.0), Y0 -- Y1, E, axesp, SharpArrow(arsize));

path g = (0.9, 0.4) .. (1.2, 0.0) .. (1.2, -0.3) ..
         (0.8, -0.8) .. (0.0, -1.3) .. (-1.0, -0.8) ..
         (-1.3, 0.0) .. (-0.9, 0.6) .. (0.0, 1.2) ..
         (0.5, 1.0) .. cycle;

path h = (1.0, 0.5) .. (1.3, 0.2) .. (1.3, -0.5) ..
         (1.0, -1.1) .. (0.1, -1.5) .. (-1.3, -1.0) ..
         (-1.5, 0.2) .. (-1.3, 0.8) .. (0.1, 1.3) ..
         (0.6, 1.2) .. cycle;

filldraw(h, red + opacity(0.2), black);
filldraw(g, cyan + opacity(0.5), dashp);
filldraw(circle((0.0, 0.0), 0.5), blue + opacity(0.4), dashp);

for (n = 0; n < n_samples; ++n)
    filldraw(circle(scale(0.25)*expi(pi / (n+1)), rDot), black, black);

draw(scale(0.25)*expi(pi/3) -- (0.0, 0.0) -- scale(0.25)*expi(pi/4));

draw("$\varepsilon$", (0.0, 0.0) -- scale(0.5)*expi(-0.25*pi));
label("$d(a_{m},\,a_{n})=\varepsilon$", (0.0, -1.8));
