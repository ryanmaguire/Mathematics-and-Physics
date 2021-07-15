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

real rDot = 0.04;

pair V0 = scale(0.5)*expi(0.25*pi);
pair V1 = scale(0.5)*expi(0.75*pi);
pair V2 = scale(0.5)*expi(1.25*pi);
pair V3 = scale(0.5)*expi(1.75*pi);

pair W0 = expi(0.0*pi);
pair W1 = expi(0.5*pi);
pair W2 = expi(1.0*pi);
pair W3 = expi(1.5*pi);

pair Z0 = scale(2.0)*expi(0.25*pi);
pair Z1 = scale(2.0)*expi(0.75*pi);
pair Z2 = scale(2.0)*expi(1.25*pi);
pair Z3 = scale(2.0)*expi(1.75*pi);

draw(V0 -- V1 -- V2 -- V3 -- cycle);
draw(W0 -- W1 -- W2 -- W3 -- cycle);
draw(Z0 -- Z1 -- Z2 -- Z3 -- cycle);

draw(V0 -- W0);
draw(V0 -- W1);

draw(V1 -- W1);
draw(V1 -- W2);

draw(V2 -- W2);
draw(V2 -- W3);

draw(V3 -- W3);
draw(V3 -- W0);

draw(W0 -- Z3);
draw(W0 -- Z0);

draw(W1 -- Z0);
draw(W1 -- Z1);

draw(W2 -- Z1);
draw(W2 -- Z2);

draw(W3 -- Z2);
draw(W3 -- Z3);

filldraw(circle(V0, rDot), white, black);
filldraw(circle(V1, rDot), white, black);
filldraw(circle(V2, rDot), white, black);
filldraw(circle(V3, rDot), white, black);

filldraw(circle(W0, rDot), white, black);
filldraw(circle(W1, rDot), white, black);
filldraw(circle(W2, rDot), white, black);
filldraw(circle(W3, rDot), white, black);

filldraw(circle(Z0, rDot), white, black);
filldraw(circle(Z1, rDot), white, black);
filldraw(circle(Z2, rDot), white, black);
filldraw(circle(Z3, rDot), white, black);
