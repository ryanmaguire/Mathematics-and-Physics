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

defaultpen(black + linewidth(0.7pt) + fontsize(10pt));

real arsize = 8bp;
real r = 1.0;
pair A = (0.0, 0.0);
pair B = (2.9*r, 0.0);
pair C = (4.7*r, -1.0*r);
pair D = (2.9*r, -2.5*r);
pair E = (0.0, -2.5*r);

path g = (0.0, r) .. (0.6*r, 0.0) .. (0.0, -r) .. (-0.6*r, 0.0) ..
         (0.0, r) .. (0.2*r, 1.1*r) .. (0.0, -1.2*r) ..
         (-0.2*r, 1.1*r) .. cycle;

draw(reverse(circle(B, r)), MidSharpArrow(arsize));
draw(circle(D, r), MidSharpArrow(arsize));
draw(circle(C + (r, 0.0), 0.7*r), MidSharpArrow(arsize));
draw(g, MidSharpArrow(arsize));
draw(shift(E)*reverse(g), MidSharpArrow(arsize));
dot(A);
dot(B);
dot(C);
dot(D);
dot(E);

label("$-2$", A, 2.0*SW);
label("$-1$", B, 2.0*SW);
label("$0$", C, 2.0*SW);
label("$1$", D, 2.0*SW);
label("$2$", E, 2.0*SW);
