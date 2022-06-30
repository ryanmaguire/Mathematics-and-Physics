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

/*  Size of the figure.                                                       */
size(256);

/*  Default pen for drawings.                                                 */
defaultpen(black + linewidth(0.7pt));
pen dpen = black + linewidth(0.4pt) + linetype("4 4");

real arsize = 5bp;
pair X0 = (-1.2, 0.0);
pair X1 = (1.2, 0.0);
pair Y0 = (0.0, -1.2);
pair Y1 = (0.0, 1.2);

draw(Label("$x$", position=1.0), X0 -- X1, N, SharpArrow(arsize));
draw(Label("$y$", position=1.0), Y0 -- Y1, E, SharpArrow(arsize));
filldraw(circle((0.0, 0.0), 1.0), cyan + opacity(0.5), dpen);

draw(Label("$r$", position=0.5), (0.0, 0.0) -- expi(0.25*pi), NW);
dot((0.0, 0.0));
dot(expi(0.25*pi));
