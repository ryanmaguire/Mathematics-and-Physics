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

settings.render = 8;

currentprojection=perspective(camera = (40, 0, 10), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

// Radii of the torus.
real R = 4;
real a = 1;
real rDot = 0.1;

pair[] V;
triple[] P;
int n;
int N = 5;
real theta;

// Number of samples in the figure.
int samples = 100;

// Material of the torus.
material blob = material(diffusepen=gray(0.7) + opacity(0.5),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

material orb = material(diffusepen=blue+lightgreen,
                        emissivepen=gray(0.2),
                        specularpen=gray(0.2));

surface s;

// Parameterization of a torus.
triple f(pair t)
{
    real x = (R + a*cos(2*pi*t.y))*cos(2*pi*t.x);
    real y = (R + a*cos(2*pi*t.y))*sin(2*pi*t.x);
    real z = a*sin(2*pi*t.y);
    return (x, y, z);
}

/*  Create the vertices on the circle.                                        */
for (n = 0; n < N; ++n)
{
    /*  Compute the angle of the current point.                               */
    theta = 2*pi*n/N + 0.5*pi/N;

    /*  And compute the position of the point.                                */
    V[n] = scale(0.1)*expi(theta) + (0.0, 0.05);
    P[n] = f(V[n]);
}
/*  End of for loop computing the vertices.                                   */

triple draw_line(real t, pair A, pair B)
{
    return f(scale(1-t)*A + scale(t)*B);
}

triple c0(real t)
{
    return draw_line(t, V[1], V[3] + (0.0, 1.0));
}

triple c1(real t)
{
    return draw_line(t, V[1], V[4] + (0.0, 1.0));
}

triple c2(real t)
{
    return draw_line(t, V[0], V[3] + (1.0, 0.0));
}

triple c3(real t){return draw_line(t, V[0], V[1]);}
triple c4(real t){return draw_line(t, V[0], V[2]);}
triple c5(real t){return draw_line(t, V[0], V[4]);}
triple c6(real t){return draw_line(t, V[1], V[2]);}
triple c7(real t){return draw_line(t, V[2], V[3]);}
triple c8(real t){return draw_line(t, V[2], V[4]);}
triple c9(real t){return draw_line(t, V[3], V[4]);}

// Some contour lines.
s = surface(f, (-1.0, -1.0), (1.0, 1.0), samples, samples, Spline);
draw(s, surfacepen=blob, render(merge=true));

draw(graph(c0, 0.0, 1.0, samples));
draw(graph(c1, 0.0, 1.0, samples));
draw(graph(c2, 0.0, 1.0, samples));
draw(graph(c3, 0.0, 1.0, samples));
draw(graph(c4, 0.0, 1.0, samples));
draw(graph(c5, 0.0, 1.0, samples));
draw(graph(c6, 0.0, 1.0, samples));
draw(graph(c7, 0.0, 1.0, samples));
draw(graph(c8, 0.0, 1.0, samples));
draw(graph(c9, 0.0, 1.0, samples));

s = scale(rDot, rDot, rDot)*unitsphere;

draw(shift(P[0])*s, orb);
draw(shift(P[1])*s, orb);
draw(shift(P[2])*s, orb);
draw(shift(P[3])*s, orb);
draw(shift(P[4])*s, orb);
