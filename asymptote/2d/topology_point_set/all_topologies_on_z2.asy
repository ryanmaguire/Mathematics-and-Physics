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
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Draws the intersection of a plane with a cube, revealing a hexagon.   *
 *      This is what you'd get if you dipped a cube into water with one of    *
 *      vertices of the cube facing down.                                     *
 ******************************************************************************/

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(256);

defaultpen(black + linewidth(0.7pt) + fontsize(12pt));

texpreamble("\usepackage{amssymb}");

pair O = (0.0, 0.0);
pair A = (-0.4, 0.0);
pair B = (0.4, 0.0);
pair C = (0.0, 0.5);
pair D = (-0.6, 0.4);
pair dx = (0.1, 0.0);
real rx = 1.2;
real ry = 0.8;
real rxall = 0.65;
real ryall = 0.35;
real rempty = 0.1;
real rxone = 0.2;
real ryone = 0.15;
transform T;

draw(ellipse(O, rx, ry));
draw(ellipse(O, rxall, ryall));
dot(A);
dot(B);
draw(circle(D, rempty));
label("$0$", A, E);
label("$1$", B, W);
label("$\mathbb{Z}_{2}$", C);

T = shift(2.5, 0.0);

draw(ellipse(T*O, rx, ry));
dot(T*A);
dot(T*B);
draw(ellipse(T*O, rxall, ryall));
draw(circle(T*D, rempty));
draw(ellipse(T*A + dx, rxone, ryone));
label("$0$", T*A, E);
label("$1$", T*B, W);
label("$\mathbb{Z}_{2}$", T*C);

T = shift(0.0, -2.0);

draw(ellipse(T*O, rx, ry));
dot(T*A);
dot(T*B);
draw(ellipse(T*O, rxall, ryall));
draw(circle(T*D, rempty));
draw(ellipse(T*B - dx, rxone, ryone));
label("$0$", T*A, E);
label("$1$", T*B, W);
label("$\mathbb{Z}_{2}$", T*C);

T = shift(2.5, -2.0);

draw(ellipse(T*O, rx, ry));
dot(T*A);
dot(T*B);
draw(ellipse(T*O, rxall, ryall));
draw(circle(T*D, rempty));
draw(ellipse(T*A + dx, rxone, ryone));
draw(ellipse(T*B - dx, rxone, ryone));
label("$0$", T*A, E);
label("$1$", T*B, W);
label("$\mathbb{Z}_{2}$", T*C);
