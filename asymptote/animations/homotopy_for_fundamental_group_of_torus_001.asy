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
 *  Date:       September 28, 2021                                            *
 ******************************************************************************/

/*  Tools for drawing the torus here.                                         */
import graph3;

/*  Tools for creating GIFs.                                                  */
import animation;

/*  Needed to set the render factor.                                          */
import settings;
settings.outformat="gif";
settings.render = 8;

/*  Size of the GIF.                                                          */
size(1024);

/*  Set up the camera.                                                        */
currentprojection = perspective(
    camera = (20, 80, 30),
    up = (0, 0, 1),
    target = (0, 0, 0),
    zoom = 0.85
);

/*  The GIF will be created in this variable.                                 */
animation out;

/*  Variable for indexing.                                                    */
int n;

/*  Number of frames in the GIF.                                              */
int n_frames = 100;

/*  Global variable used for the homotopy between the two paths on the torus. */
real x = 0.0;

/*  Incrementing factor for x.                                                */
real dx = 1.0 / n_frames;

/*  Radii of the torus.                                                       */
real R = 4;
real a = 1;

/*  Number of samples for the torus.                                          */
int t_samples = 50;

/*  Number of samples for the curve on the torus.                             */
int c_samples = 200;

/*  Pen for the curve.                                                        */
pen cpen = black + linewidth(1.2pt);

/*  Material of the torus.                                                    */
material blob = material(
    diffusepen = gray(0.7) + opacity(0.5),
    emissivepen = gray(0.2),
    specularpen = gray(0.2)
);

/*  Parameterization of the torus.                                            */
triple torus(pair t)
{
    /*  Compute the two parameters for the torus.                             */
    real u = 2.0*pi*t.x;
    real v = 2.0*pi*t.y;

    /*  Compute the sines and cosines.                                        */
    real cu = cos(u);
    real cv = cos(v);
    real su = sin(u);
    real sv = sin(v);

    /*  Use the standard parameterization for the torus.                      */
    return ((R + a*cv)*cu, (R + a*cv)*su, a*sv);
}

/*  The first curve on the torus. This is the lift to the universal cover,    *
 *  which is the plane.                                                       */
pair f0(real t)
{
    if (t < 0.25)
        return (0.0, 4.0*t);
    else if (t < 0.5)
        return (4.0*(t-0.25), 1.0);
    else if (t < 0.75)
        return (1.0, 1.0 + 4.0*(t-0.5));
    else
        return (1.0 + 4.0*(t-0.75), 2.0);
}

/*  The second curve on the torus. This is the lift to the universal cover,   *
 *  which is the plane.                                                       */
pair f1(real t)
{
    if (t < 0.5)
        return (4.0*t, 0.0);
    else
        return (2.0, 4.0*(t-0.5));
}

/*  The homotopy between f0 and f1. This uses the parameterization of the     *
 *  torus (the covering map) to draw the curves on the actual torus.          */
triple H(real t)
{
    pair p = scale(x)*f1(t) + scale(1.0-x)*f0(t);
    return torus(p);
}

/*  Render the torus.                                                         */ 
surface s = surface(torus, (0,0), (1.0, 1.0), t_samples, t_samples, Spline);

/*  Draw the torus. This will be saved so we don't need to repeatedly draw it.*/
draw(s, surfacepen=blob, render(merge=true));

/*  Loop over the frames and draw the GIF.                                    */
for (n = 0; n <= n_frames; ++n)
{
    /*  Save the background so we don't need to redraw it every time.         */
    save();

    /*  Add the frame to the GIF.                                             */
    draw(graph(H, 0.0, 1.0, c_samples, operator ..), cpen);
    out.add();

    /*  Reset the picture so it's just the background again.                  */
    restore();

    /*  Compute the next step in the homotopy.                                */
    x += dx;
}

/*  Render the gif.                                                           */
erase();
out.movie(delay=50);
