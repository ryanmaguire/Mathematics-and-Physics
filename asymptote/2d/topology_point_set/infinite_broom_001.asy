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

int n;
int n_lines = 140;
pair O = (0.0, 0.0);
pen thinp = black + linewidth(0.4pt);
pen redp = red + linewidth(1.0pt);
real rDot = 0.01;

for (n = 0; n < n_lines; ++n)
{
    pair A = (1.0, 1.0 / (n + 1.0));
    draw(O -- A, thinp);
}

draw((0.5, 0.0) -- (1.0, 0.0), redp);
filldraw(circle((1.0, 0.0), rDot), redp, black);
