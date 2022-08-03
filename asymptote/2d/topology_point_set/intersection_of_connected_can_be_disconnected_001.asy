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

import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(256);

texpreamble("\usepackage{amssymb}");

real arsize = 5bp;
pen axesp = black + linewidth(1.0pt);
path g;

draw((-3.0, 0.0) -- (3.0, 0.0), SharpArrows(arsize));
draw((0.0, -3.0) -- (0.0, 3.0), SharpArrows(arsize));

g = (1.0, -1.0){dir(90.0)} .. (0.0, -0.5){dir(180.0)} ..
    (-1.0, 0.0){dir(90.0)} .. (0.0, 0.5){dir(0.0)} ..
    (1.0, 1.0){dir(90.0)} .. (0.0, 1.5){dir(180.0)} .. 
    (-2.0, 0.0){dir(-90.0)} .. (0.0, -1.5){dir(0.0)} .. cycle;


filldraw(g, cyan + opacity(0.5), black);
filldraw(reflect((0.0, 0.0), (0.0, 1.0)) * g, red + opacity(0.5), black);

label("$\mathcal{U}$", (-2.0, 1.0));
label("$\mathcal{V}$", (2.0, 1.0));
label("$\mathbb{R}^{2}$", (2.0, 2.0));
