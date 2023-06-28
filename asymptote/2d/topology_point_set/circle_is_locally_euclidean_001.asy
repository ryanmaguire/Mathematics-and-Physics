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

import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(256);

/*  Needed for the \color command in LaTeX.                                   */
texpreamble("\usepackage{xcolor}");

defaultpen(black + linewidth(0.7pt) + fontsize(12pt));

texpreamble("\usepackage{amssymb}");
pen axesp = black + linewidth(1.2pt);
pen bluep = blue + linewidth(1.5mm);
pen redp = red + linewidth(1.5mm);
pen cyanp = cyan + linewidth(1.5mm);
pen greenp = green + linewidth(1.5mm);
real arsize = 5bp;

draw((-1.4, 0.0) -- (1.4, 0.0), axesp, SharpArrow(arsize));
draw((0.0, -1.4) -- (0.0, 1.4), axesp, SharpArrow(arsize));

draw(circle((0.0, 0.0), 1.0));
draw(arc((0.0, 0.0), 1.1, 2.0, 178.0), bluep);
draw(arc((0.0, 0.0), 1.1, 182.0, 358.0), greenp);
draw(arc((0.0, 0.0), 1.15, 92.0, 268.0), redp);
draw(arc((0.0, 0.0), 1.15, -88.0, 88.0), cyanp);

label("$\color{blue}{\mathcal{U}_{\textrm{North}}}$", (0.3, 0.7));
label("$\color{green}{\mathcal{U}_{\textrm{South}}}$", (-0.3, -0.7));
label("$\color{red}{\mathcal{U}_{\textrm{West}}}$", (-0.7, 0.3));
label("$\color{cyan}{\mathcal{U}_{\textrm{East}}}$", (0.7, -0.3));
label("$\mathbb{S}^{1}$", (-0.3, 0.7));
label("$\mathbb{R}^{2}$", (1.0, 1.0));
