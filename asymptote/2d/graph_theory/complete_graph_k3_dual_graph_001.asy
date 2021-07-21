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

/*  Coordinates for the vertices of the graph.                                */
pair V0 = expi(0.5*pi);
pair V1 = expi(3.5*pi / 3.0);
pair V2 = expi(5.5*pi / 3.0);

/*  Two points for the dual graph.                                            */
pair A = (0.0, 0.0);
pair B = scale(1.1)*expi(pi/6.0);

/*  Size of dots used to indicate points.                                     */
real rDot = 0.03;

/*  Dots for the vertices of the graph.                                       */
dot(V0);
dot(V1);
dot(V2);

/*  Draw the edges of the graph.                                              */
draw(V0 -- V1);
draw(V1 -- V2);
draw(V2 -- V0);

/*  Draw the edges of the dual graph.                                         */
draw(A -- B);
draw(A{expi(0.833*pi)} .. B{expi(1.5*pi)});
draw(A{expi(1.5*pi)} .. B{expi(0.833*pi)});

/*  Draw in the vertices of the dual graph.                                   */
filldraw(circle(A, rDot), red, black);
filldraw(circle(B, rDot), red, black);
