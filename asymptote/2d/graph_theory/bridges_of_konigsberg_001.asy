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

/*  Size of the figure.                                                       */
size(256);

/*  Points for the river.                                                     */
pair r0 = (0.0, 0.9);
pair r1 = (2.0, 1.2);
pair r2 = (4.0, 1.1);
pair r3 = (6.0, 1.4);
pair r4 = (6.0, -1.4);
pair r5 = (4.0, -1.1);
pair r6 = (2.0, -1.2);
pair r7 = (0.0, -0.9);

/*  Locations of the centers of the two islands.                              */
pair I0 = (2.0, 0.0);
pair I1 = (4.6, 0.3);

/*  Edges for land.                                                           */
pair G0 = (0.0, 2.0);
pair G1 = (6.0, 2.0);
pair G2 = (6.0, -2.0);
pair G3 = (0.0, -2.0);

/*  Colors for the river, grass, and bridges, respectively.                   */
pen rpen = blue + lightblue;
pen gpen = darkgreen;
pen bpen = yellow;

/*  Radii for the ellipses representing the islands.                          */
real xr0 = 0.8;
real yr0 = 0.3;
real xr1 = 1.0;
real yr1 = 0.3;

/*  Width of the bridges.                                                     */
real width = 0.15;

/*  Function for computing a unit orthogonal vector to the line AB.           */
pair get_unit_orthogonal(pair A, pair B)
{
    pair orth = (A.y - B.y, B.x - A.x);

    /*  Normalize this and return.                                            */
    return scale(1.0 / sqrt(orth.x*orth.x + orth.y*orth.y))*orth;
}
/*  End of get_unit_orthogonal.                                               */

/*  Function for drawing a bridge between two points.                         */
void draw_bridge(pair A, pair B, real bridge_width)
{
    /*  The displacement factor to give the bridge width.                     */
    pair ds = scale(0.5*bridge_width)*get_unit_orthogonal(A, B);

    /*  The four corners of the rectangular bridge.                           */
    pair B0 = A + ds;
    pair B1 = B + ds;
    pair B2 = B - ds;
    pair B3 = A - ds;

    /*  Fill in the rectangle.                                                */
    filldraw(B0 -- B1 -- B2 -- B3 -- cycle, bpen, bpen);

    /*  Draw in the length-wise edges black.                                  */
    draw(B0 -- B1);
    draw(B2 -- B3);
}
/*  End of draw_bridge.                                                       */

/*  Locations of the seven bridges.                                           */
pair B00 = (1.6, 0.2);
pair B01 = (1.0, 1.2);

pair B10 = (2.2, 0.25);
pair B11 = (2.6, 1.3);

pair B20 = (1.7, -0.2);
pair B21 = (1.0, -1.2);

pair B30 = (2.2, -0.2);
pair B31 = (2.6, -1.3);

pair B40 = (2.6, 0.1);
pair B41 = (3.8, 0.25);

pair B50 = (4.4, 0.5);
pair B51 = (4.2, 1.3);

pair B60 = (4.4, 0.1);
pair B61 = (4.2, -1.2);

/*  Draw in the grass first so that the river and bridges lie on top.         */
filldraw(G0 -- G1 -- G2 -- G3 -- cycle, gpen, black);

/*  Draw the river.                                                           */
filldraw(r0 .. r1 .. r2 .. r3 -- r4 .. r5 .. r6 .. r7 -- cycle, rpen, gpen);

/*  Draw the two islands.                                                     */
filldraw(ellipse(I0, xr0, yr0), gpen, rpen);
filldraw(ellipse(I1, xr1, yr1), gpen, rpen);

/*  Draw all of the bridges.                                                  */
draw_bridge(B00, B01, width);
draw_bridge(B10, B11, width);
draw_bridge(B20, B21, width);
draw_bridge(B30, B31, width);
draw_bridge(B40, B41, width);
draw_bridge(B50, B51, width);
draw_bridge(B60, B61, width);
