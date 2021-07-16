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

defaultpen(black + linewidth(0.7pt));

pair A1 = (0.0, 0.0);
pair A2 = (1.0, -0.5);
pair A3 = (2.0, 0.0);

pair B1 = (0.0, -0.5);
pair B2 = (1.0, 0.0);
pair B3 = (2.0, -0.5);

pair C0 = (0.0, 0.5);
pair C1 = (2.0, 0.5);

pair D0 = (0.0, 0.8);
pair D1 = (2.0, 0.8);

pair E1 = (0.5, -0.25);
pair E2 = (1.5, -0.25);

filldraw(A1 -- E1 -- B1 -- cycle, grey, invisible);
filldraw(A3 -- E2 -- B3 -- cycle, grey, invisible);
filldraw(E1 -- A2 -- E2 -- B2 -- cycle, grey, invisible);
draw(A1 -- A2 -- A3, white+linewidth(5.0pt));
draw(A1 -- A2 -- A3);
draw(B1 -- B2 -- B3, white+linewidth(5.0pt));
draw(B1 -- B2 -- B3);

filldraw(C0 -- C1 -- D1 -- D0 -- cycle, grey, invisible);
draw(C0 -- C1);
draw(D0 -- D1);
