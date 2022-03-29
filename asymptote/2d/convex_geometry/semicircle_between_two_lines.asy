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
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Figure from convex geometry notes. This depicts a semicircle bounded  *
 *      by two lines in the plane.                                            *
 ******************************************************************************/

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  The opacity will not render correctly for EPS format, so use PDF.         */
import settings;
settings.outformat = "pdf";

/*  Default pen for labels.                                                   */
defaultpen(fontsize(7pt));

/*  Size of the output figure.                                                */
size(128);

/*  Axes pen.                                                                 */
pen apen = black + linewidth(0.8pt);

/*  Pen for the semicircle.                                                   */
pen cpen = black + linewidth(0.2pt);

/*  Filler for the semicircle.                                                */
pen fpen = red + opacity(0.5);

/*  Radius of the circle.                                                     */
real R = 1.0;

/*  Size of the arrowheads.                                                   */
real ar = 5bp;

/*  Length of the x and y axes.                                               */
real xlen = 1.3;
real ylen = 0.2;

/*  Locations of all of the points used in the drawing.                       */
pair O = (0.0, 0.0);
pair A = scale(R)*expi(3pi/8);
pair B = scale(R)*expi(pi);
pair C = scale(-0.38)*A;
pair T = (A.y, -A.x);

/*  Coordinates for the ends of the axes.                                     */
pair[] XAxes = {(-xlen, 0.0), (xlen, 0.0)};
pair[] YAxes = {(0.0, -ylen), (0.0, xlen)};

/*  Draw the axes.                                                            */
draw(Label("$x$", position=1), XAxes[0] -- XAxes[1], N, apen, SharpArrow(ar));
draw(Label("$y$", position=1), YAxes[0] -- YAxes[1], E, apen, SharpArrow(ar));

/*  Draw the semicircle.                                                      */
filldraw(arc(O, R, 0, 180) -- cycle, fpen, cpen);

/*  Draw the lines containing the semicircle.                                 */
draw(B -- (B + scale(2.0)*T));
draw(A -- (A + T));
draw(A -- (A - T));

/*  And draw the perpendicular line.                                          */
draw("$\ell_{\theta}$", C -- A);

/*  Lastly, label the points.                                                 */
label("$A$", C, SW);
label("$B$", A, NE);
