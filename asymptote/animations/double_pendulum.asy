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

/*  Number of snapshots of time used in Euler's method.                       */
int n_times = 1800;

/*  Incrementing factor for Euler's method.                                   */
real dt = 0.01;

/*  The origin.                                                               */
pair O = (0.0, 0.0);

/*  Starting angles of the double pendulum.                                   */
real theta0 = 0.5*pi;
real theta1 = 0.5*pi;

/*  Points for the two pendulums.                                             */
pair P0 = (sin(theta0), -cos(theta0));
pair P1 = P0 + (sin(theta1), -cos(theta1));
pair Q1;

/*  Starting angular velocity for the double pendulum.                        */
real dtheta0 = 0.0;
real dtheta1 = 0.0;

/*  Starting generalized momentums (from the Lagrangian of the system).       */
real ptheta0 = 0.0;
real ptheta1 = 0.0;

/*  Factors for computing the next angle via Euler's method.                  */
real factor, cos_diff;

/*  Size of a dot.                                                            */
real rDot = 0.05;

/*  Black bar the pendulum swings from.                                       */
draw((-1.5, 0.0) -- (1.5, 0.0), black);

for (n = 0; n < n_times; ++n)
{
    /*  Compute the generalized momentum.                                     */
    ptheta0 -= 0.5*dt*(dtheta0*dtheta1*sin(theta0 - theta1) + 3.0*sin(theta0));
    ptheta1 -= 0.5*dt*(dtheta0*dtheta1*sin(theta1 - theta0) + sin(theta1));

    /*  Compute the increments in the angles via Euler's method.              */
    cos_diff = cos(theta1 - theta0);
    factor = 6.0 / (16.0 - 9.0*cos_diff*cos_diff);
    dtheta0 = factor*(2.0*ptheta0 - 3.0*cos_diff*ptheta1);
    dtheta1 = factor*(8.0*ptheta1 - 3.0*cos_diff*ptheta0);

    /*  Update the angles.                                                    */
    theta0 += dtheta0*dt;
    theta1 += dtheta1*dt;

    /*  Compute the locations of the pendulums.                               */
    P0 = (sin(theta0), -cos(theta0));
    Q1 = P0 + (sin(theta1), -cos(theta1));

    /*  Draw the path of the second pendulum over time.                       */
    draw(P1 -- Q1, red);
    P1 = Q1;


    /*  Only update the GIF every 10 frames to save space.                    */
    if (n % 10 == 0)
    {
        save();

        /*  Draw the double pendulum and mark the two ends.                   */
        draw(O -- P0 -- P1);
        filldraw(circle(P0, rDot), blue, black);
        filldraw(circle(P1, rDot), red, black);
        a.add();
        restore();
    }
}
/*  End of for-loop generating the GIF.                                       */

/*  Render the GIF.                                                           */
erase();
a.movie(delay=50);
