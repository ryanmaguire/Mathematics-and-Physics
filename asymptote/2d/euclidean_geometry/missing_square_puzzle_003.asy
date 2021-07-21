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

/*  The opacity will not render correctly for EPS format, so use PDF.         */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(128);

/*  Pens used throughout the drawing.                                         */
pen graypen = gray(0.7) + linewidth(0.4pt);
pen outlinepen = deepblue + linewidth(0.6pt);
pen Afill = green + opacity(0.7);
pen Bfill = red + opacity(0.8);

/*  Variables used for making the grid.                                       */
int n;
int nx = 8;
int ny = 3;

/*  The bigger triangle.                                                      */
pair A1 = (0.0, 0.0);
pair A2 = (8.0, 0.0);
pair A3 = (8.0, 3.0);

/*  Smaller triangle.                                                         */
pair B1 = A1;
pair B2 = (5.0, 0.0);
pair B3 = (5.0, 2.0);

/*  Create the background grid.                                               */
for (n = 0; n <= nx; ++n)
    draw((n, -0.5) -- (n, ny + 0.5), graypen);

for (n = 0; n <= ny; ++n)
    draw((-0.5, n) -- (nx + 0.5, n), graypen);

/*  Fill in the shapes with color.                                            */
filldraw(A1 -- A2 -- A3 -- cycle, Afill, outlinepen);
filldraw(B1 -- B2 -- B3 -- cycle, Bfill, outlinepen);
