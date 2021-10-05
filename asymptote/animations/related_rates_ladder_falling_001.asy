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

/*  Variable for indexing over.                                               */
int n;

/*  Number of frames in the GIF.                                              */
int n_frames = 40;

real width = 4.0;
real depth = 2.0;
real height = 60.0;
real step_length = 12.0;
real rail_length = step_length + depth;
int n_rails = 10;
real rail_factor = 1.0 / n_rails;
real rail_radius = 0.35*width;

/*  The material the cube is made out of.                                     */
material blob = material(
    diffusepen = gray(0.7),
    specularpen = gray(0.3),
    emissivepen = gray(0.3)
);

void draw_ladder(real phi)
{
    int m;
    real val = rail_factor*height;
    triple move = rotate(phi, (1.0, 0.0, 0.0))*(0.0, 0.0, val);
    triple R = rotate(phi, (1.0, 0.0, 0.0))*(height, 0.0, 0.0);
    surface s = scale(depth, width, height)*unitcube;
    s = rotate(phi, (1.0, 0.0, 0.0))*s;

    draw(s, surfacepen=blob);
    draw(shift(step_length, 0.0, 0.0)*s, surfacepen=blob);

    s = scale(rail_radius, rail_radius, rail_length)*unitcylinder;
    s = rotate(90.0, (0.0, 1.0, 0.0))*s;
    s = shift(0.0, 0.25*width + move.y, 0.5*width + move.z)*s;

    for (m = 1; m < n_rails; ++m)
    {
        draw(s, surfacepen=blob);
        s = shift(0.0, move.y, move.z)*s;
    }
}

real theta = 45.0;
real dtheta = theta / n_frames;

draw(
    shift(0.0, -0.5*height, 0.0)*
        (scale(height, height, height)*unitsphere),
        invisible
);

for (n = 0; n < n_frames; ++n)
{
    save();
    draw_ladder(theta);
    a.add();
    restore();
    theta += dtheta;
}

erase();
a.movie(delay=50);
