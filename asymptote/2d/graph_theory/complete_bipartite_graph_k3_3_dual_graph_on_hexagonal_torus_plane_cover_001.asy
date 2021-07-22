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

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Size of the output figure.                                                */
size(256);

/*  Function for computing the midpoint of two points in the plane.           */
pair MidPoint2D(pair A, pair B)
{
    /*  Use the midpoint formula and return.                                  */
    real x = 0.5*(A.x + B.x);
    real y = 0.5*(A.y + B.y);
    pair mid = (x, y);
    return mid;
}
/*  End of MidPoint2D.                                                        */

/*  Variables for indexing.                                                   */
int k, m, n;

/*  Number of hexagons to draw (NxN will be drawn).                           */
int N = 6;

/*  Two arrays for vertices in the inner and outter hexagons.                 */
pair[] V;
pair[] W;

/*  Two arrays for the vertices centered around the origin.                   */
pair[] Hex0;
pair[] Hex1;

/*  The angle made with the x axis and the first point.                       */
real theta = pi / 6.0;

/*  Precompute sine and cosine of this angle to save redundant computations.  */
real sin_theta = sin(theta);
real cos_theta = cos(theta);

/*  Radius of the outer hexagon.                                              */
real r0 = 1.0;

/*  Radius of the inner hexagon. This length is determined by the outter      *
 *  since we want the graph to create a regular tiling of hexagons.           */
real r1 = r0*cos_theta / (1.0 + sin_theta);

/*  Radius of a circle used to indicate a point.                              */
real rDot = 0.06;

/*  Point for the origin.                                                     */
pair O = (0.0, 0.0);

/*  Size of arrow heads.                                                      */
real arsize = 4bp;

/*  Width of the outter hexagon.                                              */
real outter_width = r0*cos_theta;

/*  Shift factors used to tile the plane with hexagons.                       */
pair dx = (2.0*outter_width, 0.0);
pair ds = scale(2.0*outter_width)*expi(0.6666667*pi);

/*  Dashed pen for the k_3,3 graph.                                           */
pen dpen = black + linewidth(0.3pt) + linetype("4 4");

/*  Transform used for shifting later.                                        */
transform T;

/*  Compute the locations of the two starting hexagons.                       */
for (k = 0; k < 6; ++k)
{
    Hex0[k] = T*(scale(r0)*expi(theta + 0.33333*pi*k));
    Hex1[k] = T*(scale(r1)*expi(0.33333*pi*k));
}

/*  Loop through all of the hexagons.                                         */
for (m = 0; m < N; ++m)
{
    for (n = 0; n < N; ++n)
    {
        /*  Compute the current shift factor.                                 */
        T = shift(scale(m)*dx + scale(n)*ds);

        /*  Compute the locations of the points on both hexagons.             */
        for (k = 0; k < 6; ++k)
        {
            V[k] = T*Hex0[k];
            W[k] = T*Hex1[k];
            draw(T*O -- V[k]);
        }

        /*  Draw the lines for K_3,3.                                         */
        draw(W[0] -- MidPoint2D(V[5], V[0]), dpen);
        draw(W[1] -- MidPoint2D(V[0], V[1]), dpen);
        draw(W[2] -- MidPoint2D(V[1], V[2]), dpen);
        draw(W[3] -- MidPoint2D(V[2], V[3]), dpen);
        draw(W[4] -- MidPoint2D(V[3], V[4]), dpen);
        draw(W[5] -- MidPoint2D(V[4], V[5]), dpen);
        draw(W[0] -- W[1] -- W[2] -- W[3] -- W[4] -- W[5] -- cycle, dpen);

        /*  Draw lines representing the glueing of the hexagon.               */
        draw(V[0] -- V[1], red, MidSharpArrow(arsize));
        draw(V[4] -- V[3], red, MidSharpArrow(arsize));
        draw(V[1] -- V[2], green, MidSharpArrow(arsize));
        draw(V[5] -- V[4], green, MidSharpArrow(arsize));
        draw(V[3] -- V[2], blue, MidSharpArrow(arsize));
        draw(V[5] -- V[0], blue, MidSharpArrow(arsize));

        /*  To show that this is K_3,3, draw the "top" and "bottom" different.*/
        filldraw(circle(W[0], rDot), gray(0.3), black);
        filldraw(circle(W[2], rDot), gray(0.3), black);
        filldraw(circle(W[4], rDot), gray(0.3), black);
        filldraw(circle(W[1], rDot), gray(0.7), black);
        filldraw(circle(W[3], rDot), gray(0.7), black);
        filldraw(circle(W[5], rDot), gray(0.7), black);

        /*  Points for the dual graph. Some are in the corners of the hexagon *
         *  so you only see a "third" of the point.                           */
        filldraw(circle(T*O, rDot), yellow, black);
        filldraw(circle(V[0], rDot), cyan, black);
        filldraw(circle(V[2], rDot), cyan, black);
        filldraw(circle(V[4], rDot), cyan, black);
        filldraw(circle(V[1], rDot), magenta, black);
        filldraw(circle(V[3], rDot), magenta, black);
        filldraw(circle(V[5], rDot), magenta, black);
    }
}

/*  Clip the picture so it fits into a square drawing.                        */
clip((0.0, 0.0) -- (r0*N, 0.0) -- (r0*N, r0*N) -- (0.0, r0*N) -- cycle);
