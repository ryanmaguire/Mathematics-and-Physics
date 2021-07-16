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

import custom_arrows;

real arsize = 5bp;
draw((0,0) -- (1, 1), SharpArrow(arsize));
draw((1, 0) -- (0, 1), white + linewidth(5pt));
draw((1, 0) -- (0, 1), SharpArrow(arsize));


draw(shift(0.0, -3.0)*((0,0) -- (1, 1)), SharpArrow(arsize));
draw(shift(0.0, -3.0)*((1, 0) -- (0, 1)), white + linewidth(5pt));
draw(shift(0.0, -3.0)*((1, 0) -- (0, 1)), SharpArrow(arsize));

filldraw(circle((-2.0, -1.0), 0.04), grey, black);
filldraw(circle((3.0, -1.0), 0.04), grey, black);
