/******************************************************************************
 *                                 LICENSE                                    *
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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 5, 2021                                               *
 ******************************************************************************/

/*  Used for creating the GIF.                                                */
import animate;

/*  The GIF is created and stored in this variable.                           */
animation a;

/*  Size of the GIF.                                                          */
size(1024);

/*  Variable for indexing.                                                    */
int n;

/*  Number of snapshots of time we'll use Euler's method for.                 */
int n_times = 120;

/*  Incrementing factor for Euler's method.                                   */
real dt = 0.1;

/*  Point for the origin.                                                     */
pair O = (0.0, 0.0);

/*  Two points for the ends of the two pendulums.                             */
pair P0, P1;

/*  Starting angles of the two pendulums. The closer to zero, the better the  *
 *  small angle approximation, and the closer the paths will match. Large     *
 *  angles result in large deviations of the two paths.                       */
real theta0 = 0.5*pi;
real theta1 = 0.5*pi;

/*  Variables for the time derivatives of the angles.                         */
real dtheta0 = 0.0;
real dtheta1 = 0.0;

/*  Radius of a dot for the two pendulums.                                    */
real rDot = 0.05;

/*  The bar the pendulums are hanging from.                                   */
draw((-1.5, 0.0) -- (1.5, 0.0));

/*  Loop over the selected times.                                             */
for (n = 0; n < n_times; ++n)
{
    /*  Use Euler's method to compute the angular velocity. The zeroth angle  *
     *  uses a physically realistic model, whereas the first angle uses the   *
     *  small angle approximation. This is to showcase when this              *
     *  approximation may fail.                                               */
    dtheta0 += -sin(theta0)*dt;
    dtheta1 += -theta1*dt;

    /*  Use Euler's method to compute the current angles.                     */
    theta0 += dtheta0*dt;
    theta1 += dtheta1*dt;

    /*  The current locations of the pendulums.                               */
    P0 = (sin(theta0), -cos(theta0));
    P1 = (sin(theta1), -cos(theta1));

    /*  Save the empty screen with just the bar.                              */
    save();

    /*  Draw the pendulums.                                                   */
    draw(O -- P0, black);
    draw(O -- P1, black);
    filldraw(circle(P0, rDot), blue, black);
    filldraw(circle(P1, rDot), red, black);

    /*  Add the current frame to the GIF.                                     */
    a.add();

    /*  Reset the image back to the lone bar.                                 */
    restore();
}
/*  End of for-loop over the frames of the GIF.                               */

/*  Render the GIF.                                                           */
erase();
a.movie(delay=40);
