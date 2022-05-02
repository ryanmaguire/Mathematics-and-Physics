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
 *      Draw the planes representing the standard contact structure on R^3.   *
 ******************************************************************************/

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(512);

/*  Default size of arrowheads.                                               */
real arsize = 5bp;

/*  Pen for drawing axes.                                                     */
pen axesp = black + linewidth(1.0pt) + fontsize(12pt);

/*  Variables for looping over points in the xy plane.                        */
real x, y;

/*  Start and end values for x and y values in the xy plane.                  */
real start = -2.0;
real end = -start;

/*  Size of the displacement in both the x and y axes.                        */
real ds = 1.0/6.0;

/*  Size of the displacement in the z-direction. Used for drawing planes.     */
real dz = 0.1;

/*  Function for making 3D drawings with 2D points.                           */
pair xyzpoint(real a, real b, real c)
{
    pair X = (-0.4*a, -0.4*a);
    pair Y = (b, 0.0);
    pair Z = (0.0, c);
    return X + Y + Z;
}
/*  End of xyzpoint.                                                          */

/*  Function for drawing the plane representing the contact structure at the  *
 *  point (x, y, z). The is the kernel of dz - ydx = 0.                       */
void draw_rectangle(real a, real b, real c)
{
    /*  The center of the rectangle is given by the input ordered triple.     */
    pair center = xyzpoint(a, b, c);

    /*  Two orthogonal vectors in the kernel of the one-form dz - ydx are     *
     *  (1, 0, y) and (0, 1, 0). We'll use these as the basis vectors for our *
     *  plane containing the point (a, b, c).                                 */
    pair dx1 = xyzpoint(ds, 0.0, y*dz);
    pair dx2 = xyzpoint(0.0, ds, 0.0);

    /*  Four points defining the plane.                                       */
    pair A0 = center + dx1 + dx2;
    pair A1 = center + dx1 - dx2;
    pair A2 = center - dx1 - dx2;
    pair A3 = center - dx1 + dx2;

    /*  Give a gradient based on the y coordinate to give the illusion of a   *
     *  shadow being cast on the hyperplanes.                                 */
    real lambda = (y - start)/(end - start);
    pen grayp = gray(0.8*(1.0 - lambda) + 0.5*lambda);

    /*  Draw in a parallelagram representing the plane.                       */
    filldraw(A0 -- A1 -- A2 -- A3 -- cycle, grayp, black);
}
/*  End of draw_rectangle.                                                    */

/*  Points for the axes and the origin.                                       */
pair O = xyzpoint(0.0, 0.0, 0.0);
pair X0 = xyzpoint(-3.0, 0.0, 0.0);
pair X1 = xyzpoint(3.0, 0.0, 0.0);
pair Y0 = xyzpoint(0.0, -3.0, 0.0);
pair Y1 = xyzpoint(0.0, 3.0, 0.0);
pair Z0 = xyzpoint(0.0, 0.0, -1.3);
pair Z1 = xyzpoint(0.0, 0.0, 1.3);

/*  Draw the bottom half of the z axis. This way the planes will be drawn on  *
 *  top of it.                                                                */
draw(O -- Z0, axesp, SharpArrow(arsize));

/*  Loop through points in the xy plane and draw the planes representing the  *
 *  contact structure at each point.                                          */
for (x = start; x <= end; x += 3.0*ds)
    for (y = start; y <= end; y += 3.0*ds)
            draw_rectangle(x, y, 0.0);

/*  Draw the other axes and label them.                                       */
draw(Label("$x$", position=1.0), X0 -- X1, axesp, SharpArrows(arsize));
draw(Label("$y$", position=1.0), Y0 -- Y1, axesp, SharpArrows(arsize));
draw(Label("$z$", position=1.0), O -- Z1, axesp, SharpArrow(arsize));
