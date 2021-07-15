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

pair V0 = scale(0.5)*expi(0.5*pi);
pair V1 = scale(0.5)*expi(3.5*pi / 3.0);
pair V2 = scale(0.5)*expi(5.5 * pi / 3.0);

pair W0 = expi(0.333*pi + pi / 6.0);
pair W1 = expi(0.666*pi + pi / 6.0);
pair W2 = expi(1.0*pi + pi / 6.0);
pair W3 = expi(1.333*pi + pi / 6.0);
pair W4 = expi(1.666*pi + pi / 6.0);
pair W5 = expi(pi / 6.0);

real rDot = 0.03;

draw(V0 -- V1 -- V2 -- cycle);
draw(W0 -- W1 -- W2 -- W3 -- W4 -- W5 -- cycle);

draw(V0 -- W0);
draw(V0 -- W1);
draw(V0 -- W5);

draw(V1 -- W1);
draw(V1 -- W2);
draw(V1 -- W3);

draw(V2 -- W3);
draw(V2 -- W4);
draw(V2 -- W5);

filldraw(circle(V0, rDot), red, black);
filldraw(circle(V1, rDot), yellow, black);
filldraw(circle(V2, rDot), blue, black);
filldraw(circle(W0, rDot), yellow, black);
filldraw(circle(W1, rDot), blue, black);
filldraw(circle(W2, rDot), red, black);
filldraw(circle(W3, rDot), green, black);
filldraw(circle(W4, rDot), yellow, black);
filldraw(circle(W5, rDot), green, black);