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
defaultpen(black + linewidth(0.4pt) + fontsize(10pt));
pen thickp = black + linewidth(0.7pt) + fontsize(14pt);
real r = 0.05;
real arsize = 5bp;
margin margins = TrueMargin(0.3cm, 0.3cm);

/*  Coordinates for all points in A and B.                                    */
pair Aa = (1.5, 0.75);
pair Ab = (1.5, 0.0);
pair Ac = (1.5, -0.75);
pair B1 = (-1.5, 1.2);
pair B2 = (-1.5, 0.4);
pair B3 = (-1.5, -0.4);
pair B4 = (-1.5, -1.2);
pair A = (-1.5, 2.5);
pair B = (1.5, 2.5);

/*  Ellipses representing the sets A and B.                                   */
draw(ellipse((-1.5, 0.0), 1.0, 2.0), thickp);
draw(ellipse((1.5, 0.0), 1.0, 2.0), thickp);

/*  Draw circles for the various points.                                      */
filldraw(circle(Aa, r), black, black);
filldraw(circle(Ab, r), black, black);
filldraw(circle(Ac, r), black, black);
filldraw(circle(B1, r), black, black);
filldraw(circle(B2, r), black, black);
filldraw(circle(B3, r), black, black);
filldraw(circle(B4, r), black, black);

/*  Draw paths indicating mappings.                                           */
draw(B1 -- Aa, SharpArrow(arsize), margins);
draw(B2 -- Aa, SharpArrow(arsize), margins);
draw(B3 -- Aa, SharpArrow(arsize), margins);
draw(B4 -- Aa, SharpArrow(arsize), margins);

/*  Label all of the points in A and B.                                       */
label("$a$", Aa, 2*E);
label("$b$", Ab, 2*E);
label("$c$", Ac, 2*E);
label("$1$", B1, 2*W);
label("$2$", B2, 2*W);
label("$3$", B3, 2*W);
label("$4$", B4, 2*W);
label("$A$", A, thickp);
label("$B$", B, thickp);
