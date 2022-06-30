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
defaultpen(black + linewidth(0.5pt));

pen axesp = black + linewidth(0.7pt);
pen dashp = black + linewidth(0.5pt) + linetype("4 4");
real arsize = 5bp;
Label L;
pair X0 = (-0.2, 0.0);
pair X1 = (2.2, 0.0);
pair Y0 = (0.0, -0.2);
pair Y1 = (0.0, 2.2);

pair P = (0.6, 0.6);
pair Q = (1.4, 1.4);

draw(Label("$x$", position = 1.0), X0 -- X1, N, SharpArrow(arsize));
draw(Label("$y$", position = 1.0), Y0 -- Y1, E, SharpArrow(arsize));
draw(Label("$\Delta{y}$", position = 0.5), Q -- (Q.x, P.y), E, dashp);
draw(Label("$\Delta{x}$", position = 0.5), P -- (Q.x, P.y), S, dashp);
L = Label(rotate(45.0)*"$\sqrt{\Delta{x}^{2}+\Delta{y}^{2}}$", position = 0.5); 
draw(L, P -- Q, NW);
dot(P);
dot(Q);
label("$P$", P, SW);
label("$Q$", Q, NE);
