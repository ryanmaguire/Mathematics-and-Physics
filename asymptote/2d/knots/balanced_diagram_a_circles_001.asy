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
size(128);

path A = (-1.2, 0.0) .. (-1.3, 0.3) .. (0.0, 1.5) .. (1.3, 0.3) .. (1.2, 0.0) ..
         (1.3, -0.3) .. (0.0, -1.5) .. (-1.3, -0.3) .. cycle;

path B = (-1.1, 0.0) .. (-0.6, 0.7) .. (-0.4, 0.5) .. (0.0, 0.7) ..
         (0.4, 0.5) .. (0.6, 0.7) .. (1.1, 0.0) .. (0.6, -0.7) ..
         (0.4, -0.5) .. (0.0, -0.7) .. (-0.4, -0.5) .. (-0.6, -0.7) .. cycle;
path C = (1.7, 0.0) .. (1.5, 1.1) .. (2.2, 0.0) .. (1.5, -1.1) .. cycle;

draw(A, cyan);
draw(B, red);
draw(C, green);
draw(ellipse((-0.35, 0.0), 0.2, 0.3), orange);
draw(ellipse((0.35, 0.0), 0.2, 0.3), blue);

