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

/*  Size of the output figure.                                                */
size(256);

/*  The six vertices of K_3,3.                                                */
pair[] V;

/*  Variable for indexing.                                                    */
int n;

/*  Points for the first part of the torus.                                   */
pair A0 = (0.3, 0.4);
pair A1 = (1.0, 0.2);
pair A2 = (1.7, 0.4);

/*  Second part of the torus.                                                 */
pair B0 = (0.44, 0.3);
pair B1 = (1.0, 0.5);
pair B2 = (1.56, 0.3);

/*  Final part of the torus.                                                  */
pair C0 = (1.0, -0.2);
pair C1 = (0.0, 0.1);
pair C2 = (1.0, 0.8);
pair C3 = (2.0, 0.1);

/*  Default pen used for the K_3,3 graph.                                     */
defaultpen(black + linewidth(0.4pt));

/*  Thick pen for the torus.                                                  */
pen thickp = black + linewidth(0.8pt);

/*  Dashed pen for lines that go behind the torus.                            */
pen dashp = black + linewidth(0.4pt) + linetype("2 8");

/*  Draw the torus.                                                           */
draw(A0{SE} .. A1{E} .. A2{NE}, thickp);
draw(B0{NE} .. B1 .. B2{SE}, thickp);
draw(C0{W} .. C1{NW} .. C2 .. C3{SW} .. cycle, thickp);

/*  Get the points for K_3,3.                                                 */
V[0] = (0.85, -0.15);
V[1] = (1.0, -0.15);
V[2] = (1.15, -0.15);
V[3] = (0.85, 0.15);
V[4] = (1.0, 0.15);
V[5] = (1.15, 0.15);

/*  Place dots at the vertices.                                               */
for (n = 0; n < 6; ++n)
    dot(V[n]);

/*  Draw the edges.                                                           */
draw(V[0] -- V[3]);
draw(V[0] -- V[4]);
draw(V[1] -- V[4]);
draw(V[1] -- V[5]);
draw(V[2] -- V[5]);

/*  This edge wraps around the torus.                                         */
draw(V[5]{E} .. (1.8, 0.3) .. (1.0, 0.6) .. (0.2, 0.3) .. V[0]{E});

/*  And these two edges go around the hole to the "under" side of the torus.  */
draw(V[3] -- (0.95, 0.2));
draw((0.94, 0.2) -- (0.96, -0.2), dashp);
draw((0.96, -0.2) -- V[1]);

draw(V[3] -- (1.02, 0.2));
draw((1.02, 0.2) -- (1.05, -0.2), dashp);
draw((1.05, -0.2) -- V[2]);

draw(V[4] -- (1.06, 0.2));
draw((1.07, 0.2) -- (1.1, -0.2), dashp);
draw((1.1, -0.2) -- V[2]);
