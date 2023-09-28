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
 *      Visual representing complex conjugate and modulus.                    *
 ******************************************************************************/

/*  Function for plotting the x and y axes.                                   */
import "coordinate_axes.asy" as axes;

/*  Basic complex number struct provided here.                                */
import "complex.asy" as complex;

/*  Default pens and parameters for size(256) drawings provided here.         */
import "size_256_default_settings.asy" as default;

/*  Needed to use the "mathbb" font in LaTeX.                                 */
texpreamble("\usepackage{amssymb}");

/*  A point for the origin and where the label for the plane will be.         */
pair O = (0.0, 0.0);
pair C = (2.0, 2.0);

/*  Start and end parameters for the coordinate axes.                         */
pair start = (-0.5, -2.2);
pair end = (4.4, 2.2);

/*  The complex number under consideration, and it's conjugate.               */
complex.Complex Z = complex.Complex(3.6, 1.6);
complex.Complex ZBar = Z.Conjugate();

/*  The label for the modulus is placed half-way up the line to Z.            */
complex.Complex HalfZ = 0.5*Z;

/*  Draw the coordinate axes, but label them with complex number notation.    */
axes.DrawAndLabelCoordinateAxesWithTickMarks(start, end,
                                             y_suffix = "i",
                                             x_string = "\Re(z)",
                                             y_string = "\Im(z)");

/*  Draw lines representing the point Z and it's conjugate.                   */
draw(O -- Z.AsPair());
draw(O -- ZBar.AsPair());

/*  Draw dashed lines representating the projections of Z and Z bar.          */
draw(Z.AsPair() -- Z.RealProjection().AsPair(), default.thin_dash_pen);
draw(ZBar.AsPair() -- ZBar.RealProjection().AsPair(), default.thin_dash_pen);
draw(Z.AsPair() -- Z.ImagProjection().AsPair(), default.thin_dash_pen);
draw(ZBar.AsPair() -- ZBar.ImagProjection().AsPair(), default.thin_dash_pen);

/*  Add filled in circles to mark the two points, Z and Z bar.                */
filldraw(circle(Z.AsPair(), default.dot_radius));
filldraw(circle(ZBar.AsPair(), default.dot_radius));

/*  Label Z, Z bar, the modulus |z|, and the complex plane C.                 */
label("$z=(x,\,y)$", Z.AsPair(), N);
label("$\bar{z}=(x,\,-y)$", ZBar.AsPair(), S);
label("$|z|$", HalfZ.AsPair(), N);
label("$\mathbb{C}$", C);
