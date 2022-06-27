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

texpreamble("\usepackage{amssymb}");

/*  Size of the output figure.                                                */
size(256);

/*  Default pen for drawing.                                                  */
defaultpen(black + linewidth(0.4pt) + fontsize(10pt));
pen thickp = black + linewidth(0.7pt) + fontsize(14pt);
real r = 0.05;
real arsize = 5bp;
margin margins = TrueMargin(0.4cm, 0.4cm);

/*  Coorindates.                                                              */
pair Ba = (1.5, 0.7);
pair Bb = (1.5, 0.0);
pair Bc = (1.5, -0.7);

pair A1 = (-1.5, 1.2);
pair A2 = (-1.5, 0.4);
pair A3 = (-1.5, -0.4);
pair A4 = (-1.5, -1.2);

pair A = (-1.5, 2.5);
pair B = (1.5, 2.5);

/*  Draw ellipses representing the sets A and B.                              */
draw(ellipse((-1.5, 0.0), 1.0, 2.0));
draw(ellipse((1.5, 0.0), 1.0, 2.0));

/*  Draw circles for the various points.                                      */
filldraw(circle(Ba, r), black);
filldraw(circle(Bb, r), black);
filldraw(circle(Bc, r), black);
filldraw(circle(A1, r), black);
filldraw(circle(A2, r), black);
filldraw(circle(A3, r), black);
filldraw(circle(A4, r), black);

draw(A1 -- Bc, SharpArrow(arsize), margins);
draw(A2 -- Ba, SharpArrow(arsize), margins);
draw(A3 -- Bb, SharpArrow(arsize), margins);
draw(A4 -- Ba, SharpArrow(arsize), margins);

label("$A$", A, thickp);
label("$B$", B, thickp);
label("$a$", Ba, 2*E);
label("$b$", Bb, 2*E);
label("$c$", Bc, 2*E);
label("$1$", A1, 2*W);
label("$2$", A2, 2*W);
label("$3$", A3, 2*W);
label("$4$", A4, 2*W);
