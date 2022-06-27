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

texpreamble("\usepackage{amssymb}");

/*  Size of the output figure.                                                */
size(256);

/*  Default pen for drawing.                                                  */
defaultpen(black + linewidth(0.4pt) + fontsize(10pt));
pen thickp = black + linewidth(0.7pt) + fontsize(14pt);
real r = 0.05;
real arsize = 5bp;
int n;
int N = 100;
real start = -2.0;
real end = 2.0;
real dy = (end - start) / (real)N;
real x, y;
path g;

for (n = -40; n < 40; ++n)
{
    x = (real)n / 10.0;
    draw((x, -4.0) -- (-4.0, x), green);
    draw((4.0, x) -- (x, 4.0), green);
}

y = start;
x = y*y;
g = (x, y);
for (n = 0; n <= 100; ++n)
{
    x = y*y;
    g = g .. (x, y);
    y += dy;
}

draw(g, red);
draw((4.0, 4.0) -- (4.0, 4.0));
draw((-4.3, 0.0) -- (4.3, 0.0), thickp, SharpArrows(arsize));
draw((0.0, -4.3) -- (0.0, 4.3), thickp, SharpArrows(arsize));

label("$\mathbb{R}$", (4.3, 0.3));
label("$\mathbb{R}$", (0.3, 4.3));

filldraw((1.3, 2.0) -- (1.6, 2.0) -- (1.6, 1.4) -- (1.3, 1.4) -- cycle,
         white, invisible);

label("$g$", (1.45, 1.7));
