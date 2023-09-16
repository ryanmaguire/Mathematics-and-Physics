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
 *      Draws a commutative diagram with four vertices in a square with       *
 *      arrows drawn so that the figure commutes.                             *
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

/*  Coordinates for the labels.                                               */
pair A = (0.0, 0.0);
pair B = (2.0, 0.0);
pair C = (0.0, -2.0);
pair D = (2.0, -2.0);

/*  Margins for the arrows to prevent overlap with labels.                    */
margin margins = TrueMargin(0.3cm, 0.3cm);

/*  Draw the arrows.                                                          */
draw("$\alpha$", A -- B, N, fpen, sharp_arrow, margins);
draw("$\beta$",  B -- D, E, fpen, sharp_arrow, margins);
draw("$\gamma$", A -- C, W, fpen, sharp_arrow, margins);
draw("$\delta$", C -- D, S, fpen, sharp_arrow, margins);

/*  Label the points.                                                         */
label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);
