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
pair mid = scale(0.5) * (A + B);
real r = 0.5;
real rDot = 0.03;

real y = sqrt(r*r - mid.x*mid.x);

pair C = mid + (0.0, y);
pair D = mid - (0.0, y);

draw(circle(A, r));
draw(circle(B, r));

filldraw(circle(C, rDot), red, black);
filldraw(circle(D, rDot), red, black);
