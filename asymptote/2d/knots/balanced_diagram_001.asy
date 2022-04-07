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

/*  Size of the figure.                                                       */
size(128);

/*  Pen for the rectangles.                                                   */
pen rectpen = green + linewidth(0.7pt);

/*  Pen for the arrows.                                                       */
pen arpen = black + linewidth(0.5pt);
pen whiteout = white + linewidth(2.5pt);

/*  Margins for the arrows. This gives a bit of white "buffer" space.         */
margin margins = TrueMargin(0.2cm, 0.2cm);

/*  Size of the arrow heads.                                                  */
real arsize = 5bp;

/*  Distances for the rectangles.                                             */
draw(arc((0.0, 0.0), 0.8, 0.0, 180.0), blue, MidArrow(arsize));
draw(arc((0.0, 0.0), 0.8, 180.0, 360.0), blue, MidArrow(arsize));

path A = (-0.6, 0.0) .. (-1.3, 0.5) .. (-1.6, -0.5) ..
         (-1.0, -1.0) .. (1.0, -1.0) .. (1.5, 0.0) .. (1.0, 1.0) ..
         (-1.0, 1.0) .. (-1.6, 0.5) ..  (-1.3, -0.5) .. cycle;

path B = (0.3, 0.0) .. (1.1, 0.3) .. (1.3, 0.0) .. (1.3, -1.2) .. (1.6, 0.0) ..
         (1.3, 1.2) .. (1.3, 0.0) .. (1.1, -0.3) .. cycle;

B = reverse(B);

draw(subpath(B, -0.5, 1.0), whiteout);
draw(subpath(B, -0.57, 5.1), green, MidArrow(arsize));
draw(subpath(B, 5.1, 5.94), green, MidArrow(arsize));
draw(subpath(B, 6.18, 7.33), green, MidArrow(arsize));
draw(subpath(A, -0.2, 5.2), whiteout);
draw(subpath(A, -0.32, 5.88), red, MidArrow(arsize));
draw(subpath(A, 6.0, 8.3), red, MidArrow(arsize));
draw(subpath(A, 8.5, 9.58), red, MidArrow(arsize));
