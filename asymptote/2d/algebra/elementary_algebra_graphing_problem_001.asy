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
 *      Plots for a graphing problem for students studying elementary algebra.*
 ******************************************************************************/

/*  Functions for creating paths from real-valued functions.                  */
access "path_functions.asy" as pf;

/*  Functions for adding grid lines to a drawing.                             */
access "grid_lines.asy" as grid;

/*  Function for plotting the x and y axes.                                   */
access "coordinate_axes.asy" as axes;

/*  Default pens and parameters for size(512) drawings provided here.         */
import "size_512_default_settings.asy" as default;

/*  The parabola function to be drawn.                                        */
real two_minus_x_squared(real x)
{
    return 2.0 - x*x;
}

/*  The square root function to be drawn.                                     */
real sqrt_two_minus_x(real x)
{
    return sqrt(2.0 - x);
}

/*  Start and end values for the square guide-grid to be drawn.               */
int grid_start = -9;
int grid_end = 9;

/*  Length of the grid lines.                                                 */
real grid_length = 10.2;

/*  Number of samples for square root and parabola functions.                 */
int samples = 20;

/*  Paths used for the square root and parabola functions.                    */
path g_square = pf.PathFromFunction(two_minus_x_squared, -3.46, 3.46, samples);
path g_root = pf.PathFromFunction(sqrt_two_minus_x, 2.0, -10.0, samples);

/*  Add grid lines to the drawing.                                            */
grid.DrawGridLinesWithTickMarks(grid_start, grid_end, grid_length);

/*  Draw the coordinate axes.                                                 */
axes.DrawAndLabelSquareCoordinateAxes(grid_length);

/*  Draw the function |x - 3|.                                                */
draw((-7.0, 10.0) -- (3.0, 0.0) -- (10.0, 7.0), blue, default.sharp_arrow);

/*  Several straight lines.                                                   */
draw((-3.0, -10.0) -- (-3.0, 10.0), green, default.sharp_arrow);
draw((-10.0, 2.0) -- (10.0, 2.0), purple, default.sharp_arrow);
draw((-7.5, 10.0) -- (10.0, -1.667), cyan, default.sharp_arrow);
draw((-4.6666, -10.0) -- (8.6666, 10.0), pink, default.sharp_arrow);
draw((0.0, -10.0) -- (10.0, 0.0), red, default.sharp_arrow);

/*  Draw the parabola 2-x^2.                                                  */
draw(g_square, orange, default.sharp_arrow);

/*  Lastly, the function sqrt(2 - x).                                         */
draw(g_root, brown, default.sharp_arrow);

/*  Label all of the functions.                                               */
label("$y=|x-3|$", (8.4, 3.7), blue + default.label_size);
label("$x=-3$", (-4.1, 4.5), green + default.label_size);
label("$y=2$", (8.0, 2.5), purple + default.label_size);
label("$y=-\frac{2}{3}x+5$", (3.0, 4.5), cyan + default.label_size);
label("$3x-2y=6$", (6.0, 8.4), pink + default.label_size);
label("$y=-x^{2}+2$", (4.2, -3.2), orange + default.label_size);
label("$y=x-10$", (7.2, -4.5), red + default.label_size);
label("$y=\sqrt{2-x}$", (-7.0, 3.5), brown + default.label_size);
