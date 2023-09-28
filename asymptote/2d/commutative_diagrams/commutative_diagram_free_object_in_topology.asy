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
 *      Commutative diagram for the free object in topology. This is the      *
 *      discrete topology. Given a set X the free topological object on X is  *
 *      the topological space (C(X), CT) and map alpha : X -> C(X) such that  *
 *      for any topological space (Y, T) and any function f: X -> Y there is  *
 *      an induced continuous function f':C(X) -> Y such that                 *
 *      f(x) = f'(alpha(x)). The space (C(X), CT) is (X, P(X)), where P(X) is *
 *      the power set of X. The map alpha is the identity. This figure        *
 *      demonstrates this idea via commutative diagram.                       *
 ******************************************************************************/

/*  Default pens and parameters for size(128) drawings provided here.         */
import "size_128_default_settings.asy" as default;

/*  Mark three points for A, B, and C.                                        */
pair A = (0.0, 0.0);
pair B = (1.0, 0.5);
pair C = (1.0, -0.5);

/*  Label for the dashed arrow. "tilde-f."                                    */
Label tf = Label("$\tilde{f}$");

/*  Draw the arrows.                                                          */
draw("$\alpha$", A -- B, NW, default.sharp_arrow, default.margins);
draw(tf, B -- C, E, default.dash_pen, default.sharp_arrow, default.margins);
draw("$f$", A -- C, SW, default.sharp_arrow, default.margins);

/*  Label the points.                                                         */
label("$X$", A);
label("$F(X)$", B);
label("$Y$", C);
