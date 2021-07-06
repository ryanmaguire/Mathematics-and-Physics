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
size(128);

/*  Array for vertices.                                                       */
pair[] V;

/*  Variables for indexing.                                                   */
int m, n;

/*  Number of points in K_5.                                                  */
int N = 5;

/*  Variable for the angle a point has on the circle.                         */
real theta;

/*  Value for the edge of the square.                                         */
real edge = 1.5;

/*  Variables for computing where certain lines hit the edge of the square.   */
real x0, x1, y0, dx, dy;

/*  Pairs for the square representing the torus.                              */
pair A = (-edge, -edge);
pair B = (edge, -edge);
pair C = (-edge, edge);
pair D = (edge, edge);

/*  Create the vertices on the circle.                                        */
for (n = 0; n < N; ++n)
{
    /*  Compute the angle of the current point.                               */
    theta = 2*pi*n/N + 0.5*pi/N;

    /*  And compute the position of the point.                                */
    V[n] = expi(theta);

    /*  Draw a dot indicating the vertex.                                     */
    dot(V[n]);
}
/*  End of for loop computing the vertices.                                   */

/*  Draw the edges.                                                           */
draw(V[0] -- V[1]);
draw(V[0] -- V[2]);
draw(V[1] -- V[2]);
draw(V[2] -- V[3]);
draw(V[3] -- V[4]);
draw(V[0] -- V[4]);
draw(V[2] -- V[4]);

/*  The next edges need to wrap around the torus, Pac-Man style.              */
dy = fabs(edge - V[1].y) + fabs(-edge - V[3].y);
dx = fabs(V[1].x - V[3].x);

x0 = V[1].x - dx * (fabs(edge - V[1].y) / dy);
x1 = V[1].x + dx * (fabs(edge - V[1].y) / dy);

draw(V[1] -- (x0, edge));
draw((x0, -edge) -- V[3]);

draw(V[1] -- (x1, edge));
draw((x1, -edge) -- V[4]);

dx = fabs(edge - V[0].x) + fabs(-edge - V[3].x);
dy = V[3].y - V[0].y;

y0 = V[0].y + dy * (fabs(edge - V[0].x) / dx);

draw(V[3] -- (-edge, y0));
draw((edge, y0) -- V[0]);

/*  Draw in lines to indicate the square.                                     */
draw(A -- B, blue + linewidth(1.0));
draw(C -- D, blue + linewidth(1.0));
draw(A -- C, red + linewidth(1.0));
draw(B -- D, red + linewidth(1.0));
