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
 *  Date:       October 4, 2021                                               *
 ******************************************************************************/

 /*  3D tools are here.                                                        */
import graph3;

/*  Needed for the GIF.                                                       */
import animation;

/*  Size of the GIF.                                                          */
size(1024);

/*  Setup the camera.                                                         */
currentprojection = perspective(5.0, 2.0, 2.0);

/*  The frames of the GIF will be stored in this variable.                    */
animation a;

/*  Increment in time for Euler's method for the falling ladder.              */
real dt = 0.01;

/*  Variable for indexing.                                                    */
int n;

/*  Number of snapshots in time we'll compute the ladder falling.             */
int n_times = 300;

/*  Width of the rectangular part of the ladder.                              */
real width = 4.0;

/*  Depth of the rectangular part of the ladder.                              */
real depth = 2.0;

/*  Height of the ladder.                                                     */
real height = 60.0;

/*  Distance between the two rectangular parts of the ladder.                 */
real step_length = 12.0;

/*  Length of the rails, the actual cylindrical steps of the ladder.          */
real rail_length = step_length + depth;

/*  Number of rails in the ladder.                                            */
int n_rails = 10;

/*  Factor for the distance between rails on the ladder.                      */
real rail_factor = 1.0 / n_rails;

/*  Radius of the rails.                                                      */
real rail_radius = 0.35*width;

/*  The material the ladder is made out of.                                   */
material blob = material(
    diffusepen = gray(0.7),
    specularpen = gray(0.3),
    emissivepen = gray(0.3)
);

/*  Function for drawing the ladder.                                          */
void draw_ladder(real phi)
{
    /*  Variable for indexing over rails.                                     */
    int m;

    /*  Factor for shifting the rails up the ladder.                          */
    transform3 move = shift(0.0, 0.0, rail_factor*height);

    /*  The rectangular part of the ladder.                                   */
    surface s = scale(depth, width, height)*unitcube;
    s = rotate(phi, (1.0, 0.0, 0.0))*s;

    /*  Draw both rectangular portions of the ladder.                         */
    draw(s, surfacepen=blob);
    draw(shift(step_length, 0.0, 0.0)*s, surfacepen=blob);

    /*  Create a cylinder for the rails of the ladder.                        */
    s = scale(rail_radius, rail_radius, rail_length)*unitcylinder;
    s = rotate(90.0, (0.0, 1.0, 0.0))*s;
    s = shift(0.0, 0.5*width, rail_factor*height)*s;

    /*  Loop over and draw the rails.                                         */
    for (m = 1; m < n_rails; ++m)
    {
        draw(rotate(phi, (1.0, 0.0, 0.0))*s, surfacepen=blob);
        s = move*s;
    }
}
/*  End of draw_ladder.                                                       */

/*  Starting angle of the ladder.                                             */
real theta = 0.125*pi;

/*  Starting angular velocity.                                                */
real dtheta = 0.0;

/*  Draw an invisible sphere to "zoom-out" a bit so the whole ladder is       *
 *  always in view without needing the camera to change.                      */
draw(
    shift(0.0, -0.5*height, 0.4*height)*
        (scale(0.7*height, 0.7*height, 0.7*height)*unitsphere),
        invisible
);

/*  Draw a floor to indicate where the ladder falling stops.                  */
draw(
    surface(
        (0.8*height, 0.4*height, 0) -- (0.8*height, -1.2*height, 0) --
        (-0.8*height, -1.2*height, 0) -- (-0.8*height, 0.4*height, 0) -- cycle
    ),
    green
);

/*  Loop over the snapshots of time.                                          */
for (n = 0; n < n_times; ++n)
{
    /*  Once the angle hits pi/2, the ladder hits the floor. Stop there.      */
    if (theta < 0.5*pi)
    {
        /*  If theta < pi/2, use Euler's method to numerically solve the      *
         *  pendulum problem. The acceleration theta'' is proportional to     *
         *  sin(theta).                                                       */
        dtheta += sin(theta)*dt;
        theta += dtheta*dt;
    }

    /*  Add every 5 snapshots to the GIF.                                     */
    if (n % 5 == 0)
    {
        save();
        draw_ladder(180.0*theta/pi);
        a.add();
        restore();
    }
}
/*  End of for-loop for the ladder.                                           */

/*  Render the GIF.                                                           */
erase();
a.movie(delay=20);
