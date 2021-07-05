/******************************************************************************
 *                                 LICENSE                                    *
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

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Size of the figure.                                                       */
size(128);

/*  Default pen for labels and drawings.                                      */
defaultpen(black + fontsize(7pt) + linewidth(0.7pt));

/*  Four points for the vertices of the commutative diagram.                  */
pair A = (-3.0, 0.0);
pair B = (0.0, 5.196);
pair C = (3.0, 0.0);
pair D = (0.0, 1.732);

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  Label the points.                                                         */
label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);

/*  Margins to prevent lines from overlapping with labels.                    */
margin margins = TrueMargin(0.3cm, 0.3cm);

/*  Draw arrows between the points.                                           */
draw("$f$", A -- B, NW, SharpArrow(arsize), margins);
draw("$g$", B -- C, NE, SharpArrow(arsize), margins);
draw("$g\circ{f}$", A -- C, SharpArrow(arsize), margins);
draw(rotate(-30)*"$h$", C -- D, SW, SharpArrow(arsize), margins);
draw(rotate(-90)*"$h\circ{g}$", B -- D, E, SharpArrow(arsize), margins);
draw(rotate(30)*"$h\circ{g}\circ{f}$", A -- D, SharpArrow(arsize), margins);
