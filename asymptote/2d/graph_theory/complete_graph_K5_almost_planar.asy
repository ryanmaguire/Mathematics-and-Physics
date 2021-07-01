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

/*  Number of points in a triangle. We'll draw K_5 via a triangle, a point    *
 *  inside the triangle, and a point outside of it.                           */
int N = 3;

/*  Variable for the angle a point has on the circle.                         */
real theta;

/*  Create the vertices on the circle.                                        */
for (n = 0; n < N; ++n)
{
    /*  Compute the angle of the current point.                               */
    theta = 2*pi*n/N + 0.07*pi;

    /*  And compute the position of the point.                                */
    V[n] = expi(theta);

    /*  Draw a dot indicating the vertex.                                     */
    dot(V[n]);
}
/*  End of for loop computing the vertices.                                   */

/*  Add two more points for K_5.                                              */
V[3] = (0.0, 0.0);
V[4] = (3.0, 0.0);

/*  And add dots.                                                             */
dot(V[3]);
dot(V[4]);

/*  Draw all of the edges.                                                    */
for (m = 0; m < N + 2; ++m)
{
    for (n = 0; n < N + 2; ++n)
    {
        /*  No need to draw an edge from a point to itself.                   */
        if (n == m)
            continue;
        else
            draw(V[n] -- V[m]);
    }
}
/*  End of for loop drawing edges.                                            */
