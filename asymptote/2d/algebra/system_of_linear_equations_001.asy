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
 *      Draw two lines representing a linear system of equations.             *
 ******************************************************************************/

/*  Functions for adding grid lines to a drawing.                             */
access "grid_lines.asy" as grid;

/*  Function for plotting the x and y axes.                                   */
access "coordinate_axes.asy" as axes;

/*  Default pens and parameters for size(512) drawings provided here.         */
import "size_256_default_settings.asy" as default;

/*  Start and end values for the square guide-grid to be drawn.               */
int grid_start = -4;
int grid_end = 4;

/*  Length of the grid lines.                                                 */
real grid_length = 4.1;

/*  Length of the axes.                                                       */
real axis_length = 4.2;

/*  Start and end points for the lines representing the linear equations.     */
pair starta = (-4.0, 3.0);
pair enda = (4.0, -2.333333);
pair startb = (-4.0, 1.0);
pair endb = (4.0, -0.333333);

/*  Add grid lines to the drawing.                                            */
grid.DrawGridLinesWithTickMarks(grid_start, grid_end, grid_length);

/*  Draw the coordinate axes.                                                 */
axes.DrawAndLabelSquareCoordinateAxes(axis_length);

/*  Draw the lines representing the linear equations.                         */
draw(starta -- enda, default.red_pen);
draw(startb -- endb, default.blue_pen);

/*  Label two points on the line.                                             */
label("$2x+3y=1$", (-3.0, 3.5));
label("$x+6y=2$", (-3.0, 1.2));
