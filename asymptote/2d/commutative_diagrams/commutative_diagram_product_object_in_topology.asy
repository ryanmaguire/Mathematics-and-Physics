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

/*  Default pen used for labels.                                              */
defaultpen(fontsize(10pt));

/*  Pen used to label the induced function.                                   */
pen dpen = fontsize(10pt) + linetype("4 4");

/*  Set arrow size, and mark three points for A, B, and C.                    */
real arsize = 5bp;
pair Y = (0.0, 0.0);
pair X1 = (-1.5, -1.0);
pair X2 = (1.5, -1.0);
pair X12 = (0.0, -1.0);

/*  Margins for the arrows to prevent overlap with labels.                    */
margin margins = TrueMargin(0.5cm, 0.5cm);
margin widemargins = TrueMargin(0.8cm, 0.5cm);

/*  Draw the arrows.                                                          */
draw("$f_{1}$", Y -- X1, NW, SharpArrow(arsize), margins);
draw("$f_{2}$", Y -- X2, NE, SharpArrow(arsize), margins);
draw("$f$", Y -- X12, W, SharpArrow(arsize), margins);
draw("$\pi_{1}$", X12 -- X1, S, SharpArrow(arsize), widemargins);
draw("$\pi_{2}$", X12 -- X2, S, SharpArrow(arsize), widemargins);

/*  Label the points.                                                         */
label("$X_{1}$", X1);
label("$X_{2}$", X2);
label("$Y$", Y);
label("$X_{1}\times{X}_{2}$", X12);
