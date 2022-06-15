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
size(256);

currentprojection = perspective(
    camera = (100.0, 20.0, 10.0),
    up = (0.0, 0.0, 1.0),
    target = (0.0, 0.0, 0.0),
    zoom = 1.0
);

real s0 = 0.5;
real s1 = 1.0;
real s2 = 0.3;
real r = 0.025;

triple A0 = (s0, s0, s2);
triple A1 = (-s0, s0, s2);
triple A2 = (-s0, -s0, s2);
triple A3 = (s0, -s0, s2);

triple B0 = (s0, s0, -s2);
triple B1 = (-s0, s0, -s2);
triple B2 = (-s0, -s0, -s2);
triple B3 = (s0, -s0, -s2);

triple C0 = (s1, s1, s2);
triple C1 = (-s1, s1, s2);
triple C2 = (-s1, -s1, s2);
triple C3 = (s1, -s1, s2);

triple D0 = (s1, s1, -s2);
triple D1 = (-s1, s1, -s2);
triple D2 = (-s1, -s1, -s2);
triple D3 = (s1, -s1, -s2);

material blob = material(
    diffusepen = deepred + opacity(0.7),
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

surface sphere = scale(2.2*r, 2.0*r, 2.0*r)*unitsphere;

draw(surface(A0 -- A1 -- C1 -- C0 -- cycle, planar=true), surfacepen=blob);
draw(surface(A1 -- A2 -- C2 -- C1 -- cycle, planar=true), surfacepen=blob);
draw(surface(A2 -- A3 -- C3 -- C2 -- cycle, planar=true), surfacepen=blob);
draw(surface(A3 -- A0 -- C0 -- C3 -- cycle, planar=true), surfacepen=blob);
draw(surface(B0 -- B1 -- D1 -- D0 -- cycle, planar=true), surfacepen=blob);
draw(surface(B1 -- B2 -- D2 -- D1 -- cycle, planar=true), surfacepen=blob);
draw(surface(B2 -- B3 -- D3 -- D2 -- cycle, planar=true), surfacepen=blob);
draw(surface(B3 -- B0 -- D0 -- D3 -- cycle, planar=true), surfacepen=blob);
draw(surface(A0 -- A1 -- B1 -- B0 -- cycle, planar=true), surfacepen=blob);
draw(surface(A1 -- A2 -- B2 -- B1 -- cycle, planar=true), surfacepen=blob);
draw(surface(A2 -- A3 -- B3 -- B2 -- cycle, planar=true), surfacepen=blob);
draw(surface(A3 -- A0 -- B0 -- B3 -- cycle, planar=true), surfacepen=blob);
draw(surface(C0 -- C1 -- D1 -- D0 -- cycle, planar=true), surfacepen=blob);
draw(surface(C1 -- C2 -- D2 -- D1 -- cycle, planar=true), surfacepen=blob);
draw(surface(C2 -- C3 -- D3 -- D2 -- cycle, planar=true), surfacepen=blob);
draw(surface(C3 -- C0 -- D0 -- D3 -- cycle, planar=true), surfacepen=blob);
draw(tube(A0 -- B0, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(A1 -- B1, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(A2 -- B2, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(A3 -- B3, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(C0 -- D0, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(C1 -- D1, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(C2 -- D2, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(C3 -- D3, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(A0 -- C0, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(A1 -- C1, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(A2 -- C2, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(A3 -- C3, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(B0 -- D0, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(B1 -- D1, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(B2 -- D2, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(B3 -- D3, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(B0 -- B1 -- B2 -- B3 -- cycle, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(C0 -- C1 -- C2 -- C3 -- cycle, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(D0 -- D1 -- D2 -- D3 -- cycle, scale(r)*unitcircle), surfacepen=pipe);
draw(tube(A0 -- A1 -- A2 -- A3 -- cycle, scale(r)*unitcircle), surfacepen=pipe);
draw(shift(A0)*sphere, surfacepen=ball);
draw(shift(A1)*sphere, surfacepen=ball);
draw(shift(A2)*sphere, surfacepen=ball);
draw(shift(A3)*sphere, surfacepen=ball);
draw(shift(B0)*sphere, surfacepen=ball);
draw(shift(B1)*sphere, surfacepen=ball);
draw(shift(B2)*sphere, surfacepen=ball);
draw(shift(B3)*sphere, surfacepen=ball);
draw(shift(C0)*sphere, surfacepen=ball);
draw(shift(C1)*sphere, surfacepen=ball);
draw(shift(C2)*sphere, surfacepen=ball);
draw(shift(C3)*sphere, surfacepen=ball);
draw(shift(D0)*sphere, surfacepen=ball);
draw(shift(D1)*sphere, surfacepen=ball);
draw(shift(D2)*sphere, surfacepen=ball);
draw(shift(D3)*sphere, surfacepen=ball);
