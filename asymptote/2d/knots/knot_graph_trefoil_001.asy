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

import custom_arrows;

/*  Size of the figure.                                                       */
size(128);

real r = 0.5;
real rDot = 0.03;

pair A0 = expi(1.167*pi);
pair B0 = expi(1.833*pi);
pair C0 = expi(0.5*pi);

pair A1 = scale(r)*(rotate(60)*A0);
pair B1 = scale(r)*(rotate(60)*B0);
pair C1 = scale(r)*(rotate(60)*C0);

real arsize = 5bp;

path g = A0 .. A1 .. B1 .. C0{W} .. C1 .. A1 .. B0 ..B1 .. C1 .. cycle;

draw(g);

filldraw(circle(A1, rDot), blue, black);
filldraw(circle(B1, rDot), blue, black);
filldraw(circle(C1, rDot), blue, black);
