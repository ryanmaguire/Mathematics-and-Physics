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
 *      Draw a commutative diagram showing associativity of composition.      *
 ******************************************************************************/

/*  Default pens and parameters for size(256) drawings provided here.         */
import "size_256_default_settings.asy" as default;

/*  Four points for the vertices of the commutative diagram.                  */
pair A = (-3.0, 0.000);
pair B = (+0.0, 5.196);
pair C = (+3.0, 0.000);
pair D = (+0.0, 1.732);

/*  Label the points.                                                         */
label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);

/*  Labels for the three rotated arrows. These are the function compositions. */
Label h = rotate(-30)*Label("$h$");
Label hg = rotate(-90)*Label("$h\circ{g}$");
Label hgf = rotate(30)*Label("$h\circ{g}\circ{f}$");

/*  Draw arrows between the points.                                           */
draw("$f$", A -- B, NW, default.sharp_arrow, default.margins);
draw("$g$", B -- C, NE, default.sharp_arrow, default.margins);
draw("$g\circ{f}$", A -- C, default.sharp_arrow, default.margins);
draw(h, C -- D, SW, default.sharp_arrow, default.margins);
draw(hg, B -- D, E, default.sharp_arrow, default.margins);
draw(hgf, A -- D, default.sharp_arrow, default.margins);
