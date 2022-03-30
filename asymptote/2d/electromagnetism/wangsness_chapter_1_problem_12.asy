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

/*  Needed for drawing the sphere.                                            */
import graph;

/*  The opacity will not render correctly for EPS format, so use PDF.         */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(128);

/*  Default pen used for the axes and labels.                                 */
defaultpen(linewidth(0.7pt) + fontsize(7pt));

/*  Pens for drawing arrows.                                                  */
pen redpen = linewidth(0.7pt) + red;
pen bluepen = linewidth(0.7pt) + blue;

/*  Pens for radial shading.                                                  */
pen rpen0 = white + opacity(0.5);
pen rpen1 = black + opacity(0.5);

/*  Center for the radial shading.                                            */
pair C = (-0.04, 0.3);

/*  Pen for the infinitesimal area.                                           */
pen rectpen = orange;

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  Length of the arrows for the normal and z components.                     */
real arlength = 0.2;

/*  Fontsize for smaller labels.                                              */
real small_font = 5pt;

/*  Function for creating a 2D projection of a 3D point to give the illusion  *
 *  of a 3D drawing.                                                          */
pair xyzpoint(real x, real y, real z)
{
    /*  Pairs for the points. They help convert from 2D coordinates to 3D.    */
    pair X = (-0.5, -0.5);
    pair Y = (1.0, 0.0);
    pair Z = (0.0, 1.0);

    /*  Project (x, y, z) onto the 2D plane using the values above.           */
    return scale(x)*X + scale(y)*Y + scale(z)*Z;
}
/*  End of xyzpoint.                                                          */

/*  Points for the three axes.                                                */
pair X = xyzpoint(1.0, 0.0, 0.0);
pair Y = xyzpoint(0.0, 1.0, 0.0);
pair Z = xyzpoint(0.0, 0.0, 1.0);

/*  And a point for the origin.                                               */
pair O = (0.0, 0.0);

/*  Radius of the sphere.                                                     */
real r = 0.7;

/*  Function for drawing the three arcs of the sphere.                        */
pair sphere_arcs(real t)
{
    /*  Angle for different parts of the curve.                               */
    real theta;

    /*  The sphere consists of 3 arcs which will be drawn using the           *
     *  projection function xyzpoint above.                                   */
    if (t < 0.0)
        return scale(r)*xyzpoint(0.0, 1.0, 0.0);
    else if (t < 1.0)
    {
        theta = 0.5*pi*t;
        return scale(r)*xyzpoint(0.0, cos(theta), sin(theta));
    }
    else if (t < 2.0)
    {
        theta = 0.5*pi*(t - 1.0);
        return scale(r)*xyzpoint(sin(theta), 0.0, cos(theta));
    }
    else if (t < 3.0)
    {
        theta = 0.5*pi*(t - 2.0);
        return scale(r)*xyzpoint(cos(theta), sin(theta), 0.0);
    }
    else
        return scale(r)*xyzpoint(0.0, 1.0, 0.0);
}
/*  End of sphere_arcs.                                                       */

/*  Number of samples for the sphere.                                         */
int n_samples = 120;

/*  The point of interest on the sphere.                                      */
pair Q = (0.2, 0.2);

/*  Pairs for displacements to create the infinitesimal area.                 */
pair dx = (0.05, 0.00);
pair ds = (0.035, 0.035);

/*  Endpoints for the two arrows.                                             */
pair A_Start = Q + scale(0.5)*(dx + ds);
pair Z_End = A_Start + (0.0, arlength);
pair N_End = A_Start + scale(arlength)*expi(0.25*pi);

/*  Path for the arc.                                                         */
path g = graph(sphere_arcs, 0.0, 3.0, n_samples);

/*  Labels for the arrows.                                                    */
Label Z_Label = Label("$\hat{\mathbf{z}}$", position=1.0);
Label N_Label = Label("$\hat{\mathbf{n}}$", position=1.0);

/*  Draw the coordinate axes.                                                 */
draw(Label("$x$", position=1.0), O -- X, SW, SharpArrow(arsize));
draw(Label("$y$", position=1.0), O -- Y, E, SharpArrow(arsize));
draw(Label("$z$", position=1.0), O -- Z, N, SharpArrow(arsize));

/*  Color in the sphere.                                                      */
radialshade(g -- cycle, rpen0, C, 0.0, rpen1, C, r);

/*  Draw the outline of the sphere.                                           */
draw(g -- cycle);

/*  Draw an arrow for the z direction.                                        */
draw(Z_Label, A_Start -- Z_End, redpen, SharpArrow(arsize));

/*  Draw an arrow for the normal.                                             */
draw(N_Label, A_Start -- N_End, bluepen, SharpArrow(arsize));

/*  Draw the infinitesimal area.                                              */
filldraw(Q -- (Q+dx) -- (Q+dx+ds) -- (Q+ds) -- cycle, rectpen);

/*  Label the infinitesimal area.                                             */
label("$\textrm{d}a$", A_Start, scale(2.0)*S, fontsize(small_font));
