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
pen bluep = blue + linewidth(1.2pt);

real rDot = 0.05;
real arsize = 5bp;

draw((-0.5, 0.0) -- (-5.0, 0.0), SharpArrow(arsize));
draw((0.0, 0.5) -- (5.0, 0.5), SharpArrow(arsize));
draw((0.0, -0.5) -- (5.0, -0.5), SharpArrow(arsize));
draw((-0.5, 0.0){dir(0.0)} .. (0.0, 0.5){dir(0.0)}, bluep);
draw((-0.5, 0.0){dir(0.0)} .. (0.0, -0.5){dir(0.0)});

filldraw(circle((0.0, 0.5), rDot), blue, blue);
filldraw(circle((0.0, -0.5), rDot), black, black);
draw((0.0, 0.5) -- (0.5, 0.5), bluep);

draw((-0.5, -2.0) -- (-5.0, -2.0), SharpArrow(arsize));
draw((0.0, -1.5) -- (5.0, -1.5), SharpArrow(arsize));
draw((0.0, -2.5) -- (5.0, -2.5), SharpArrow(arsize));
draw((-0.5, -2.0){dir(0.0)} .. (0.0, -2.5){dir(0.0)}, bluep);
draw((-0.5, -2.0){dir(0.0)} .. (0.0, -1.5){dir(0.0)});
draw((0.0, -2.5) -- (0.5, -2.5), bluep);

filldraw(circle((0.0, -2.5), rDot), blue, bluep);
filldraw(circle((0.0, -1.5), rDot), black, black);

label("$\mathcal{U}$", (-0.35, 0.8));
label("$\mathcal{V}$", (-0.35, -2.8));
