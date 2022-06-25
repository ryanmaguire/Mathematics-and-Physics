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

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(256);

/*  Default pen for drawing.                                                  */
defaultpen(black + linewidth(0.4pt));

pair A000 = (0.0, 0.0);
pair A001 = (1.0, 1.0);
pair A010 = (0.0, 1.0);
pair A100 = (-1.0, 1.0);
pair A011 = (1.0, 2.0);
pair A101 = (0.0, 2.0);
pair A110 = (-1.0, 2.0);
pair A111 = (0.0, 3.0);
real x = 0.4;
real y = 0.3;

draw(A000 -- A001);
draw(A000 -- A010);
draw(A000 -- A100);
draw(A001 -- A101);
draw(A001 -- A011);
draw(A010 -- A011);
draw(A010 -- A110);
draw(A100 -- A101);
draw(A100 -- A110);
draw(A011 -- A111);
draw(A101 -- A111);
draw(A110 -- A111);

filldraw(ellipse(A000, x, y), white, black);
filldraw(ellipse(A001, x, y), white, black);
filldraw(ellipse(A010, x, y), white, black);
filldraw(ellipse(A100, x, y), white, black);
filldraw(ellipse(A011, x, y), white, black);
filldraw(ellipse(A101, x, y), white, black);
filldraw(ellipse(A110, x, y), white, black);
filldraw(ellipse(A111, x, y), white, black);

label("$\emptyset$", A000);
label("$\{\,1\,\}$", A001);
label("$\{\,2\,\}$", A010);
label("$\{\,3\,\}$", A100);
label("$\{\,1,\,2\,\}$", A011);
label("$\{\,1,\,3\,\}$", A101);
label("$\{\,2,\,3\,\}$", A110);
label("$\{\,1,\,2,\,3\,\}$", A111);

