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

pair A1 = (0.0, 0.0);
pair A2 = (1.0, 1.0);

pair B1 = (1.0, 0.0);
pair B2 = (0.0, 1.0);

pair C1 = (0.0, 0.7);
pair C2 = (1.0, 0.7);

draw(A1 -- A2);
draw(B1 -- B2, white+linewidth(4.0pt));
draw(B1 -- B2);
draw(C1 -- C2, white+linewidth(4.0pt));
draw(C1 -- C2);

draw(shift(1.5, 0.0)*(A1 -- A2));
draw(shift(1.5, 0.0)*(B1 -- B2), white+linewidth(4.0pt));
draw(shift(1.5, 0.0)*(B1 -- B2));
draw(shift(1.5, -0.5)*(C1 -- C2), white+linewidth(4.0pt));
draw(shift(1.5, -0.5)*(C1 -- C2));

