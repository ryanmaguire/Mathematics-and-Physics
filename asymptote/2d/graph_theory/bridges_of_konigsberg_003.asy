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

/*  Locations of the 4 vertices.                                              */
pair A = (0.0, 0.0);
pair B = (1.0, 1.0);
pair C = (2.0, 0.0);
pair D = (1.0, -1.0);

/*  Draw the straight-line edges.                                             */
draw(A -- B -- C -- D -- cycle);
draw(A -- C);

/*  Draw the edges that make a multi-graph.                                   */
draw(A{N} .. B{E});
draw(A{S} .. D{E});

/*  Draw the vertices.                                                        */
dot(A);
dot(B);
dot(C);
dot(D);

/*  Label the degrees of the vertices.                                        */
label("$5$", A, NW);
label("$3$", B, NW);
label("$3$", C, NE);
label("$3$", D, SW);
