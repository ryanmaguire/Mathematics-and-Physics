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
int n, m;
int N = 2;

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
for (n = 0; n < 4; ++n)
{
    /*  Compute the angle of the current point.                               */
    theta = 0.5*pi*n + 0.25*pi;

    /*  And compute the position of the point.                                */
    V[n] = expi(theta);
}
/*  End of for loop computing the vertices.                                   */

V[4] = (0.0, 0.0);
real rDot = 0.05;
transform T;

for (m = 0; m < N; ++m)
{
    for (n = 0; n < N; ++ n)
    {
        T = shift(2.0*edge*m, 2.0*edge*n);

        /*  Draw the edges.                                                   */
        draw(T*(V[0] -- V[4]));
        draw(T*(V[1] -- V[4]));
        draw(T*(V[2] -- V[4]));
        draw(T*(V[3] -- V[4]));

        draw(T*(V[0] -- (edge, V[0].y)));
        draw(T*((-edge, V[0].y) -- V[1]));
        draw(T*(V[3] -- (edge, V[3].y)));
        draw(T*((-edge, V[3].y) -- V[2]));
        draw(T*(V[1] -- (V[1].x, edge)));
        draw(T*((V[1].x, -edge) -- V[2]));
        draw(T*(V[0] -- (V[0].x, edge)));
        draw(T*((V[3].x, -edge) -- V[3]));
        draw(T*(V[4] -- (0.0, edge)));
        draw(T*((0.0, -edge) -- V[4]));
        draw(T*(V[4] -- (edge, 0.0)));
        draw(T*((-edge, 0.0) -- V[4]));

        filldraw(circle(T*V[0], rDot), black, black);
        filldraw(circle(T*V[1], rDot), black, black);
        filldraw(circle(T*V[2], rDot), black, black);
        filldraw(circle(T*V[3], rDot), black, black);
        filldraw(circle(T*V[4], rDot), black, black);
    }
}

