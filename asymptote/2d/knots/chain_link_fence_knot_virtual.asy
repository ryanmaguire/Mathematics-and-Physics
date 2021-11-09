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

/*  Size of the figure.                                                       */
size(128);

pair A = (0.0, 0.0);
pair B = (0.3, 0.5);
pair C = (0.0, 1.0);

pair D = (1.0, 1.5);
pair E = (0.3, 0.0);
pair F = (0.0, 0.5);
pair G = (0.3, 1.0);
pair H = (1.0, -0.5);

draw(B -- C);
draw(C -- D);
draw(D -- E);
draw(F -- G, white + linewidth(5pt));
draw(E -- F);
draw(F -- G);
draw(G -- H);
draw(A -- B, white + linewidth(5pt));
draw(A -- B);
draw(H -- A);
draw(B -- (B + scale(0.1)*(C - B)));

draw(circle((0.53, 0.5), 0.05), black);
