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

/*  Default pens and parameters for size(256) drawings provided here.         */
import "size_256_default_settings.asy" as default;

real r = 1.0;

pair A = (0.0, 0.0);
pair B = (2.9*r, 0.0);
pair C = (4.7*r, -1.0*r);
pair D = (2.9*r, -2.5*r);
pair E = (0.0, -2.5*r);

path g = (0.0, r) .. (0.6*r, 0.0) .. (0.0, -r) .. (-0.6*r, 0.0) ..
         (0.0, r) .. (0.2*r, 1.1*r) .. (0.0, -1.2*r) ..
         (-0.2*r, 1.1*r) .. cycle;

draw(reverse(circle(B, r)), default.mid_sharp_arrow);
draw(circle(D, r), default.mid_sharp_arrow);
draw(circle(C + (r, 0.0), 0.7*r), default.mid_sharp_arrow);
draw(g, default.mid_sharp_arrow);
draw(shift(E)*reverse(g), default.mid_sharp_arrow);

filldraw(circle(A, default.dot_radius));
filldraw(circle(B, default.dot_radius));
filldraw(circle(C, default.dot_radius));
filldraw(circle(D, default.dot_radius));
filldraw(circle(E, default.dot_radius));

label("$-2$", A, 2.0*SW);
label("$-1$", B, 2.0*SW);
label("$0$", C, 2.0*SW);
label("$1$", D, 2.0*SW);
label("$2$", E, 2.0*SW);
