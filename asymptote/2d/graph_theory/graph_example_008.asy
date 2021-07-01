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

/*  Number of points in a circle.                                             */
int N = 2;

/*  The number of circles.                                                    */
int number_of_circles = 16;

/*  Variable for the angle a point has on a given circle.                     */
real theta;

/*  And a shift in the angle for alternating circles.                         */
real shift;

/*  Radius of the dots representing vertices.                                 */
real radius = 0.4;

/*  Loop through and create the vertices.                                     */
for (m = 0; m < number_of_circles; ++m)
{
    /*  If m is even there is no shift. If it is odd, shift by pi / N.        */
    if ((m % 2) == 0)
        shift = 0;
    else
        shift = pi / N;

    /*  Create the vertices on the current circle.                            */
    for (n = 0; n < N; ++n)
    {
        /*  Compute the angle of the current point.                           */
        theta = 2*pi*n/N;

        /*  And compute the position of the point.                            */
        V[n + m*N] = scale(m + 1.0)*expi(theta + shift);
    }
    /*  End of for loop over points on a given circle.                        */
}
/*  End of for loop over each circle.                                         */

/*  Draw all of the edges.                                                    */
for (m = 0; m < number_of_circles * N; ++m)
{
    for (n = 0; n < number_of_circles * N; ++n)
    {
        /*  No need to draw an edge from a point to itself.                   */
        if (n == m)
            continue;
        else
            draw(V[n] -- V[m], black + linewidth(0.1pt));
    }
}

/*  Place a dot on all of the vertices.                                       */
for (n = 0; n < number_of_circles * N; ++n)
    filldraw(circle(V[n], radius), blue, black);
