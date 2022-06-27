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
margin margins = TrueMargin(0.3cm, 0.3cm);
int n;
real x;

/*  Coorindates for the curve.                                                */
pair P1 = (-4.0, -2.0);
pair P2 = (-2.0, -3.0);
pair P3 = (0.0, 0.0);
pair P4 = (2.0, 3.0);
pair P5 = (4.0, 3.9);

for (n = -40; n < 40; ++n)
{
    x = (real)n / 10.0;
    draw((x, -4.0) -- (-4.0, x), green);
    draw((4.0, x) -- (x, 4.0), green);
}

draw((4.0, 4.0) -- (4.0, 4.0));
draw((-4.3, 0.0) -- (4.3, 0.0), SharpArrows(arsize));
draw((0.0, -4.3) -- (0.0, 4.3), SharpArrows(arsize));

label("$\mathbb{R}$", (4.3, 0.3));
label("$\mathbb{R}$", (0.3, 4.3));

draw(P1{dir(-30.0)} .. P2{dir(-30.0)} ..
     P3{dir(30.0)} .. P4{dir(0.0)} ..
     P5, blue);

filldraw((1.3, 2.0) -- (1.6, 2.0) -- (1.6, 1.4) -- (1.3, 1.4) -- cycle,
         white, invisible);

label("$f$", (1.45, 1.7));
