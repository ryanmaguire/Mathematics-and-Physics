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
 *      Basic commutative diagram featuring 3 vertices in a triangle. This is *
 *      used for projections and one of the maps is labeled "pi".             *
 ******************************************************************************/

/*  Default pens and parameters for size(64) drawings provided here.          */
import "size_64_default_settings.asy" as default;

/*  Coordinates for labels.                                                   */
pair A = (0.0, 0.0);
pair B = (1.0, 0.0);
pair C = (0.0, -1.0);

/*  Draw the arrows.                                                          */
draw("$f$", A -- B, N, default.sharp_arrow, default.small_margins);
draw("$\pi$", A -- C, W, default.sharp_arrow, default.small_margins);
draw("$\tilde{f}$", C -- B, SE, default.sharp_arrow, default.small_margins);

/*  Add labels.                                                               */
label("$A$", A);
label("$B$", B);
label("$C$", C);
