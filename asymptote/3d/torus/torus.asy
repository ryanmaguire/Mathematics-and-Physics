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
 ******************************************************************************/

/*  Size of the figure.                                                       */
size(256);

import graph3;
import settings;
settings.outformat = "pdf";

settings.render = 8;

currentprojection=perspective(camera = (20, 80, 30), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

// Radii of the torus.
real R = 4;
real a = 1;

// Number of samples in the figure.
int samples = 24;

// Material of the torus.
material blob = material(diffusepen=gray(0.7),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

surface s;

// Parameterization of a torus.
triple f(pair t)
{
    return ((R+a*cos(t.y))*cos(t.x), (R+a*cos(t.y))*sin(t.x), a*sin(t.y));
}

// Some contour lines.
s = surface(f, (0,0), (2pi,2pi), samples, samples, Spline);
draw(s, surfacepen=blob, render(merge=true));
