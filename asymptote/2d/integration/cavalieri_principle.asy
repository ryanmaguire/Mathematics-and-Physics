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

 /*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(256);

real width = 1.5;
real height = 0.2;
real rdot = 0.02;
pen fillcolor = rgb(255, 215, 0);
int n_coins = 6;

void draw_coin(real x, real y)
{
    path g = (x, y) -- (x+width, y) -- (x+width, y+height) -- (x, y+height);
    filldraw(g -- cycle, fillcolor, black);
}

for (int n = 0; n < n_coins; ++n)
{
    draw_coin(0.0, n*height);
    draw_coin(1.5*width+sin(n*0.2*pi), n*height);
}

draw((-width, 0.0) -- (4.0*width, 0.0));
draw((-width, n_coins*height) -- (4.0*width, n_coins*height));
