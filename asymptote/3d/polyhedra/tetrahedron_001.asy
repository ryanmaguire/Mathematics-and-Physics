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

import three;
import settings;
import tube;
settings.outformat = "pdf";
settings.render = 8;
size(128);

currentprojection = perspective(
    camera = (100.0, 20.0, 00.0),
    up = (0.0, 0.0, 1.0),
    target = (0.0, 0.0, 0.0),
    zoom = 1.0
);

real z0 = sqrt(0.5);
real r = 0.03;

triple A = (1.0, 0.0, -z0);
triple B = (-1.0, 0.0, -z0);
triple C = (0.0, 1.0, z0);
triple D = (0.0, -1.0, z0);

material blob = material(
    diffusepen = deepred,
    emissivepen = gray(0.2),
    specularpen = gray(0.2)
);

material pipe = material(
    diffusepen = deepblue,
    emissivepen = gray(0.1),
    specularpen = gray(0.1)
);

material ball = material(
    diffusepen = cyan,
    emissivepen = gray(0.1),
    specularpen = gray(0.1)
);

surface sphere = scale(2.0*r, 2.0*r, 2.0*r)*unitsphere;

draw(surface(A -- B -- C -- cycle, planar=true), surfacepen=blob);
draw(surface(A -- B -- D -- cycle, planar=true), surfacepen=blob);
draw(surface(A -- C -- D -- cycle, planar=true), surfacepen=blob);
draw(surface(B -- C -- D -- cycle, planar=true), surfacepen=blob);
draw(tube(A -- B, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(A -- C, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(A -- D, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(B -- C, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(B -- D, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(C -- D, scale(r)*unitcircle), surfacepen=pipe);
draw(shift(A)*sphere, surfacepen=ball);
draw(shift(B)*sphere, surfacepen=ball);
draw(shift(C)*sphere, surfacepen=ball);
draw(shift(D)*sphere, surfacepen=ball);
