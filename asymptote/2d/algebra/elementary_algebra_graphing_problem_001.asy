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

/*  Create 3D drawings using 2D points.                                       */
import "vec2.asy" as vec2;

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

/*  Points for the lines. Used for linear equations of the form y = mx + b.   */
vec2.Vec2 A0 = vec2.Vec2(-3.00, -10.0);
vec2.Vec2 A1 = vec2.Vec2(-3.00, +10.0);
vec2.Vec2 B0 = vec2.Vec2(-10.0, +2.00);
vec2.Vec2 B1 = vec2.Vec2(+10.0, +2.00);
vec2.Vec2 C0 = vec2.Vec2(-7.50, +10.0);
vec2.Vec2 C1 = vec2.Vec2(+10.0, -1.67);
vec2.Vec2 D0 = vec2.Vec2(-4.67, -10.0);
vec2.Vec2 D1 = vec2.Vec2(+8.67, +10.0);
vec2.Vec2 E0 = vec2.Vec2(+0.00, -10.0);
vec2.Vec2 E1 = vec2.Vec2(+10.0, +0.00);

/*  Used for the function f(x) = |x - 3|.                                     */
vec2.Vec2 F0 = vec2.Vec2(-7.00, +10.0);
vec2.Vec2 F1 = vec2.Vec2(+3.00, +0.00);
vec2.Vec2 F2 = vec2.Vec2(+10.0, +7.00);
vec2.Vec2 FPts[] = {F0, F1, F2};

/*  Several straight lines.                                                   */
draw(A0.LineTo(A1), green, default.sharp_arrows);
draw(B0.LineTo(B1), purple, default.sharp_arrows);
draw(C0.LineTo(C1), cyan, default.sharp_arrows);
draw(D0.LineTo(D1), pink, default.sharp_arrows);
draw(E0.LineTo(E1), red, default.sharp_arrows);

/*  Draw the function |x - 3|.                                                */
draw(vec2.PolygonThroughPoints(FPts), blue, default.sharp_arrows);

/*  Draw the parabola 2 - x^2.                                                */
draw(g_square, orange, default.sharp_arrows);

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
