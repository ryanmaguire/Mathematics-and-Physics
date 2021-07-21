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

/*  Size of the output figure.                                                */
size(128);

/*  Default pen for drawing figures.                                          */
defaultpen(black + linewidth(0.5pt) + fontsize(7pt));

/*  Radius used for the two circles in Euclid's construction.                 */
real radius = 2.0;

/*  Radius of a dot used to mark a point.                                     */
real dotr = 0.05;

/*  Location of the 3 points for Euclid's construction.                       */
pair A = (0, 0.0);
pair B = (radius, 0.0);
pair C = scale(radius)*expi(0.333*pi);

/*  Draw the two circles in Euclid's construction.                            */
draw(circle(A, radius));
draw(circle(B, radius));

/*  Fill in the equilateral triangle.                                         */
filldraw(A -- B -- C -- cycle, green);

/*  Mark and label all of the points.                                         */
filldraw(circle(A, dotr), black);
filldraw(circle(B, dotr), black);
filldraw(circle(C, dotr), black);
label("$A$", A, SW);
label("$B$", B, SE);
label("$C$", C, N);
