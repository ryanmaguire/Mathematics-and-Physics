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

import custom_arrows;
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(256);

defaultpen(black + linewidth(0.5pt));

real rDot = 0.05;
real arsize = 5bp;
int n;
int n_arrows = 23;
real x = -4.7;
real dx = 0.2;
pen dashp = defaultpen + linetype("4 4");

for (n = 0; n < n_arrows; ++n)
{
    draw((x, 2.0) -- (x, 0.0), SharpArrows(arsize));
    x += dx;
}

draw((-5.0, 0.0) -- (5.0, 0.0), SharpArrows(arsize));
draw((-5.0, 2.0) -- (5.0, 2.0), SharpArrows(arsize));

filldraw(circle((0.0, 0.0), rDot), black, black);
filldraw(circle((0.0, 2.0), rDot), black, black);
draw((0.0, -0.5) -- (0.0, -1.5), SharpArrow(arsize));

draw((0.0, -2.5) -- (-5.0, -2.5), SharpArrow(arsize));
draw((0.0, -3.0) -- (5.0, -3.0), SharpArrow(arsize));
draw((0.0, -2.0) -- (5.0, -2.0), SharpArrow(arsize));

filldraw(circle((0.0, -2.5), rDot), white, black);
filldraw(circle((0.0, -3.0), rDot), black, black);
filldraw(circle((0.0, -2.0), rDot), black, black);
draw((0.0, -3.5) -- (0.0, -4.5), dashp, SharpArrow(arsize));

draw((-0.5, -5.5) -- (-5.0, -5.5), SharpArrow(arsize));
draw((0.0, -6.0) -- (5.0, -6.0), SharpArrow(arsize));
draw((0.0, -5.0) -- (5.0, -5.0), SharpArrow(arsize));
draw((-0.5, -5.5){dir(0.0)} .. (0.0, -6.0){dir(0.0)});
draw((-0.5, -5.5){dir(0.0)} .. (0.0, -5.0){dir(0.0)});

filldraw(circle((0.0, -6.0), rDot), black, black);
filldraw(circle((0.0, -5.0), rDot), black, black);
