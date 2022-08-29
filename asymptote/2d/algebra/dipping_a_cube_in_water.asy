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
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Draws the intersection of a plane with a cube, revealing a hexagon.   *
 *      This is what you'd get if you dipped a cube into water with one of    *
 *      vertices of the cube facing down.                                     *
 ******************************************************************************/

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(128);

/*  Default pen for drawings.                                                 */
defaultpen(black + linewidth(0.5pt));

/*  Other pens used.                                                          */
pen dashp = defaultpen + linetype("4 4");
pen thinp = black + linewidth(0.1pt);
pen bluep = blue + linewidth(0.5pt);
pen thindashp = thinp + linetype("4 4");
pen bluedashp = bluep + linetype("4 4");
pen greendashp = green + linewidth(0.4pt) + linetype("4 4");

/*  Function for making 3D drawings with 2D points.                           */
pair xyzpoint(real x, real y, real z)
{
    pair X = (-0.4*x, -0.4*x);
    pair Y = (y, 0.0);
    pair Z = (0.0, z);
    return X + Y + Z;
}
/*  End of xyzpoint.                                                          */

/*  Coordinates for all of the points in the cube.                            */
pair O = xyzpoint(0, 0, 0);
pair x = xyzpoint(6, 0, 0);
pair y = xyzpoint(0, 6, 0);
pair z = xyzpoint(0, 0, 6);
pair xy = xyzpoint(6, 6, 0);
pair xz = xyzpoint(6, 0, 6);
pair yz = xyzpoint(0, 6, 6);
pair xyz = xyzpoint(6, 6, 6);
pair MID = xyzpoint(3, 3, 3);
pair a1 = xyzpoint(3, 0, 6);
pair a2 = xyzpoint(3, 6, 6);
pair a3 = xyzpoint(0, 3, 6);
pair a4 = xyzpoint(6, 3, 6);
pair b1 = xyzpoint(0, 0, 3);
pair b2 = xyzpoint(6, 0, 3);
pair b3 = a1;
pair b4 = xyzpoint(3, 0, 0);
pair c1 = b2;
pair c2 = xyzpoint(6, 6, 3);
pair c3 = a4;
pair c4 = xyzpoint(6, 3, 0);
pair d1 = xyzpoint(0, 6, 3);
pair d2 = c2;
pair d3 = a2;
pair d4 = xyzpoint(3, 6, 0);
pair e1 = a3;
pair e2 = xyzpoint(0, 3, 0);
pair e3 = b1;
pair e4 = d1;
pair f1 = e2;
pair f2 = c4;
pair f3 = b4;
pair f4 = d4;
pair A = xyzpoint(3, 3, 6);
pair B = xyzpoint(3, 0, 3);
pair C = xyzpoint(6, 3, 3);
pair D = xyzpoint(3, 6, 3);
pair E = xyzpoint(0, 3, 3);
pair F = xyzpoint(3, 3, 0);

/*  Draw the back of the cube.                                                */
draw(O -- x, dashp);
draw(O -- y, dashp);
draw(O -- z, dashp);

/*  Thin lines that make crosses on each of the outer faces.                  */
draw(a1 -- a2, thinp);
draw(a3 -- a4, thinp);
draw(c1 -- c2, thinp);
draw(c3 -- c4, thinp);
draw(d1 -- d2, thinp);
draw(d3 -- d4, thinp);

/*  Dashed lines that makes crosses on each of the inner faces.               */
draw(b1 -- b2, thindashp);
draw(b3 -- b4, thindashp);
draw(e1 -- e2, thindashp);
draw(e3 -- e4, thindashp);
draw(f1 -- f2, thindashp);
draw(f3 -- f4, thindashp);

/*  Dashed lines on the inside of the cube connecting the centers of the      *
 *  faces to the center of the cube.                                          */
draw(A -- MID, thindashp);
draw(B -- MID, thindashp);
draw(C -- MID, thindashp);
draw(D -- MID, thindashp);
draw(E -- MID, thindashp);
draw(F -- MID, thindashp);

/*  Draw the hexagon.                                                         */
draw(a1 -- a3, bluep);
draw(a3 -- d1, bluedashp);
draw(d1 -- d4, bluep);
draw(d4 -- c4, bluedashp);
draw(c4 -- b2, bluep);
draw(b2 -- a1, bluedashp);

/*  Draw the spokes of the hexagon.                                           */
draw(a1 -- MID, greendashp);
draw(a3 -- MID, greendashp);
draw(d1 -- MID, greendashp);
draw(c4 -- MID, greendashp);
draw(d4 -- MID, greendashp);
draw(b2 -- MID, greendashp);

/*  Draw the front of the cube.                                               */
draw(x -- xy);
draw(y -- xy);
draw(x -- xz);
draw(z -- xz);
draw(y -- yz);
draw(z -- yz);
draw(xy -- xyz);
draw(yz -- xyz);
draw(xz -- xyz);
