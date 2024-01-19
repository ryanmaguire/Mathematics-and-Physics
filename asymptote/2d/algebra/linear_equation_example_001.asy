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

/*  Two dimensional vector struct provided here.                              */
import "vec2.asy" as vec2;

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
vec2.Vec2 start = vec2.Vec2(-axis_length, -axis_length);
vec2.Vec2 end = vec2.Vec2(axis_length, axis_length);

/*  Points for the labels.                                                    */
vec2.Vec2 O = vec2.Vec2(0.0, 0.0);
vec2.Vec2 P = vec2.Vec2(1.0, 1.0);
vec2.Vec2 L1 = vec2.Vec2(-0.58, 0.5);
vec2.Vec2 L2 = vec2.Vec2(+0.58, 1.5);

/*  Add grid lines to the drawing.                                            */
grid.DrawGridLinesWithTickMarks(grid_start, grid_end, grid_length);

/*  Draw the coordinate axes.                                                 */
axes.DrawAndLabelSquareCoordinateAxes(axis_length);

/*  Draw the line representing the linear equation.                           */
draw(start.LineTo(end));

/*  Label two points on the line.                                             */
vec2.DrawDot(O, default.dot_radius);
vec2.DrawDot(P, default.dot_radius);
vec2.AddLabel("$(0, 0)$", L1);
vec2.AddLabel("$(1, 1)$", L2);
