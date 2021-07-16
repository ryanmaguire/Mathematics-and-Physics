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

pair D1 = (0.3, 0.7);
pair D2 = (0.7, 0.7);
pair D3 = (0.5, 0.5);

filldraw(D1 -- D2 -- D3 -- cycle, grey, invisible);
filldraw(B2 -- D1 -- C1 -- cycle, grey, invisible);
filldraw(A2 -- D2 -- C2 -- cycle, grey, invisible);
filldraw(A1 -- D3 -- B1 -- cycle, grey, invisible);

draw(A1 -- A2, white+linewidth(4.0pt));

draw(A1 -- A2);
draw(B1 -- B2, white+linewidth(4.0pt));
draw(B1 -- B2);
draw(C1 -- C2, white+linewidth(4.0pt));
draw(C1 -- C2);

D1 = shift(-0.1, -0.5)*D1;
D2 = shift(0.1, -0.5)*D2;
C1 = shift(0.0, -0.5)*C1;
C2 = shift(0.0, -0.5)*C2;

filldraw(shift(1.5, 0.0)*(A1 -- D1 -- D2 -- B1 -- cycle), grey, invisible);
filldraw(shift(1.5, 0.0)*(A2 -- D3 -- D2 -- C2 -- cycle), grey, invisible);
filldraw(shift(1.5, 0.0)*(B2 -- D3 -- D1 -- C1 -- cycle), grey, invisible);
draw(shift(1.5, 0.0)*(A1 -- A2), white+linewidth(4.0pt));
draw(shift(1.5, 0.0)*(A1 -- A2));
draw(shift(1.5, 0.0)*(B1 -- B2), white+linewidth(4.0pt));
draw(shift(1.5, 0.0)*(B1 -- B2));
draw(shift(1.5, 0.0)*(C1 -- C2), white+linewidth(4.0pt));
draw(shift(1.5, 0.0)*(C1 -- C2));
