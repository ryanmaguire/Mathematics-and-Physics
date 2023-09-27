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
 *      Draw a line representing a linear equation y = ax in the plane.       *
 ******************************************************************************/

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

/*  Length of the coordinate axes.                                            */
real axis_length = 4.2;

/*  Start and end points for the line representing the linear equation.       */
pair start = (-axis_length, -axis_length);
pair end = (axis_length, axis_length);

/*  Add grid lines to the drawing.                                            */
grid.DrawGridLinesWithTickMarks(grid_start, grid_end, grid_length);

/*  Draw the coordinate axes.                                                 */
axes.DrawAndLabelSquareCoordinateAxes(axis_length);

/*  Draw the line representing the linear equation.                           */
draw(start -- end);

/*  Label two points on the line.                                             */
filldraw(circle((0.0, 0.0), default.dot_radius));
filldraw(circle((1.0, 1.0), default.dot_radius));
label("$(0, 0)$", (-0.58, 0.5));
label("$(1, 1)$", (0.58, 1.5));
