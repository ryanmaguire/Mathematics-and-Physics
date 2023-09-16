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
 *      Draws a commutative diagram with 4 vertices, three in 1 column on the *
 *      left and 1 by itself on the right, with arrows connecting to form     *
 *      two triangular regions. This is used in various lecture notes.        *
 ******************************************************************************/

/*  Sharp tikz style arrows provided here.                                    */
access "custom_arrows.asy" as arrows;

/*  Size of the output figure.                                                */
size(128);

/*  Default pen used for labels.                                              */
defaultpen(fontsize(9pt));

/*  Pen used to label functions.                                              */
pen fpen = fontsize(7pt);

/*  Size of arrow heads.                                                      */
real arrow_size = 5bp;

/*  Arrow used for all lines.                                                 */
arrowbar sharp_arrow = arrows.SharpArrow(arrow_size);

/*  Mark coordinates for the points.                                          */
real height = -0.7;
real width = 0.9;
pair A = (0.0, 0.0);
pair B = (0.0, -height);
pair C = (0.0, -2.0*height);
pair D = (width, -height);

/*  Margins for the arrows to prevent overlap with labels.                    */
margin margins = TrueMargin(0.4cm, 0.4cm);

/*  Draw the arrows.                                                          */
draw("$f_{1}$", A -- D, SE, fpen, sharp_arrow, margins);
draw("$f_{2}$", B -- D, S, fpen, sharp_arrow, margins);
draw("$f_{3}$", C -- D, NE, fpen, sharp_arrow, margins);
draw("$g_{1}$", A -- B, W, fpen, sharp_arrow, margins);
draw("$g_{2}$", B -- C, W, fpen, sharp_arrow, margins);

/*  Label the points.                                                         */
label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);
