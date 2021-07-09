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

/*  Value for the edge of the square.                                         */
real edge = 1.5;

/*  Coordinates for the link.                                                 */
pair A0 = (0.0, edge);
pair A1 = (0.0, -edge);

pair B0 = (-edge, 0.0);
pair B1 = (edge, 0.0);

/*  Pairs for the square representing the torus.                              */
pair V0 = (-edge, -edge);
pair V1 = (edge, -edge);
pair V2 = (-edge, edge);
pair V3 = (edge, edge);

/*  Draw in the link.                                                         */
draw(A0 -- A1);
draw(B0 -- B1, white + linewidth(4.0pt));
draw(B0 -- B1);

/*  Draw in lines to indicate the square.                                     */
draw(V0 -- V1, blue + linewidth(1.0));
draw(V2 -- V3, blue + linewidth(1.0));
draw(V0 -- V2, red + linewidth(1.0));
draw(V1 -- V3, red + linewidth(1.0));
