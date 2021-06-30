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
pair A = (0.0, 0.0);
pair B0 = (1.0, 1.0);
pair B1 = (-1.0, 1.0);
pair C00 = (1.5, 2.0);
pair C01 = (0.5, 2.0);
pair C10 = (-1.5, 2.0);
pair C11 = (-0.5, 2.0);
pair D000 = (1.75, 3.0);
pair D001 = (1.25, 3.0);
pair D010 = (0.75, 3.0);
pair D011 = (0.25, 3.0);
pair D100 = (-1.75, 3.0);
pair D101 = (-1.25, 3.0);
pair D110 = (-0.75, 3.0);
pair D111 = (-0.25, 3.0);

/*  Dots for the vertices of the graph.                                       */
dot(A);
dot(B0);
dot(B1);
dot(C00);
dot(C01);
dot(C10);
dot(C11);
dot(D000);
dot(D001);
dot(D010);
dot(D011);
dot(D100);
dot(D101);
dot(D110);
dot(D111);

/*  And draw the edges.                                                       */
draw(A -- B0);
draw(A -- B1);
draw(B0 -- C00);
draw(B0 -- C01);
draw(B1 -- C10);
draw(B1 -- C11);
draw(C00 -- D000);
draw(C00 -- D001);
draw(C01 -- D010);
draw(C01 -- D011);
draw(C10 -- D100);
draw(C10 -- D101);
draw(C11 -- D110);
draw(C11 -- D111);
