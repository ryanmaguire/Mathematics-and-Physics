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
 *      Shows a commutative diagram depicting the product of topological      *
 *      spaces. This is the "categorical" definition of topological product.  *
 ******************************************************************************/

/*  Default pens and parameters for size(256) drawings provided here.         */
import "size_256_default_settings.asy" as default;

/*  Mark three points for the labels.                                         */
pair Y = (0.0, 0.0);
pair X1 = (-1.5, -1.0);
pair X2 = (1.5, -1.0);
pair X12 = (0.0, -1.0);

/*  Custom margins for the center label, which is wider than the others.      */
margin widemargins = TrueMargin(0.9cm, 0.5cm);

/*  Draw the arrows.                                                          */
draw("$f_{1}$", Y -- X1, NW, default.sharp_arrow, default.margins);
draw("$f_{2}$", Y -- X2, NE, default.sharp_arrow, default.margins);
draw("$f$", Y -- X12, W, default.sharp_arrow, default.margins);
draw("$\pi_{1}$", X12 -- X1, S, default.sharp_arrow, widemargins);
draw("$\pi_{2}$", X12 -- X2, S, default.sharp_arrow, widemargins);

/*  Label the points.                                                         */
label("$X_{1}$", X1);
label("$X_{2}$", X2);
label("$Y$", Y);
label("$X_{1}\times{X}_{2}$", X12);
