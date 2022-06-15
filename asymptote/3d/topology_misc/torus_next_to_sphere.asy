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
 ******************************************************************************/

/*  Size of the figure.                                                       */
size(256);

import graph3;
import settings;
settings.outformat = "pdf";
settings.render = 8;

currentprojection = perspective(
    camera = (5.0, 80.0, 30.0),
    up = (0.0, 0.0, 1.0),
    target = (0.0, 0.0, 0.0),
    zoom = 1.0
);

/*  Radii of the torus.                                                       */
real R = 1.5;
real a = 0.4;

/*  Number of samples in the torus.                                           */
int samples = 24;

/*  Shift for the torus so it is not on top of the sphere.                    */
real xshift = 4.0;

/*  Material of the torus and sphere.                                         */
material blob = material(
    diffusepen = gray(0.7),
    emissivepen = gray(0.1),
    specularpen = gray(0.1)
);

/*  Parameterization of a torus.                                              */
triple f(pair t)
{
    real cosu = cos(t.x);
    real sinu = sin(t.x);
    real cosv = cos(t.y);
    real sinv = sin(t.y);
    real x = (R + a*cosv)*cosu + xshift;
    real y = (R + a*cosv)*sinu;
    real z = a*sinv;
    return (x, y, z);
}

/*  Draw the torus.                                                           */
surface s = surface(f, (0.0, 0.0), (2.0*pi, 2.0*pi), samples, samples, Spline);
draw(s, surfacepen=blob, render(merge=true));

/*  Draw the sphere.                                                          */
draw(unitsphere, surfacepen=blob, render(merge=true));
