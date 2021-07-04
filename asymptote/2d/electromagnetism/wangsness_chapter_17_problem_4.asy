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

/*  Size of the output figure.                                                */
size(128);

/*  Default font size for labels.                                             */
defaultpen(fontsize(7pt));

/*  Pen for dashed and solid lines.                                           */
pen dpen = black + linewidth(0.5pt) + linetype("4 4");
pen apen = black + linewidth(0.5pt) + fontsize(4pt);

/*  Pair for the origin and the point of interest in the plane.               */
pair O = (0.0, 0.0);
pair P = (2.0, 1.3);

/*  Pairs for the X and Y axes.                                               */
pair X = (3.0, 0.0);
pair Y = (0.0, 2.0);

/*  Displacements for the x and y axes.                                       */
real dx = 0.7;
real dy = 0.7;

/*  Size of arrow heads.                                                      */
real arsize = 5bp;
real small_arr = 3bp;

/*  Radii of the two circles.                                                 */
real R = 0.5;
real r = 0.3;

/*  Smaller font size for some labels.                                        */
real fsize = 0.5pt;

/*  Point on the circle around P.                                             */
pair Q = P + scale(r)*expi(0.25*pi);

/*  Draw and label the two axes.                                              */
draw(Label("$x$", position=1.0), O -- X, N, SharpArrow(arsize));
draw(Label("$y$", position=1.0), O -- Y, E, SharpArrow(arsize));

/*  Draw the circle around P.                                                 */
draw(circle(P, R), black);

/*  Label the radius.                                                         */
draw(Label("$r$", fontsize(fsize)), P -- Q);

/*  Label the radius of the outer circle.                                     */
draw(Label("$a$", fontsize(fsize)), P -- (P + scale(R)*expi(1.8*pi)), SW);

/*  Label the x displacement for the point around P.                          */
draw("$\rho$", (0.0, Q.y) -- Q, N, dpen);

/*  Label the secondary coordinate system centered at P.                      */
Label x_tilde = Label("$\tilde{x}$", position=1.0);
Label y_tilde = Label("$\tilde{y}$", position=1.0);
draw(x_tilde, P -- (P + (dx, 0.0)), N, apen, SharpArrow(small_arr));
draw(y_tilde, P -- (P + (0.0, dy)), E, apen, SharpArrow(small_arr));
