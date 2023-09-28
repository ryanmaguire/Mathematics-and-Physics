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
 *      Draws a commutative diagram with four vertices in a square with       *
 *      arrows drawn so that the figure commutes.                             *
 ******************************************************************************/

/*  Default pens and parameters for size(128) drawings provided here.         */
import "size_128_default_settings.asy" as default;

/*  Coordinates for the labels.                                               */
pair A = (0.0, 0.0);
pair B = (1.0, 0.0);
pair C = (0.0, -1.0);
pair D = (1.0, -1.0);

/*  Draw the arrows.                                                          */
draw("$\alpha$", A -- B, N, default.sharp_arrow, default.margins);
draw("$\beta$", B -- D, E, default.sharp_arrow, default.margins);
draw("$\gamma$", A -- C, W, default.sharp_arrow, default.margins);
draw("$\delta$", C -- D, S, default.sharp_arrow, default.margins);

/*  Label the points.                                                         */
label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);
