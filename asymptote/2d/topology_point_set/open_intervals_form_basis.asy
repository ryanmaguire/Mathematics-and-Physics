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
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Draws the intersection of a plane with a cube, revealing a hexagon.   *
 *      This is what you'd get if you dipped a cube into water with one of    *
 *      vertices of the cube facing down.                                     *
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

texpreamble("\usepackage{amssymb}");

pen axesp = black + linewidth(1.0pt);
pen bluep = blue + linewidth(1.4pt);
pen purplep = magenta + linewidth(1.4pt);
pen redp = red + linewidth(1.4pt);
real arsize = 8bp;
real rDot = 0.015;

draw((-1.0, 0.0) -- (1.0, 0.0), SharpArrows(arsize));

draw((-0.7, 0.0) -- (-0.1, 0.0), bluep);
draw((0.2, 0.0) -- (0.8, 0.0), redp);
draw((-0.1, 0.0) -- (0.2, 0.0), purplep);
draw(arc((-0.1, 0.0), 0.3, -15.0, 15.0), bluep);
draw(arc((-0.4, 0.0), 0.3, 165.0, 195.0), bluep);
draw(arc((0.5, 0.0), 0.3, -15.0, 15.0), redp);
draw(arc((0.2, 0.0), 0.3, 165.0, 195.0), redp);
filldraw(circle((0.05, 0.0), rDot), black, black);

label("$a$", (-0.7, -0.15));
label("$c$", (-0.1, -0.15));
label("$b$", (0.2, -0.15));
label("$d$", (0.8, -0.15));
label("$\mathbb{R}$", (1.0, 0.1));
