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

/*  Sharp tikz style arrows provided here.                                    */
access "custom_arrows.asy" as arrows;

/*  Size of the output figure.                                                */
size(256);

/*  Default pen used for labels.                                              */
defaultpen(fontsize(10pt));

/*  Pen used to label the induced function.                                   */
pen dpen = fontsize(10pt) + linetype("4 4");

/*  Size of arrow heads.                                                      */
real arrow_size = 5bp;

/*  Arrow used for all lines.                                                 */
arrowbar sharp_arrow = arrows.SharpArrow(arrow_size);

/*  Mark three points for the labels.                                         */
pair Y = (0.0, 0.0);
pair X1 = (-1.5, -1.0);
pair X2 = (1.5, -1.0);
pair X12 = (0.0, -1.0);

/*  Margins for the arrows to prevent overlap with labels.                    */
margin margins = TrueMargin(0.5cm, 0.5cm);
margin widemargins = TrueMargin(0.8cm, 0.5cm);

/*  Draw the arrows.                                                          */
draw("$f_{1}$", Y -- X1, NW, sharp_arrow, margins);
draw("$f_{2}$", Y -- X2, NE, sharp_arrow, margins);
draw("$f$", Y -- X12, W, sharp_arrow, margins);
draw("$\pi_{1}$", X12 -- X1, S, sharp_arrow, widemargins);
draw("$\pi_{2}$", X12 -- X2, S, sharp_arrow, widemargins);

/*  Label the points.                                                         */
label("$X_{1}$", X1);
label("$X_{2}$", X2);
label("$Y$", Y);
label("$X_{1}\times{X}_{2}$", X12);
