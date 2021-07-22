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
size(128);

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

/*  Variable for indexing.                                                    */
int k;

/*  Two arrays for vertices in the inner and outter hexagons.                 */
pair[] V;
pair[] W;

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
real rDot = 0.03;

/*  Size of arrow heads.                                                      */
real arsize = 4bp;

/*  Width of the outter hexagon.                                              */
real outter_width = r0*cos_theta;

/*  Compute the locations of the points on both hexagons.                     */
for (k = 0; k < 6; ++k)
{
    V[k] = scale(r0)*expi(theta + 0.33333*pi*k);
    W[k] = scale(r1)*expi(0.33333*pi*k);
}

/*  Draw the lines for K_3,3.                                                 */
draw(W[0] -- MidPoint2D(V[5], V[0]));
draw(W[1] -- MidPoint2D(V[0], V[1]));
draw(W[2] -- MidPoint2D(V[1], V[2]));
draw(W[3] -- MidPoint2D(V[2], V[3]));
draw(W[4] -- MidPoint2D(V[3], V[4]));
draw(W[5] -- MidPoint2D(V[4], V[5]));
draw(W[0] -- W[1] -- W[2] -- W[3] -- W[4] -- W[5] -- cycle);

/*  Draw lines representing the glueing of the hexagon.                       */
draw(V[0] -- V[1], green, MidSharpArrow(arsize));
draw(V[4] -- V[3], green, MidSharpArrow(arsize));
draw(V[1] -- V[2], blue, MidSharpArrow(arsize));
draw(V[5] -- V[4], blue, MidSharpArrow(arsize));
draw(V[3] -- V[2], red, MidSharpArrow(arsize));
draw(V[5] -- V[0], red, MidSharpArrow(arsize));

/*  To show that this is K_3,3, draw the "top" points blue and the            *
 *  "bottom" points red.                                                      */
filldraw(circle(W[0], rDot), gray(0.3), black);
filldraw(circle(W[2], rDot), gray(0.3), black);
filldraw(circle(W[4], rDot), gray(0.3), black);
filldraw(circle(W[1], rDot), gray(0.6), black);
filldraw(circle(W[3], rDot), gray(0.6), black);
filldraw(circle(W[5], rDot), gray(0.6), black);
