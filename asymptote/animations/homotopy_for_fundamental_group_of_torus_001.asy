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
 *  Date:       September 24, 2021                                            *
 ******************************************************************************/

/*  Tools for drawing the torus here.                                         */
import graph3;

/*  Tools for creating GIFs.                                                  */
import animation;
import palette;

/*  Needed to set the render factor.                                          */
import settings;
settings.outformat="gif";
settings.render = 8;

size(1024);

currentprojection = perspective(
    camera = (20, 80, 30),
    up = (0, 0, 1),
    target = (0, 0, 0),
    zoom = 0.85
);

/*  The GIF will be created in this variable.                                 */
animation out;

int n;
int n_frames = 100;
real x = 0.0;
real dx = 1.0 / n_frames;

// Radii of the torus.
real R = 4;
real a = 1;

// Number of samples in the figure.
int samples = 32;

// Material of the torus.
material blob = material(diffusepen=gray(0.7) + opacity(0.5),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

surface s;

// Parameterization of a torus.
/*  Parameterization of the torus.                                            */
triple f(pair t)
{
    /*  Variables for precomputing cosine and sine to save computations.      */
    real cx, sx, cy, sy;

    /*  Compute the sines and cosines.                                        */
    cx = cos(2.0*pi*t.x);
    cy = cos(2.0*pi*t.y);
    sx = sin(2.0*pi*t.x);
    sy = sin(2.0*pi*t.y);

    /*  Use the standard parameterization for the torus.                      */
    return ((R + a*cy)*cx, (R + a*cy)*sx, a*sy);
}

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

pair f1(real t)
{
    if (t < 0.5)
        return (4.0*t, 0.0);
    else
        return (2.0, 4.0*(t-0.5));
}

triple H(real t)
{
    pair p = scale(x)*f1(t) + scale(1.0-x)*f0(t);
    return f(p);
}

// Some contour lines.
s = surface(f, (0,0), (1.0, 1.0), samples, samples, Spline);
draw(s, surfacepen=blob, render(merge=true));

/*  Loop over the frames and draw the GIF.                                    */
for (n = 0; n < n_frames; ++n)
{
    /*  Save the background so we don't need to redraw it every time.         */
    save();


    /*  Add the frame to the GIF.                                             */
    draw(graph(H, 0.0, 1.0, 200, operator ..), black + linewidth(0.7pt));
    out.add();

    /*  Reset the picture so it's just the background again.                  */
    restore();

    /*  Compute the next epsilon.                                             */
    x += dx;
}

/*  Render the gif.                                                           */
erase();
out.movie(delay=50);
