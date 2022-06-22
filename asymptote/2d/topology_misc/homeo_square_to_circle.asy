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
size(128);

/*  Default pen for drawing figures.                                          */
defaultpen(black + linewidth(0.5pt) + fontsize(7pt));

texpreamble("\usepackage{amssymb}");

real arsize = 5bp;
margin margins = TrueMargin(0.1cm, 0.1cm);

draw(Label("$x$", N), (-3.0, 0.0) -- (3.0, 0.0), SharpArrow(arsize));
draw(Label("$y$", E), (0.0, -3.0) -- (0.0, 3.0), SharpArrow(arsize));
draw(circle((0.0, 0.0), 2.0));
draw((2.0, -2.0) -- (2.0, 2.0) -- (-2.0, 2.0) -- (-2.0, -2.0) -- cycle);

draw((2.0, 2.0) -- (1.414, 1.414), SharpArrow(arsize), margins);
draw((1.5, 2.0) -- (1.2, 1.6), SharpArrow(arsize), margins);
draw((2.0, 1.5) -- (1.6, 1.2), SharpArrow(arsize), margins);

draw((-2.0, 2.0) -- (-1.414, 1.414), SharpArrow(arsize), margins);
draw((-1.5, 2.0) -- (-1.200, 1.600), SharpArrow(arsize), margins);
draw((-2.0, 1.5) -- (-1.600, 1.200), SharpArrow(arsize), margins);

draw((-2.0, -2.0) -- (-1.414, -1.414), SharpArrow(arsize), margins);
draw((-1.5, -2.0) -- (-1.200, -1.600), SharpArrow(arsize), margins);
draw((-2.0, -1.5) -- (-1.600, -1.200), SharpArrow(arsize), margins);

draw((2.0, -2.0) -- (1.414, -1.414), SharpArrow(arsize), margins);
draw((1.5, -2.0) -- (1.200, -1.600), SharpArrow(arsize), margins);
draw((2.0, -1.5) -- (1.600, -1.200), SharpArrow(arsize), margins);

label("$\mathbb{R}^{2}$", (2.5, 2.5));
label("$\mathbb{S}^{1}$", (0.4, 1.6));
