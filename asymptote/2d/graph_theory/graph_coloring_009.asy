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
pair[] W;

/*  Variables for indexing.                                                   */
int m, n;

/*  Number of points in K_5.                                                  */
int N = 5;

/*  Variable for the angle a point has on the circle.                         */
real theta;

/*  Create the vertices on the circle.                                        */
for (n = 0; n < N; ++n)
{
    /*  Compute the angle of the current point.                               */
    theta = 2*pi*n/N + 0.5*pi/N;

    /*  And compute the position of the point.                                */
    V[n] = scale(0.5)*expi(theta);
    W[n] = expi(theta);
}
/*  End of for loop computing the vertices.                                   */

draw(V[0] -- W[0]);
draw(V[0] -- V[2]);
draw(V[0] -- V[3]);

draw(V[1] -- W[1]);
draw(V[1] -- V[3]);
draw(V[1] -- V[4]);

draw(V[2] -- W[2]);
draw(V[2] -- V[4]);

draw(V[3] -- W[3]);

draw(V[4] -- W[4]);

draw(W[0] -- W[1] -- W[2] -- W[3] -- W[4] -- cycle);

/*  Color the vertices.                                                       */
filldraw(circle(V[0], 0.03), red, black);
filldraw(circle(V[1], 0.03), blue, black);
filldraw(circle(V[2], 0.03), green, black);
filldraw(circle(V[3], 0.03), green, black);
filldraw(circle(V[4], 0.03), red, black);

filldraw(circle(W[0], 0.03), blue, black);
filldraw(circle(W[1], 0.03), red, black);
filldraw(circle(W[2], 0.03), blue, black);
filldraw(circle(W[3], 0.03), red, black);
filldraw(circle(W[4], 0.03), green, black);

