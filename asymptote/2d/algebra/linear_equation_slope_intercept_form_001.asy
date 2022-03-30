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
 *      Draw a visual for the slope-intercept form of a line.                 *
 ******************************************************************************/

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Size of the figure.                                                       */
size(128);

/*  Default pen for drawings.                                                 */
defaultpen(black + linewidth(0.5pt));

/*  Variable for indexing.                                                    */
int n;

/*  Start and end values for the square guide-grid to be drawn.               */
int grid_start = -3;
int grid_end = 3;

/*  Variables for drawing the grid, and drawing the axes.                     */
pair top, bottom, left, right;

/*  Length of the grid lines.                                                 */
real length = 3.9;

/*  Length of the axes.                                                       */
real axeslength = 4.2;

/*  Thin grey pen used for the grid.                                          */
pen thingreyp = gray(0.8) + linewidth(0.3pt);

/*  Dashed pen for drawing perpendicular lines.                               */
pen dashp = defaultpen + linetype("4 4") + fontsize(7pt);

/*  Thicker black pen used for the axes.                                      */
pen axesp = black + linewidth(0.7pt) + fontsize(9pt);

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  Pen for labels.                                                           */
pen labelp = fontsize(6pt);

/*  Start and end points for the line representing the linear equation.       */
pair start = (-4.0, -1.0);
pair end = (4.0, 3.0);

/*  Radius for dots representing points in the plane.                         */
real rDot = 0.07;

/*  Coordinates for the points on the triangle indicating rise over run.      */
pair p1 = (0.0, 1.0);
pair p2 = (2.0, 1.0);
pair p3 = (2.0, 2.0);

/*  Coordinates for the labels for the function y = mx + b and rise/run.      */
pair m = (-2.7, 2.7);
pair b = (-2.1, 1.6);
pair y = (2.0, 3.3);

/*  Radius of a dot indicating a point in the plane.                          */
real rDot = 0.05;

/*  Loop through and draw the lines for the grid.                             */
for (n = grid_start; n <= grid_end; ++n)
{
    /*  The grid consists of straight lines left-to-right and top-to-bottom.  *
     *  Compute the current set of lines to be drawn and draw them.           */
    bottom = (n, -length);
    top = (n, length);
    left = (-length, n);
    right = (length, n);

    draw(bottom -- top, thingreyp);
    draw(left -- right, thingreyp);
}
/*  End of for-loop drawing the guide-grid.                                   */

/*  Draw the axes.                                                            */
bottom = (0.0, -axeslength);
top = (0.0, axeslength);
left = (-axeslength, 0.0);
right = (axeslength, 0.0);

draw(Label("$y$", position=1.0), bottom -- top, E, axesp, SharpArrows(arsize));
draw(Label("$x$", position=1.0), left -- right, S, axesp, SharpArrows(arsize));

/*  Draw the line.                                                            */
draw(start -- end);

/*  Mark points on the line to help indicate the rise and the run.            */
filldraw(circle(p1, rDot), black, black);
filldraw(circle(p2, rDot), black, black);
filldraw(circle(p3, rDot), black, black);

/*  Draw perpendicular lines to form a triangle.                              */
draw(Label("Rise"), p2 -- p3, E, dashp);
draw(Label("Run"), p1 -- p2, S, dashp);

/*  Labels for the equation y = mx + b.                                       */
label("$m=\frac{\textrm{Rise}}{\textrm{Run}}$", m, dashp);
label("$b=y\textrm{-intercept}$", b, dashp);
label("$y=mx+b$", y, dashp);
