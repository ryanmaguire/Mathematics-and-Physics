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
 ******************************************************************************/

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(64);

/*  Default pen used for labels.                                              */
defaultpen(fontsize(7pt));

/*  Pens used to label functions.                                             */
pen fpen = fontsize(7pt);
pen dpen = fpen + linetype("4 4");

/*  Set arrow size, and mark three points for A, B, and C.                    */
real arsize = 5bp;
pair A = (0.0, 0.0);
pair B = (1.0, 0.5);
pair C = (1.0, -0.5);

/*  Margins for the arrows to prevent overlap with labels.                    */
margin margins = TrueMargin(0.3cm, 0.3cm);

/*  Draw the arrows.                                                          */
draw("$\alpha$", A -- B, NW, fpen, SharpArrow(arsize), margins);
draw("$\tilde{f}$", C -- B, E, dpen, SharpArrow(arsize), margins);
draw("$f$", C -- A, SW, fpen, SharpArrow(arsize), margins);

/*  Label the points.                                                         */
label("$X$", A);
label("$C(X)$", B);
label("$Y$", C);
