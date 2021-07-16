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

/*  Size of the figure.                                                       */
size(128);

pair A = (0.0, 0.0);
pair B = (0.9, 0.0);
real r = 0.5;
real arsize = 5bp;
real rDot = 0.05;

draw(arc(A, r, 0, 270), Arrow(arsize, position=0.6), Arrow(arsize, position=2.5));
draw(circle(B, r), white + linewidth(5pt));
draw(circle(B, r), Arrow(arsize, position=0.2), Arrow(arsize, position=2.1));
draw(arc(A, r, 270, 360), white + linewidth(5pt));
draw(arc(A, r, 180, 380));

filldraw(circle(A, rDot), grey, black);
filldraw(circle(B, rDot), grey, black);
