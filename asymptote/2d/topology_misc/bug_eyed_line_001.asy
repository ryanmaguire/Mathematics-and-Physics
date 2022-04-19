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
real start = -4.5;
real end = 4.6;
real dx = 0.25;
real x = start;

draw((-5.0, 0.0) -- (5.0, 0.0), SharpArrows(arsize));
draw((-5.0, 2.0) -- (5.0, 2.0), SharpArrows(arsize));

while (x < end)
{
    if (x != 0.0)
        draw((x, 0.0) -- (x, 2.0), SharpArrows(arsize));

    x += dx;
}

draw((0.0, -0.5) -- (0.0, -1.5), SharpArrow(arsize));

draw((-5.0, -2.5) -- (5.0, -2.5), SharpArrows(arsize));
filldraw(circle((0.0, -2.5), rDot), white, black);
filldraw(circle((0.0, -3.0), rDot), black, black);
filldraw(circle((0.0, -2.0), rDot), black, black);

draw((0.0, -3.5) -- (0.0, -4.5), SharpArrow(arsize));

draw((-0.5, -5.5) -- (-5.0, -5.5), SharpArrow(arsize));
draw((0.5, -5.5) -- (5.0, -5.5), SharpArrow(arsize));
filldraw(circle((0.0, -6.0), rDot), black, black);
filldraw(circle((0.0, -5.0), rDot), black, black);
draw((0.5, -5.5){dir(180.0)} .. (0.0, -6.0) .. (-0.5, -5.5){dir(180.0)});
draw((0.5, -5.5){dir(180.0)} .. (0.0, -5.0) .. (-0.5, -5.5){dir(180.0)});
