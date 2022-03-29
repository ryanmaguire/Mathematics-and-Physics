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
 *      Give a visual depiction of Galileo's infinity paradox.                *
 ******************************************************************************/

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(128);

/*  Default pen for drawing.                                                  */
defaultpen(black + linewidth(0.4pt));

/*  Thinner pen.                                                              */
pen tpen = black+linewidth(0.2);

/*  Variable for indexing and the number of lines to be drawn.                */
int n;
int number_of_lines = 8;

/*  Length of the longer line.                                                */
real line_length = 1.0;

/*  Distance between dots on the longer line.                                 */
real dx = 2.0*line_length/(real)number_of_lines;

/*  Radius of dots.                                                           */
real rDot = 0.008;

/*  Endpoints for the longer line.                                            */
pair A = (-line_length, 0.0);
pair B = (line_length, 0.0);

/*  Endpoints for the shorter line.                                           */
pair C = (-0.5*line_length, -0.5);
pair D = (0.5*line_length, -0.5);

/*  The position of the observer.                                             */
pair O = (0.0, -1.0);

/*  Variable for the point on the longer line to be connected to O.           */
pair point_on_line_A = A;

/*  Variable for the point on the shorter line to be connected to O.          */
pair point_on_line_C = C;

/*  Draw the two lines from Galileo's paradox.                                */
draw(A -- B);
draw(C -- D);

/*  Draw the lines connecting the observer to the short line to the long line.*/
for (n = 0; n <= number_of_lines; ++n)
{
    draw(O -- point_on_line_A, tpen);
    filldraw(circle(point_on_line_A, rDot));
    filldraw(circle(point_on_line_C, rDot));
    point_on_line_A += (dx, 0.0);
    point_on_line_C += (0.5*dx, 0.0);
}

/*  Fill in the dot for the observer.                                         */
filldraw(circle(O, 1.5*rDot));

/*  Label the observer.                                                       */
label("$O$", O, SE, fontsize(9pt));
