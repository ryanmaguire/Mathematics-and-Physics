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

real rDot = 0.03;

/*  Coordinates for the vertices of the graph.                                */
pair V0 = expi(0.5*pi);
pair V1 = expi(3.5*pi / 3.0);
pair V2 = expi(5.5 * pi / 3.0);
pair V3 = (0.0, 0.0);

pair W1 = scale(0.33)*expi(pi/3.0 + 0.5*pi);
pair W2 = scale(0.33)*expi(pi/3.0 + 3.5*pi / 3.0);
pair W3 = scale(0.33)*expi(pi/3.0 + 5.5 * pi / 3.0);
pair W0 = (2.0, 0.0);

/*  Dots for the vertices of the graph.                                       */
dot(V0);
dot(V1);
dot(V2);
dot(V3);

/*  And draw the edges.                                                       */
draw(V0 -- V1);
draw(V0 -- V2);
draw(V0 -- V3);
draw(V1 -- V2);
draw(V1 -- V3);
draw(V2 -- V3);

draw(W1{NW} .. W0{S});
draw(W2{W2} .. W0{N});
draw(W3{W3} .. W0);
draw(W1 -- W2);
draw(W1 -- W3);
draw(W2 -- W3);

filldraw(circle(W0, rDot), red, black);
filldraw(circle(W1, rDot), red, black);
filldraw(circle(W2, rDot), red, black);
filldraw(circle(W3, rDot), red, black);
