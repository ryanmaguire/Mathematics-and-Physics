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

pair A0, A1;
pair B0, B1, B2;
transform T;
A0 = (0.0, 0.0);
A1 = (1.0, 0.0);

dot(A0);
dot(A1);
draw(A0 -- A1);

T = shift(1.6, -0.2);
A0 = T*(0.1, 0.4);
A1 = T*(0.9, 0.4);
B0 = T*(0.1, 0.3);
B1 = T*(0.5, 0.0);
B2 = T*(0.9, 0.3);

dot(A0);
dot(A1);
draw(A0 .. B0 .. B1 .. B2 .. A1);

T = shift(0.0, -1.2);
A0 = T*(0.25, 0.6);
A1 = T*(0.75, 0.6);
B0 = T*(0.1, 0.3);
B1 = T*(0.5, 0.0);
B2 = T*(0.9, 0.3);

dot(A0);
dot(A1);
draw(A0 .. B0 .. B1 .. B2 .. A1);

T = shift(1.6, -1.2);
A0 = T*(0.5, 0.7);
A1 = T*(0.5, 0.7);
B0 = T*(0.15, 0.35);
B1 = T*(0.5, 0.0);
B2 = T*(0.85, 0.35);

dot(A0);
dot(A1);
draw(A0 .. B0 .. B1 .. B2 .. A1);
