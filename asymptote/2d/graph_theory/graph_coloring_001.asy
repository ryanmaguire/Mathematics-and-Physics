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
pair V0 = (0.0, 0.0);
pair V1 = (1.0, 0.0);
pair V2 = (1.5, 1.0);
pair V3 = (0.2, 1.0);

/*  And draw the edges.                                                       */
draw(V0 -- V1);
draw(V0 -- V2);
draw(V0 -- V3);

/*  Dots for the vertices of the graph.                                       */
filldraw(circle(V0, 0.03), blue, black);
filldraw(circle(V1, 0.03), green, black);
filldraw(circle(V2, 0.03), red, black);
filldraw(circle(V3, 0.03), yellow, black);
