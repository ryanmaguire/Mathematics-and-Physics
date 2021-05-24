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

/*  Draw the image on a PDF file.                                             */
import settings;
settings.outformat = "pdf";

/*  Custom arrows mimicing the tikz style. _custom_arrows.asy must be in      *
 *  your path when creating this figure.                                      */
import _custom_arrows;

/* Size of the output figure.                                                 */
size(256);

/*  Default pen for drawing figures.                                          */
defaultpen(black + linewidth(0.5pt) + fontsize(7pt));

/*  Default size of arrowheads.                                               */
real arsize = 5bp;

/*  Pen for drawing axes.                                                     */
pen axesp  = black + linewidth(0.7pt) + fontsize(9pt);

/*  Radius of the big circle, length of the axes, and radius of circle        *
 *  for used for indicating an angle.                                         */
real R = 1.0;
real len = 1.8;
real rAng = 0.2;

/*  Various points on the circle used to draw the rectangle.                  */
pair A = scale(R)*expi(3pi/4);
pair B = scale(R)*expi(-pi/4);
pair D = scale(R)*expi(pi/4);
pair X = (len, 0.0);
pair Y = (0.0, len);
pair O = (0.0, 0.0);

/*  The angle the point D makes.                                              */
real delta = atan(D.y/D.x);

/*  Draw the circle and add axes.                                             */
draw(circle(O, R));
draw(Label("$B$", position=1), O--X, S, axesp, SharpArrow(arsize));
draw(Label("$A$", position=1), O--Y, W, axesp, SharpArrow(arsize));

/*  Draw the rectangle.                                                       */
draw(A--(A+D)--(B+D)--B--cycle);
draw(O--D);

/*  Add the angle and label.                                                  */
draw("$\delta$", arc(O, rAng, 90, 180*delta/pi), N+0.5E);
