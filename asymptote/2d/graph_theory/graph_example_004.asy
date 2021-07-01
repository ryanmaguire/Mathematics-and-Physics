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
pair V1 = (0.33, 0.0);
pair V2 = (0.33, 0.75);
pair V3 = (0.33, -0.75);
pair V4 = (0.66, 0.0);
pair V5 = (0.66, -0.75);
pair V6 = (1.0, 0.0);
pair V7 = (1.0, 1.0);
pair V8 = (1.0, -1.0);
pair V9 = (1.33, 0.0);
pair V10 = (1.33, 0.75);
pair V11 = (1.33, -0.45);
pair V12 = (1.33, -0.75);
pair V13 = (1.75, -0.45);
pair V14 = (1.66, 0.0);
pair V15 = (1.66, 0.5);
pair V16 = (2.0, 0.0);

/*  Dots for the vertices of the graph.                                       */
dot(V0);
dot(V1);
dot(V2);
dot(V3);
dot(V4);
dot(V5);
dot(V6);
dot(V7);
dot(V8);
dot(V9);
dot(V10);
dot(V11);
dot(V12);
dot(V13);
dot(V14);
dot(V15);
dot(V16);

/*  And draw the edges.                                                       */
draw(V0 -- V1);
draw(V1 -- V2);
draw(V1 -- V3);
draw(V1 -- V4);
draw(V4 -- V5);
draw(V4 -- V6);
draw(V6 -- V7);
draw(V6 -- V8);
draw(V6 -- V9);
draw(V9 -- V10);
draw(V9 -- V11);
draw(V11 -- V12);
draw(V11 -- V13);
draw(V9 -- V14);
draw(V14 -- V15);
draw(V14 -- V16);
