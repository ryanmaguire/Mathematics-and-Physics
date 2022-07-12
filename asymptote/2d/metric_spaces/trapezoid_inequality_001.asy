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

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(256);

pair A = (0.0, 0.0);
pair B = (0.3, 1.5);
pair C = (2.1, 0.1);
pair D = (1.8, 1.4);

draw(rotate(180.0*atan(B.y/B.x)/pi)*"$d(a,\,b)$", A -- B, W);
draw(rotate(180.0*atan(C.y/C.x)/pi)*"$d(a,\,c)$", A -- C);
draw(rotate(180.0*atan((D.y-B.y)/(D.x-B.x))/pi)*"$d(b,\,d)$", B -- D, N);
draw(rotate(180.0*atan(B.y/B.x)/pi)*"$d(a,\,b)$", A -- B, W);
draw(rotate(180.0*atan((D.y-C.y)/(D.x-C.x))/pi)*"$d(c,\,d)$", C -- D, E);
label("$a$", A, SW);
label("$b$", B, NW);
label("$c$", C, SE);
label("$d$", D, NE);
