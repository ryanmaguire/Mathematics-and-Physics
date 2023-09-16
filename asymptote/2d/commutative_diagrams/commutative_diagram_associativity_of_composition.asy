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

/*  Sharp tikz style arrows provided here.                                    */
access "custom_arrows.asy" as arrows;

/*  Size of the figure.                                                       */
size(256);

/*  Default pen for labels and drawings.                                      */
defaultpen(black + fontsize(10pt) + linewidth(0.7pt));

/*  Pen for labels.                                                           */
pen label_pen = fontsize(12pt);

/*  Four points for the vertices of the commutative diagram.                  */
pair A = (-3.0, 0.000);
pair B = (+0.0, 5.196);
pair C = (+3.0, 0.000);
pair D = (+0.0, 1.732);

/*  Size of arrow heads.                                                      */
real arrow_size = 5bp;

/*  Arrow used for all lines.                                                 */
arrowbar sharp_arrow = arrows.SharpArrow(arrow_size);

/*  Label the points.                                                         */
label("$A$", A, label_pen);
label("$B$", B, label_pen);
label("$C$", C, label_pen);
label("$D$", D, label_pen);

/*  Margins to prevent lines from overlapping with labels.                    */
margin margins = TrueMargin(0.3cm, 0.3cm);

/*  Draw arrows between the points.                                           */
draw("$f$", A -- B, NW, sharp_arrow, margins);
draw("$g$", B -- C, NE, sharp_arrow, margins);
draw("$g\circ{f}$", A -- C, sharp_arrow, margins);
draw(rotate(-30)*"$h$", C -- D, SW, sharp_arrow, margins);
draw(rotate(-90)*"$h\circ{g}$", B -- D, E, sharp_arrow, margins);
draw(rotate(30)*"$h\circ{g}\circ{f}$", A -- D, sharp_arrow, margins);
