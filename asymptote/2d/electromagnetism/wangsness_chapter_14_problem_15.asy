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

/*  Pen used for drawing straight lines.                                      */
pen lpen = linewidth(0.5pt);

/*  Radius of the inner circle.                                               */
real R1 = 1.0;

/*  Radius of the outer circle.                                               */
real R2 = 1.5;

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  Size of the bar used to represent tiny displacements.                     */
real barsize = 3bp;

/*  Smaller fontsize for labels.                                              */
real fsize = 6pt;

/*  Label for the tiny displacement.                                          */
Label L = Label("$\textrm{d}\ell$", fontsize(fsize));

/*  Margins to prevent lines from overlapping with labels.                    */
margin margins = TrueMargin(0.0, 0.02cm);

/*  Angle the position vector makes with the x axis, in degrees.              */
real theta = 45.0;

/*  Displacement for the angle.                                               */
real dtheta = 3;

/*  Factor for converting from degrees to radians.                            */
real d2r = 0.017453292519943295;

/*  Length of the displacement.                                               */
real dl = 0.06;

/*  Radius of the dot for the origin.                                         */
real rDot = 0.02;

/*  Pair for the origin.                                                      */
pair O = (0.0, 0.0);

/*  Paths for the arrows.                                                     */
pair arrowend1 = scale(R1 + dl)*expi(d2r*(theta - dtheta));
pair arrowend2 = scale(R1 + dl)*expi(d2r*(theta + dtheta));
path arrow1 = ((scale(2.0)*arrowend1) - arrowend2) -- arrowend1;
path arrow2 = ((scale(2.0)*arrowend2) - arrowend1) -- arrowend2;

/*  Draw the wire.                                                            */
draw("I", arc(O, R1, 0.0, 180.0), N, MidSharpArrow(arsize));
draw("II", (-R1, 0.0) -- (-R2, 0.0), S, MidSharpArrow(arsize));
draw("III", arc(O, R2, 180, 0.0), N, MidSharpArrow(arsize));
draw("IV", (R2, 0.0) -- (R1, 0.0), S, MidSharpArrow(arsize));

/*  Draw two lines to indicate the radii of the two semicircles.              */
draw("$a$", O -- scale(R1)*expi(3pi/4), NE, lpen);
draw("$b$", O -- scale(R2)*expi(6pi/7), S, lpen);

/*  And a line for the position vector.                                       */
draw("$\mathbf{R}$", O -- scale(R1)*expi(pi*theta/180), NW);

/*  Draw the displacement.                                                    */
draw(L, arc(O, R1 + dl, theta - dtheta, theta + dtheta), NE, bar=Bars(barsize));

/*  Draw the arrows.                                                          */
draw(arrow1, SharpArrow(), margins);
draw(arrow2, SharpArrow(), margins);

/*  Mark a point for the origin.                                              */
filldraw(circle(O, rDot), black, black);

/*  Label the charge.                                                         */
label("$q$", O, SE);

/*  And label the charge current.                                             */
label("$I'$", scale(R2 + dl)*expi(0.25*pi), NE);
