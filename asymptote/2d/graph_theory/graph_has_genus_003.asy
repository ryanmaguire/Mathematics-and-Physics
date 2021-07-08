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
pair[] A = {(-1.0, 1.0), (0.0, 0.0), (1.0, -1.0)};
pair[] B = {(1.0, 1.0), (-1.0, -1.0)};

/*  Radius of the dots.                                                       */
real radius = 0.05;

/*  Draw the edges.                                                           */
draw(A[0] -- B[0]);
draw(A[0] -- B[1]);
draw(A[1] -- B[0]);
draw(A[1] -- B[1]);
draw(A[2] -- B[0]);
draw(A[2] -- B[1]);

/*  Dots for the vertices of the graph.                                       */
filldraw(circle(A[0], radius), blue, black);
filldraw(circle(A[1], radius), blue, black);
filldraw(circle(A[2], radius), blue, black);
filldraw(circle(B[0], radius), red, black);
filldraw(circle(B[1], radius), red, black);
