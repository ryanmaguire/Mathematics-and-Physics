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

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(128);

pair C1 = (-1.3, 0.0);
pair C2 = (1.3, 0.0);
pair A = (-1.6, 1.4);
pair B = (1.6, 1.4);
pair U = (0.0, 3.1);

pair R0 = (-4.5, 3.6);
pair R1 = (4.5, 3.6);
pair R2 = (4.5, -3.6);
pair R3 = (-4.5, -3.6);
real r = 2.6;

draw(R0 -- R1 -- R2 -- R3 -- cycle);
filldraw(circle(C2, r), cyan, invisible);
filldraw(circle(C1, r), white, invisible);
draw(circle(C1, r), black);
draw(circle(C2, r), black);

label("$A$", A);
label("$B$", B);
label("$B\setminus{A}$", U);
