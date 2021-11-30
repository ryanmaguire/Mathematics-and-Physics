/******************************************************************************
 *                                 LICENSE                                    *
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
 *      Draws a commutative diagram with 4 vertices, three in 1 column on the *
 *      left and 1 by itself on the right, with arrows connecting to form     *
 *      two triangular regions. This is used in various lecture notes.        *
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

/*  Default pen used for labels.                                              */
defaultpen(fontsize(9pt));

/*  Pen used to label functions.                                              */
pen fpen = fontsize(7pt);

/*  Mark coordinates for the points, and specify the arrow size.              */
real arsize = 5bp;
real height = -0.7;
real width = 0.9;
pair A = (0.0, 0.0);
pair B = (0.0, -height);
pair C = (0.0, -2.0*height);
pair D = (width, -height);

/*  Margins for the arrows to prevent overlap with labels.                    */
margin margins = TrueMargin(0.4cm, 0.4cm);

/*  Draw the arrows.                                                          */
draw("$f_{1}$", A -- D, SE, fpen, SharpArrow(arsize), margins);
draw("$f_{2}$", B -- D, S, fpen, SharpArrow(arsize), margins);
draw("$f_{3}$", C -- D, NE, fpen, SharpArrow(arsize), margins);
draw("$g_{1}$", A -- B, W, fpen, SharpArrow(arsize), margins);
draw("$g_{2}$", B -- C, W, fpen, SharpArrow(arsize), margins);

/*  Label the points.                                                         */
label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);
