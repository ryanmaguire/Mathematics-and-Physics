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

/*  Used for rendering the Klein bottle.                                      */
import graph3;

/*  Used for setting the output to PDF and setting the rendering factor.      */
import settings;

/*  EPS is sometimes weird with opacity, so output PDF.                       */
settings.outformat = "pdf";

/*  Render with high quality.                                                 */
settings.render = 8;

/*  Size of the figure.                                                       */
size(256);

/*  Set up the camera.                                                        */
currentprojection = perspective(
    camera = (50, 0, 30),
    up = (0, 0, 1),
    target = (0,  0,  0),
    zoom = 1.0
);

/*  Radii of the "torus", the factors used to draw the Klein bottle.          */
real R = 4;
real a = 1;

/*  Size of dots for vertices of the graph.                                   */
real rDot = 0.05;


pair[] V;
triple[] P;
int n;
int N = 5;
real theta;

// Number of samples in the figure.
int samples = 200;

// Material of the torus.
material blob = material(diffusepen=gray(0.7) + opacity(0.7),
                         emissivepen=gray(0.2),
                         specularpen=gray(0.2));

material orb = material(diffusepen=blue+lightgreen,
                        emissivepen=gray(0.2),
                        specularpen=gray(0.2));

surface s;

/* Parameterization of the Klein bottle.                                      */
triple f(pair t)
{
    real v = 2*pi*t.x;
    real u = 2*pi*t.y;
    real cu = cos(u);
    real su = sin(u);
    real cv = cos(v);
    real sv = sin(v);

    real cu2 = cu*cu;
    real cu4 = cu2*cu2;

    real x = (-2.0/15.0)*cu*(
        3.0*cv - 30.0*su + 90*cu4*su - 60.0*cu4*cu2*su + 5.0*cu*cv*su
    );

    real y = (-1.0/15.0)*su*(
        3.0*cv - 3.0*cu2*cv - 48.0*cu4*cv + 48.0*cu4*cu2*cv - 60.0*su +
        5.0*cu*cv*su - 5.0*cu2*cu*cv*su -
        80.0*cu4*cu*cv*su + 80.0*cu4*cu2*cu*cv*su
    );

    real z = (2.0/15.0)*(3.0 + 5.0*cu*su)*sv;
    return (x,y,z);
}

/*  Create the vertices on the circle.                                        */
for (n = 0; n < N; ++n)
{
    /*  Compute the angle of the current point.                               */
    theta = 2*pi*n/N + 0.5*pi/N;

    /*  And compute the position of the point.                                */
    V[n] = scale(0.1, 0.03)*expi(theta) + (0.05, 0.62);
    P[n] = f(V[n]);
}
/*  End of for loop computing the vertices.                                   */

triple draw_line(real t, pair A, pair B)
{
    return f(scale(1-t)*A + scale(t)*B);
}

triple c0(real t)
{
    return draw_line(t, V[1], (0.5 - V[3].x, V[3].y + 0.5));
}

triple c1(real t)
{
    return draw_line(t, V[1], (0.5 - V[4].x, V[4].y + 0.5));
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
s = surface(f, (0.0, 0.0), (1.0, 0.5), samples, samples, Spline);
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

