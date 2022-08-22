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

import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(256);

defaultpen(black + linewidth(0.7pt) + fontsize(12pt));

texpreamble("\usepackage{amssymb}");

pen axesp = black + linewidth(1.2pt);
pen bluep = blue + opacity(0.5);
pen redp = red + opacity(0.5);
pen dashp = black + linewidth(0.5pt) + linetype("4 4");
real arsize = 5bp;
real phiP = 0.3*pi;
real phiQ = 0.1*pi;

Label Lx = Label("$x$", position = 0.96);
Label Ly = Label("$y$", position = 0.96);

transform T = scale(2.0);
pair P = expi(phiP);
pair Q = expi(phiQ);

real theta = 0.25*acos(P.x*Q.x + P.y*Q.y);
pair Pa = T*expi(phiP + theta);
pair Pb = T*expi(phiP - theta);
pair Qa = T*expi(phiQ + theta);
pair Qb = T*expi(phiQ - theta);

draw(Lx, (-1.0, 0.0) -- (1.0, 0.0), N, axesp, SharpArrow(arsize));
draw(Ly, (0.0, -1.0) -- (0.0, 1.0), E, axesp, SharpArrow(arsize));

draw(T*(-P) -- T*P);
draw(T*(-Q) -- T*Q);
filldraw(Pa -- (-Pa) -- (-Pb) -- Pb -- cycle, bluep, invisible);
filldraw(Qa -- (-Qa) -- (-Qb) -- Qb -- cycle, redp, invisible);
draw(Pa -- (-Pa), dashp);
draw(Pb -- (-Pb), dashp);
draw(Qa -- (-Qa), dashp);
draw(Qb -- (-Qb), dashp);

clip((1.0, 1.0) -- (1.0, -1.0) -- (-1.0, -1.0) -- (-1.0, 1.0) -- cycle);

label("$\mathcal{U}$", (0.6, 0.5));
label("$\mathcal{V}$", (0.7, 0.05));
label("$\mathbb{R}^{2}$", (-0.6, 0.6));
