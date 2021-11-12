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
import settings;
settings.outformat = "pdf";

defaultpen(black + linewidth(0.5pt) + fontsize(7pt));

real arsize = 5bp;
real a = 0.1;
pen thickp = black + linewidth(1.0pt);
path g;
draw((a, 0.0) -- (0.5, 0.5 - a) -- (1.0 - a, 0.0));
draw((a, 1.0) -- (0.5, 0.5 + a) -- (1.0 - a, 1.0));
draw((1.0, a) -- (0.5 + a, 0.5) -- (1.0, 1.0 - a));
draw((0.0, a) -- (0.5 - a, 0.5) -- (0.0, 1.0 -a));
draw((0.5 - a, 0.5) -- (0.5 + a, 0.5), thickp);
draw((0.1, 0.1) -- (0.25, 0.25), SharpArrow(arsize));
draw((0.75, 0.75) -- (0.9, 0.9), SharpArrow(arsize));
draw((0.9, 0.1) -- (0.75, 0.25), SharpArrow(arsize));
draw((0.25, 0.75) -- (0.1, 0.9), SharpArrow(arsize));
label("$0$", (0.5, -0.2));

draw((2.0 + a, 0.0) -- (2.5, 0.5 - a) -- (3.0 - a, 0.0));
draw((2.0 + a, 1.0) -- (2.5, 0.5 + a) -- (3.0 - a, 1.0));
draw((3.0, a) -- (2.5 + a, 0.5) -- (3.0, 1.0 - a));
draw((2.0, a) -- (2.5 - a, 0.5) -- (2.0, 1.0 -a));
draw((2.5, 0.5 - a) -- (2.5, 0.5 + a), thickp);
draw((2.1, 0.1) -- (2.25, 0.25), SharpArrow(arsize));
draw((2.75, 0.75) -- (2.9, 0.9), SharpArrow(arsize));
draw((2.9, 0.1) -- (2.75, 0.25), SharpArrow(arsize));
draw((2.25, 0.75) -- (2.1, 0.9), SharpArrow(arsize));
label("$1$", (2.5, -0.2));
