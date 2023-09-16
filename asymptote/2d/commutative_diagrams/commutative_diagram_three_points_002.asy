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

/*  Sharp tikz style arrows provided here.                                    */
access "custom_arrows.asy" as arrows;

/*  Size of the output figure.                                                */
size(64);

/*  Default pen used for labels.                                              */
defaultpen(fontsize(9pt));

/*  Pen used to label functions.                                              */
pen fpen = fontsize(7pt);

/*  Size of arrow heads.                                                      */
real arrow_size = 5bp;

/*  Arrow used for all lines.                                                 */
arrowbar sharp_arrow = arrows.SharpArrow(arrow_size);

/*  Coordinates for labels.                                                   */
pair A = (0.0, 0.0);
pair B = (1.0, 0.0);
pair C = (0.0, -1.0);

/*  Margins for the arrows to prevent overlap with labels.                    */
margin margins = TrueMargin(0.3cm, 0.3cm);

/*  Draw the arrows.                                                          */
draw("$f$", A -- B, N, fpen, sharp_arrow, margins);
draw("$\pi$", A -- C, W, fpen, sharp_arrow, margins);
draw("$\tilde{f}$", C -- B, SE, fpen, sharp_arrow, margins);

/*  Add labels.                                                               */
label("$A$", A);
label("$B$", B);
label("$C$", C);
