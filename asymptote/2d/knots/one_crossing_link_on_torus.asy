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

draw((1.0, 0.0){E} .. (1.8, 0.3) .. (1.0, 0.7) .. (0.2, 0.3) .. cycle{E});
draw((1.0, 0.2){E} .. (1.1, 0.0) .. (1.0, -0.2){W}, white+linewidth(4.0pt));
draw((1.0, 0.2){E} .. (1.1, 0.0) .. (1.0, -0.2){W});
draw((1.0, -0.2){W} .. (0.9, 0.0) .. (1.0, 0.2){E}, dashp);

/*  Draw the torus.                                                           */
draw(A0{SE} .. A1{E} .. A2{NE}, thickp);
draw(B0{NE} .. B1 .. B2{SE}, thickp);
draw(C0{W} .. C1{NW} .. C2 .. C3{SW} .. cycle, thickp);
