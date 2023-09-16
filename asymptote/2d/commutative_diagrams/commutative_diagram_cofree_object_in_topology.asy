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
 *      Draw a commutative diagram for the cofree object in topology. This is *
 *      the trivial topology, also called the chaotic topology. Given any     *
 *      set X, the cofree topological object of X is the topological space    *
 *      (C(X), CT) and map alpha:X -> C(X) such that for any topological      *
 *      space (Y, T) and any function f:Y -> X there is an induced continuous *
 *      function f':Y -> C(X) such that f'(y) = alpha(f(y)). The space that   *
 *      does this is the trivial topological space on X, the only open sets   *
 *      are the empty set and X. This figure shows this commutative diagram.  *
 ******************************************************************************/

/*  Sharp tikz style arrows provided here.                                    */
access "custom_arrows.asy" as arrows;

/*  Size of the output figure.                                                */
size(128);

/*  Default pen used for labels.                                              */
defaultpen(fontsize(10pt));

/*  Pen used to label the induced function.                                   */
pen dpen = fontsize(10pt) + linetype("4 4");

/*  Size of arrow heads.                                                      */
real arrow_size = 5bp;

/*  Arrow used for all lines.                                                 */
arrowbar sharp_arrow = arrows.SharpArrow(arrow_size);

/*  Mark three points for A, B, and C.                                        */
pair A = (0.0, 0.0);
pair B = (1.0, 0.5);
pair C = (1.0, -0.5);

/*  Margins for the arrows to prevent overlap with labels.                    */
margin margins = TrueMargin(0.5cm, 0.5cm);

/*  Draw the arrows.                                                          */
draw("$\alpha$", A -- B, NW, sharp_arrow, margins);
draw("$\tilde{f}$", C -- B, E, dpen, sharp_arrow, margins);
draw("$f$", C -- A, SW, sharp_arrow, margins);

/*  Label the points.                                                         */
label("$X$", A);
label("$C(X)$", B);
label("$Y$", C);
