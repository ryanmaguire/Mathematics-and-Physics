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
 *  Date:       September 29, 2021                                            *
 ******************************************************************************/

/*  Tools for drawing the Klein bottle here.                                  */
import graph3;

/*  Coloring tools are here.                                                  */
import palette;

/*  Tools for creating GIFs.                                                  */
import animation;

/*  The GIF will be created in this variable.                                 */
animation a;

/*  Variable for indexing.                                                    */
int n;

/*  Number of frames in the GIF.                                              */
int n_frames = 100;

/*  Samples for the Klein bottle.                                             */
int samples = 20;

/*  Variable for looping over the Klein bottle.                               */
real x = 0.0;

/*  Incrementing factor for the Klein bottle.                                 */
real dx = 2.0*pi / n_frames;

/*  Surface for the Klein bottle.                                             */
surface s;

/*  Precompute sqrt(2).                                                       */
real SQRT_2 = sqrt(2.0);

/*  Size of the created image.                                                */
size(1024);

/*  Camera setup.                                                             */
currentprojection = perspective(
    camera = (20, -20,40),
    up     = (0,  -1, 0),
    target = (0,   0, 0),
    zoom   = 1
);

/*  Lighting for the drawing.                                                 */
currentlight = light(
    new pen[] {
        rgb(0.38, 0.38, 0.45),
        rgb(0.6, 0.6, 0.67),
        rgb(0.5, 0.5, 0.57)
    },
    specularfactor=3,
    new triple[] {
        (-2,-1.5,-0.5),
        (2,1.1,-2.5),
        (-0.5,0,2)
    }
);

/*  Parameterization of RP^2.                                                 */
triple real_proj_plane(pair t)
{
    real u = t.x;
    real v = t.y;
    real cu = cos(u);
    real su = sin(u);
    real cv = cos(v);
    real sv = sin(v);
    real s2v = sin(2.0*v);
    real c2u = cos(2.0*u);
    real s2u = sin(2.0*u);
    real s3u = sin(3.0*u);
    real denom = 1.0 / (2.0 - SQRT_2*s3u*s2v);

    real x0 = (SQRT_2*cv*cv*c2u + cu*s2v)*denom;
    real x1 = (SQRT_2*cv*cv*s2u - su*s2v)*denom;
    real x2 = 3.0*cv*cv*denom;

    return (x0, x1, x2);
}
/*  End of real_proj_plane.                                                   */

/*  Loop over the frames and create the GIF.                                  */
for (n = 0; n < n_frames; ++n)
{
    /*  Create the surface.                                                   */
    s = surface(real_proj_plane, (x, 0.0), (x+0.4, 2.0*pi),
                samples, samples, Spline);

    /*  Color the surface with a gradient.                                    */
    s.colors(palette(s.map(ypart), Gradient(green, blue)));

    /*  Draw the surface to the actual frame.                                 */
    draw(s, render(merge=true));

    /*  Add this frame to the GIF.                                            */
    a.add();

    /*  Erase the screen for the next image.                                  */
    erase();

    /*  Increment x.                                                          */
    x += dx;
}

/*  Render the GIF.                                                           */
a.movie(delay=50);
