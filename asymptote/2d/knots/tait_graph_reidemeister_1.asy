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

real arsize = 5bp;

pair A0 = (1.0, -0.5);
pair A1 = (1.0, -1.0);

pair B0 = (0.7, -1.0);
pair B1 = (1.0, -0.8);
pair B2 = (1.2, -0.5);
pair B3 = (1.0, -0.2);
pair B4 = (0.8, -0.5);
pair B5 = (1.3, -1.0);

pair C0 = (2.0, -0.75);

pair D0 = (1.3, -0.75);
pair D1 = (1.6, -0.75);

draw(B0 .. B1 .. B2 .. B3{W});
filldraw(circle(B1, 0.02), white, white);
draw(B3{W} .. B4 .. B1 .. B5, black);
draw(A0 -- A1);
draw(D0 -- D1, SharpArrow(arsize));

filldraw(circle(A0, 0.05), grey, black);
filldraw(circle(A1, 0.05), grey, black);
filldraw(circle(C0, 0.05), grey, black);
