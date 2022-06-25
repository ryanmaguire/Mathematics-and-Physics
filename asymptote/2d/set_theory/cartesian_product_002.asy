/******************************************************************************
 *                                  LICENSE                                   *
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

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(256);

/*  Default pen for drawing.                                                  */
defaultpen(black + linewidth(0.4pt));

pen axesp = black+linewidth(0.7pt);
pen gridp = gray(0.5)+linewidth(0.4pt);
real arsize = 5bp;
int x, y;
int n_ticks = 8;
real r = 0.05;

draw(Label("$x$", position=1.0), (0.0, 0.0) -- (8.4, 0.0), N, axesp, SharpArrow(arsize));
draw(Label("$y$", position=1.0), (0.0, 0.0) -- (0.0, 8.4), E, axesp, SharpArrow(arsize));

for (x = 0; x < n_ticks; ++x)
{
    for (y = 0; y < n_ticks; ++y)
    {
        filldraw(circle((x, y), r), black, black);
    }
    draw((x, -0.1) -- (x, 0.1), gridp);
    draw((-0.1, x) -- (0.0, x), gridp);
}
