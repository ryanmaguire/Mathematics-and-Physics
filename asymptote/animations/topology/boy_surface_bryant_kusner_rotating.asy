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

/*  Used for drawing surfaces in 3D.                                          */
import graph3;

/*  Used for coloring the Boy surface.                                        */
import palette;

/*  Needed to create the gif.                                                 */
import animation;

/*  Needed to output a PDF.                                                   */
import settings;
settings.render = 8;
settings.outformat = "gif";

/*  Size of the created image.                                                */
size(1024);

/*  Setup the camera.                                                         */
currentprojection = orthographic(
    camera = (20, 80, 30),
    up = (0, 0, 1),
    target = (0, 0, 0),
    zoom = 1.0
);

/*  Precompute sqrt(5).                                                       */
real SQRT_5 = sqrt(5.0);

/*  The GIF is created with this variable.                                    */
animation out;

/*  Variable for indexing over.                                               */
int n;

/*  Number of frames in the GIF.                                              */
int n_frames = 100;

/*  Variable for looping over angles for the camera.                          */
real theta = 0.0;
real dtheta = 360.0/n_frames;

/*  Asymptote does not have a complex number data type, so let's make one.    */
struct complex {
    real re, im;
};

/*  Constructor for a complex number from two reals.                          */
complex complex(real a, real b)
{
    complex z = new complex;
    z.re = a;
    z.im = b;
    return z;
}

/*  Complex addition. This is done component-wise.                            */
complex operator + (complex z, complex w)
{
    return complex(z.re + w.re, z.im + w.im);
}

/*  Complex subtraction.                                                      */
complex operator - (complex z, complex w)
{
    return complex(z.re - w.re, z.im - w.im);
}

/*  Complex multiplication.                                                   */
complex operator * (complex z, complex w)
{
    return complex(z.re*w.re - z.im*w.im, z.re*w.im + z.im*w.re);
}

/*  Complex division.                                                         */
complex operator / (complex z, complex w)
{
    real denom = 1.0 / (z.re*z.re + w.im*w.im);
    real re = (z.re*w.re + z.im*w.im)*denom;
    real im = (-z.re*w.im + z.im*w.re)*denom;
    return complex(re, im);
}

/*  Addition of a complex number and a real one.                              */
complex operator + (complex z, real a)
{
    return complex(z.re + a, z.im);
}

/*  Addition of a real number and a complex one. This is the same as the      *
 *  previous operator, but for reversed order (z+a vs a+z).                   */
complex operator + (real a, complex z)
{
    return complex(z.re + a, z.im);
}

/*  Subtraction of a real number from a complex one.                          */
complex operator - (complex z, real a)
{
    return complex(z.re - a, z.im);
}

/*  Subtraction of a complex number from a real one.                          */
complex operator - (real a, complex z)
{
    return complex(a - z.re, -z.im);
}

/*  Multiplication of a complex number and a real one.                        */
complex operator * (complex z, real a)
{
    return complex(a*z.re, a*z.im);
}

/*  Multiplication of a real number and a complex one.                        */
complex operator * (real a, complex z)
{
    return complex(a*z.re, a*z.im);
}

/*  Division of a complex number and a real one, z / a.                       */
complex operator / (complex z, real a)
{
    return complex(z.re / a, z.im / a);
}

/*  Division of a real number and a complex one, a / z.                       */
complex operator / (real a, complex z)
{
    real denom = 1.0 / (z.re*z.re + z.im*z.im);
    return complex(a*z.re*denom, -a*z.im*denom);
}

/*  Bryant-Kusner immersion for the Boy Surface, a model for RP^2.            */
triple real_proj_plane(pair t)
{
    /*  The surface is parameterized by the points in the unit disk.          */
    real x = t.x*cos(t.y);
    real y = t.x*sin(t.y);

    /*  Treat this as a complex number.                                       */
    complex z = complex(x, y);

    /*  The rest of these factors are the actual immersion.                   */
    complex z3 = z*z*z;
    complex z4 = z3*z;
    complex z6 = z3*z3;
    complex denom = 1.0 / (z6 + SQRT_5*z3 - 1.0);
    complex g1 = z*(z4 - 1.0)*denom;
    complex g2 = z*(z4 + 1.0)*denom;
    complex g3 = (z6 + 1.0)*denom;
    real f1 = 1.5*g1.im;
    real f2 = -1.5*g2.re;
    real f3 = g3.im - 0.5;
    real f = f1*f1 + f2*f2 + f3*f3;

    return (f1/f, f2/f, f3/f);
}
/*  End of real_proj_plane.                                                   */

/*  Create the Boy Surface.                                                   */
surface s = surface(real_proj_plane, (0.0, 0.0), (1.0, 2.0*pi), 40, 40, Spline);

/*  Give it a nice color gradient.                                            */
s.colors(palette(s.map(zpart), Gradient(blue, green)));

/*  Draw an invisible sphere of radius 2. This gives some "buffer" room so    *
 *  the screen doesn't move as the Boy surface rotates. The result is rather  *
 *  annoying without this buffer. The "zoom" option in the camera can also be *
 *  fiddled with, but this worked best and produced a nice result.            */
draw(scale(2.0, 2.0, 2.0)*unitsphere, invisible);

/*  Loop over the frames and draw the GIF.                                    */
for (n = 0; n <= n_frames; ++n)
{
    /*  Save the blank screen for the next frame in the GIF.                  */
    save();

    /*  Draw the Boy surface.                                                 */
    draw(rotate(theta, (1.0, 1.0, 0.0))*s, render(merge=true));

    /*  Add this frame to the GIF.                                            */
    out.add();

    /*  Reset the frame back to a blank screen.                               */
    restore();

    /*  Increase the rotating angle.                                          */
    theta += dtheta;
}
/*  End of for-loop creating the GIF.                                         */

/*  Render the gif.                                                           */
erase();
out.movie(delay=50);
