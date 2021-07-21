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
pair V0 = scale(0.8)*expi(0.5*pi);
pair V1 = scale(0.8)*expi(3.5*pi / 3.0);
pair V2 = scale(0.8)*expi(5.5 * pi / 3.0);
pair V3 = (0.0, 0.0);

/*  Draw the faces.                                                           */
filldraw((-1, -1) -- (-1, 1) -- (1, 1) -- (1, -1) -- cycle, cyan, invisible);
filldraw(V0 -- V1 -- V2 -- cycle, blue, black);
filldraw(V0 -- V1 -- V3 -- cycle, green, black);
filldraw(V0 -- V2 -- V3 -- cycle, red, black);

/*  Dots for the vertices of the graph.                                       */
dot(V0);
dot(V1);
dot(V2);
dot(V3);
