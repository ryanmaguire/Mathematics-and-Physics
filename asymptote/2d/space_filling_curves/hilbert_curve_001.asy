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
 *      Draws iterations of the Hilbert curve.                                *
 ******************************************************************************/

/*  Used to make the path a rainbow gradient to indicate start and end.       */
import palette;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(256);

/*  Default pen for drawing.                                                  */
defaultpen(black + linewidth(0.4pt));

/*  Pen for coloring with a rainbow gradient.                                 */
pen[] mypen = Rainbow(144);

/*  Angle of tilt for the Hilbert curve, in degrees.                          */
real dir_angle = 0.0;

/*  Starting point for the Hilbert curve. This doesn't quite matter.          */
pair A = (0.0, 1.0);

/*  Number of Hilbert iterations to perform. Warning, the complexity grows    *
 *  like 4^n, where n is the depth. Do not make this large.                   */
int depth = 4;

/*  Counter for the number of line segments created in the Hilbert curve.     */
int pen_counter = 0;

/*  Path for the Hilbert curve, which starts at A.                            */
path g = A;

/*  Moves the point to its new position and updates the path with a new line. */
void forward(real stride)
{
    /*  Increment the point forward by the given direction and length.        */
    A = A + scale(stride, stride)*dir(dir_angle);

    /*  Add this new point to the path.                                       */
    g = g -- A;

    /*  We've added another line segment, so increment the counter.           */
    pen_counter += 1;
}
/*  End of forward.                                                           */

/*  Turns the direction "right" by incr degrees and ensures the result is     *
 *  between 0 and 360 degrees.                                                */
void right(real incr)
{
    /*  Turning right meaning decreasing the angle by incr.                   */
    dir_angle = fmod(dir_angle - incr, 360.0);

    /*  fmod makes sure |dir_angle| < 360. Make sure it is also positive.     */
    if (dir_angle < 0.0)
        dir_angle += 360.0;
}
/*  End of right.                                                             */

/*  Turns the direction "left" by incr degrees and ensures the result is      *
 *  between 0 and 360 degrees.                                                */
void left(real incr)
{
    /*  Turning left meaning increasing the angle by incr.                    */
    dir_angle = fmod(dir_angle + incr, 360.0);

    /*  fmod makes sure |dir_angle| < 360. Make sure it is also positive.     */
    if (dir_angle < 0.0)
        dir_angle += 360.0;
}
/*  End of left.                                                              */

/*  Function for drawing Hilbert curve with "level" iterations, and largest   *
 *  length of a segment set to "stride".                                      */
void hilbert(int level, real angle, real stride)
{
    /*  The zeroth level is a single line segment. Add this.                  */
    if (level == 0)
        return;

    /*  Otherwise we use the recursive steps to define the Hilbert curve.     */
    else
    {
        right(angle);
        hilbert(level - 1, -angle, stride);

        forward(stride);
        left(angle);
        hilbert(level - 1, angle, stride);

        forward(stride);
        hilbert(level - 1, angle, stride);

        left(angle);
        forward(stride);
        hilbert(level - 1, -angle, stride);

        right(angle);
    }
}
/*  End of hilbert.                                                           */

/*  The number of steps in the Hilbert curve grows at a ludicrous 4^n. Do not *
 *  use this for large n.                                                     */
hilbert(depth, 90.0, 2.0^-depth);

/*  Pen for coloring with a rainbow gradient.                                 */
pen[] mypen = Rainbow(pen_counter) + linewidth(0.8pt);

/*  Draw the path for the Hilbert curve, and color it with a rainbow gradient.*/
for (int n = 0; n < pen_counter - 1; ++n)
    draw(point(g, n) -- point(g, n+1), mypen[n]);
