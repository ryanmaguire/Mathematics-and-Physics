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

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output.                                                       */
size(128);

/*  Pen for drawing.                                                          */
pen dpen = red + 0.5*white + linewidth(0.8pt) + linetype("4 4");
pen cpen = black + linewidth(0.8pt);

/*  Radius of dots.                                                           */
real r = 0.03;

/*  Font size for labels.                                                     */
real fsize = 8pt;

/*  Radii of the ellipse.                                                     */
real rx = 0.22;
real ry = 0.15;

/*  Lengths of the sides of the cube.                                         */
real length = 2.0;

/*  Function for creating a 2D projection of a 3D point to give the illusion  *
 *  of a 3D drawing.                                                          */
pair xyzpoint(real x, real y, real z)
{
    /*  Pairs for the points. The help convert from 2D coordinates to 3D.     */
    pair X = (sqrt(0.5), -sqrt(0.5));
    pair Y = (1.0, 0.0);
    pair Z = (0.0, 1.0);

    /*  Project (x, y, z) onto the 2D plane using the values above.           */
    return scale(x)*X + scale(y)*Y + scale(z)*Z;
}
/*  End of xyzpoint.                                                          */

/*  Get the 8 points on the cube.                                             */
pair O = xyzpoint(0.0, 0.0, 0.0);
pair x0 = xyzpoint(length, 0.0, 0.0);
pair y0 = xyzpoint(0.0, length, 0.0);
pair xy0 = xyzpoint(length, length, 0.0);
pair t = xyzpoint(0.0, 0.0, length);
pair x1 = xyzpoint(length, 0.0, length);
pair y1 = xyzpoint(0.0, length, length);
pair xy1 = xyzpoint(length, length, length);

/*  Get the centers of the top and bottom faces.                              */
pair center0 = xyzpoint(0.5*length, 0.5*length, 0.0);
pair center1 = xyzpoint(0.5*length, 0.5*length, length);

/*  Draw all of the edges of the cube.                                        */
draw(O -- x0, dpen);
draw(O -- y0, dpen);
draw(x0 -- xy0, dpen);
draw(y0 -- xy0, dpen);
draw(x0 -- x1, dpen);
draw(y0 -- y1, dpen);
draw(xy0 -- xy1, dpen);
draw(O -- t, dpen);
draw(O -- x0, dpen);
draw(O -- x0, dpen);
draw(O -- x0, dpen);
draw(t -- x1, dpen);
draw(t -- y1, dpen);
draw(x1 -- xy1, dpen);
draw(y1 -- xy1, dpen);

/*  Draw in the 8 vertices of the cube.                                       */
filldraw(circle(O, r), black, black);
filldraw(circle(x0, r), black, black);
filldraw(circle(y0, r), black, black);
filldraw(circle(xy0, r), black, black);
filldraw(circle(t, r), black, black);
filldraw(circle(x1, r), black, black);
filldraw(circle(y1, r), black, black);
filldraw(circle(xy1, r), black, black);

/*  Draw the top and bottom of the cylinder.                                  */
draw(ellipse(center0, rx, ry), cpen);
draw(ellipse(center1, rx, ry), cpen);

/*  Draw the edges of the cylinder.                                           */
draw((center0 - (rx, 0.0)) -- (center1 - (rx, 0.0)), cpen);
draw((center0 + (rx, 0.0)) -- (center1 + (rx, 0.0)), cpen);

/*  Label everything.                                                         */
label("$A$", center1, fontsize(fsize));
label("$x$", x0, SW, fontsize(fsize));
label("$y$", y0, E, fontsize(fsize));
label("$t$", t,  W, fontsize(fsize));
