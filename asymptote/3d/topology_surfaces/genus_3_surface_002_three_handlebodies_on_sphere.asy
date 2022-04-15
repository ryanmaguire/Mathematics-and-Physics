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
 *      Draw a genus 2 surface by drawing two torii and blending.             *
 ******************************************************************************/

/*  Used for rendering parameterized 3D objects.                              */
import graph3;

/*  PDF works best with LaTeX, output this. Also set the render factor high.  */
import settings;
settings.outformat = "pdf";
settings.render = 8;

/*  Size of the image. For 3D objects it seems best to have this set to a     *
 *  power of 2, otherwise weird vertical or horizontal black lines may appear.*/
size(256);

/*  How the image is being drawn on a 2D picture.                             */
currentprojection = perspective(0.0, 0.0, 10.0);

/*  Defining radii of the torii to be drawn.                                  */
real R = 0.4;
real a = 0.1;

/*  Radius of the sphere.                                                     */
real r = 0.9;

/*  Number of samples for the torii.                                          */
int N = 60;

/*  Start and end parameterizations for the torus.                            */
pair start = (0.0, 0.0);
pair end = (2.0*pi, 2.0*pi);

/*  Material the torus is made out of.                                        */
material blob = material(
    diffusepen = gray(0.7),
    emissivepen = gray(0.2),
    specularpen = gray(0.2)
);

/*  Parameterization of a torus.                                              */
triple torus_parameterization(pair t)
{
    /*  The parameterization is in terms of sine and cosine of 2 pi t.x and   *
     *  2 pi t.y. Precompute these to avoid repetitive calculations.          */
    real u = 2.0*pi*t.x;
    real v = 2.0*pi*t.y;
    real cosu = cos(u);
    real cosv = cos(v);
    real sinu = sin(u);
    real sinv = sin(v);

    /*  Given the two angles u and v, the x, y, and z coordinates are:        */
    real x = (R + a*cosv)*cosu;
    real y = (R + a*cosv)*sinu;
    real z = a*sinv;

    /*  Return the point (x, y, z), which is a point on the surface.          */
    triple out = (x, y, z);
    return out;
}
/*  End of torus_parameterization.                                            */

/*  Create the torus.                                                         */
surface s = surface(torus_parameterization, start, end, N, N, Spline);

/*  Draw the sphere.                                                          */
draw(scale(r, r, r)*unitsphere, surfacepen=blob, render(merge=true));

/*  Attach three handlebodies by drawing three torii connected to the sphere. */
draw(shift(0.0, 0.9, 0.0)*s, surfacepen=blob, render(merge=true));
draw(shift(0.9, 0.0, 0.0)*s, surfacepen=blob, render(merge=true));
draw(shift(-0.9, 0.0, 0.0)*s, surfacepen=blob, render(merge=true));
