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
 *      is used often in notes and lectures in this project.                  *
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

/*  Mark three points for A, B, and C.                                        */
pair A = (0.0, 0.0);
pair B = (0.0, -1.0);
pair C = (1.0, 0.0);

/*  Margins for the arrows to prevent overlap with labels.                    */
margin margins = TrueMargin(0.3cm, 0.3cm);

/*  Draw the arrows.                                                          */
draw("$f$", A -- B, W, fpen, sharp_arrow, margins);
draw("$g$", B -- C, SE, fpen, sharp_arrow, margins);
draw("$h$", A -- C, N, fpen, sharp_arrow, margins);

/*  Label the points.                                                         */
label("$A$", A);
label("$B$", B);
label("$C$", C);
