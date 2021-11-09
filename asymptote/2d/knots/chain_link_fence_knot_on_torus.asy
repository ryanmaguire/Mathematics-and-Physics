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

/*  PDF works best in LaTeX, so use this.                                     */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(256);

/*  The five vertices of K_5.                                                 */
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

/*  Default pen used for the link.                                            */
defaultpen(black + linewidth(0.4pt));

/*  Thick pen for the torus.                                                  */
pen thickp = black + linewidth(0.8pt);

/*  Dashed pen for lines that go behind the torus.                            */
pen dashp = black + linewidth(0.4pt) + linetype("4 4");

path g1, g2, g3, g4;

g1 = (0.95, -0.2) .. (0.9, 0.0) .. (1.0, 0.05){E};
g2 = (1.0, 0.05){E} .. (1.2, 0.0) .. (1.8, 0.3) .. (1.0, 0.7){W};
g3 = (1.0, 0.7){W} .. (0.2, 0.3) .. (0.8, 0.0) .. (1.1, 0.0) .. (1.05, 0.2);

draw(g1);
draw(g3, white + linewidth(4.0pt));
draw(g3);
filldraw(circle((1.12, 0.024), 0.02), white, white);
draw(g2);

draw((0.95, -0.2) -- (1.05, 0.2), dashp);

/*  Draw the torus.                                                           */
draw(A0{SE} .. A1{E} .. A2{NE}, thickp);
draw(B0{NE} .. B1 .. B2{SE}, thickp);
draw(C0{W} .. C1{NW} .. C2 .. C3{SW} .. cycle, thickp);
