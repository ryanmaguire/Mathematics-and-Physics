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

path g1 = (-0.5, 0.0) -- (-5.0, 0.0);
path g2 = (0.5, 0.0) -- (5.0, 0.0);
path g3 = (0.5, 0.0){dir(180.0)} .. (0.0, 0.5) .. (-0.5, 0.0){dir(180.0)};
path g4 = (0.5, 0.0){dir(180.0)} .. (0.0, -0.5) .. (-0.5, 0.0){dir(180.0)};

pair labelpoint = (1.0, 0.4);
pair uppoint = (0.0, 0.5);
pair downpoint = (0.0, -0.5);
pair origin = (0.0, 0.0);

transform TShift = shift(0.0, -1.5);
path g5 = (-0.2, -3.0) -- (-5.0, -3.0);
path g6 = (0.2, -3.0) -- (5.0, -3.0);
path g7 = (-0.5, -3.0) -- (-0.1, -3.0);
path g8 = (0.1, -3.0) -- (0.5, -3.0);

draw(g1, SharpArrow(arsize));
draw(g2, SharpArrow(arsize));
draw(g3, blue);
draw(g4);
filldraw(circle(uppoint, rDot), blue, blue);
filldraw(circle(downpoint, rDot), black, black);
label("$\mathcal{U}$", labelpoint);

g1 = TShift*g1;
g2 = TShift*g2;
g3 = TShift*g3;
g4 = TShift*g4;
downpoint = TShift*downpoint;
uppoint = TShift*uppoint;
labelpoint = TShift*labelpoint;

draw(g1, SharpArrow(arsize));
draw(g2, SharpArrow(arsize));
draw(g3);
draw(g4, blue);
filldraw(circle(uppoint, rDot), black, black);
filldraw(circle(downpoint, rDot), blue, blue);
label("$\mathcal{V}$", labelpoint);

downpoint = TShift*downpoint;
uppoint = TShift*uppoint;
labelpoint = TShift*labelpoint;

draw(g5, SharpArrow(arsize));
draw(g6, SharpArrow(arsize));
draw(g7, blue + linewidth(1.0pt));
draw(g8, blue + linewidth(1.0pt));
filldraw(circle(uppoint, rDot), black, black);
filldraw(circle(downpoint, rDot), black, black);
label("$\mathcal{U}\cap\mathcal{V}$", labelpoint);
