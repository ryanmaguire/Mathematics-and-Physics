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

/*  Sharp tikz style arrows provided here.                                    */
access "custom_arrows.asy" as arrows;

/*  Functions for adding grid lines to a drawing.                             */
access "grid_lines.asy" as grid;

/*  Function for plotting the x and y axes.                                   */
access "coordinate_axes.asy" as axes;

/*  Default pens and parameters for size(512) drawings provided here.         */
import "size_512_default_settings.asy" as default;

/*  Start and end values for the square guide-grid to be drawn.               */
int grid_start = -3;
int grid_end = 3;

/*  Length of the grid lines.                                                 */
real grid_length = 3.9;

/*  Length of the axes.                                                       */
real axes_length = 4.2;

/*  Start and end points for the line representing the linear equation.       */
pair start = (-4.0, -1.0);
pair end = (4.0, 3.0);

/*  Coordinates for the points on the triangle indicating rise over run.      */
pair p1 = (0.0, 1.0);
pair p2 = (2.0, 1.0);
pair p3 = (2.0, 2.0);

/*  Coordinates for the labels for the function y = mx + b and rise/run.      */
pair m = (-2.7, 2.7);
pair b = (-2.1, 1.6);
pair y = (2.0, 3.3);

/*  Add grid lines to the drawing.                                            */
grid.DrawGridLinesWithTickMarks(grid_start, grid_end, grid_length);

/*  Draw the coordinate axes.                                                 */
axes.DrawAndLabelSquareCoordinateAxes(axes_length);

/*  Draw the line.                                                            */
draw(start -- end);

/*  Mark points on the line to help indicate the rise and the run.            */
filldraw(circle(p1, default.dot_radius));
filldraw(circle(p2, default.dot_radius));
filldraw(circle(p3, default.dot_radius));

/*  Draw perpendicular lines to form a triangle.                              */
draw(Label("Rise"), p2 -- p3, E, default.dash_pen);
draw(Label("Run"), p1 -- p2, S, default.dash_pen);

/*  Labels for the equation y = mx + b.                                       */
label("$m=\frac{\textrm{Rise}}{\textrm{Run}}$", m);
label("$b=y\textrm{-intercept}$", b);
label("$y=mx+b$", y);
