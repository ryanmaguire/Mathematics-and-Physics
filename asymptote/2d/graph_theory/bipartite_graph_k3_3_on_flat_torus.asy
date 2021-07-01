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
pair[] A = {(-1.0, -0.5), (0.0, -0.5), (1.0, -0.5)};
pair[] B = {(-1.0, 0.5), (0.0, 0.5), (1.0, 0.5)};

/*  Radius of the dots.                                                       */
real radius = 0.02;

/*  Value for the edge of the square.                                         */
real edge = 1.5;

/*  Pairs for the square representing the torus.                              */
pair V0 = (-edge, -edge);
pair V1 = (edge, -edge);
pair V2 = (-edge, edge);
pair V3 = (edge, edge);

/*  Dots for the vertices of the graph.                                       */
filldraw(circle(A[0], radius), black);
filldraw(circle(A[1], radius), black);
filldraw(circle(A[2], radius), black);
filldraw(circle(B[0], radius), black);
filldraw(circle(B[1], radius), black);
filldraw(circle(B[2], radius), black);

/*  And draw the edges.                                                       */
draw(A[0] -- B[0]);
draw(A[0] -- B[1]);
draw(A[1] -- B[1]);
draw(A[1] -- B[2]);
draw(A[2] -- B[2]);

/*  Some of the edges need to curve around the torus.                         */
draw(A[0] -- (-edge, 0.0));
draw((edge, 0.0) -- B[2]);

draw(A[2] -- (0.0, -edge));
draw((0.0, edge) -- B[0]);

draw(B[0] -- (-0.5, edge));
draw((-0.5, -edge) -- A[1]);

draw(A[2] -- (0.5, -edge));
draw((0.5, edge) -- B[1]);

/*  Draw in lines to indicate the square.                                     */
draw(V0 -- V1, blue + linewidth(1.0));
draw(V2 -- V3, blue + linewidth(1.0));
draw(V0 -- V2, red + linewidth(1.0));
draw(V1 -- V3, red + linewidth(1.0));
