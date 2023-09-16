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
 *      Draw a line representing an affine equation y = ax + b in the plane.  *
 ******************************************************************************/

/*  Functions for adding grid lines to a drawing.                             */
access "grid_lines.asy" as grid;

/*  Function for plotting the x and y axes.                                   */
access "coordinate_axes.asy" as axes;

/*  Size of the figure.                                                       */
size(256);

/*  Default pen for drawings.                                                 */
defaultpen(black + linewidth(0.5pt));

/*  Start and end values for the square guide-grid to be drawn.               */
int grid_start = -3;
int grid_end = 3;

/*  Length of the grid lines.                                                 */
real grid_length = 3.9;

/*  Length of the axes.                                                       */
real axis_length = 4.2;

/*  Pen for labels.                                                           */
pen label_pen = fontsize(6pt);

/*  Start and end points for the line representing the linear equation.       */
pair start = (-2.32, -4.2);
pair end = (2.72, 4.2);

/*  Radius for dots representing points in the plane.                         */
real rDot = 0.07;

/*  Add grid lines to the drawing.                                            */
grid.DrawGridLinesWithTickMarks(grid_start, grid_end, grid_length);

/*  Draw the coordinate axes.                                                 */
axes.DrawAndLabelSquareCoordinateAxes(axis_length);

/*  Draw the line representing the linear equation.                           */
draw(start -- end);

/*  Label two points on the line.                                             */
filldraw(circle((-1.0, -2.0), rDot), black, black);
filldraw(circle((2.0, 3.0), rDot), black, black);
label("$(2, 3)$", (1.58, 3.5), label_pen);
label("$(-1, -2)$", (-2.08, -1.5), label_pen);
