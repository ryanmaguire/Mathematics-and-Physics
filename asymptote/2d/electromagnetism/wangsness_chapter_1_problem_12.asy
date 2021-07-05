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

/*  Size of the figure.                                                       */
size(128);

/*  Default pen used for the axes and labels.                                 */
defaultpen(linewidth(0.7pt) + fontsize(7pt));

/*  Pens for drawing arrows.                                                  */
pen redpen = linewidth(0.7pt) + red;
pen bluepen = linewidth(0.7pt) + blue;

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
    /*  Pairs for the points. The help convert from 2D coordinates to 3D.     */
    pair X = (-0.7071067811865476, -0.7071067811865476);
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

/*  Points on the sphere.                                                     */
pair P0 = scale(r)*X;
pair P1 = scale(r)*Y;

/*  The point of interest on the sphere.                                      */
pair Q = (0.2, 0.2);

/*  Path for the sphere.                                                      */
path g = arc(O, r, 0.0, 90.0){SW} .. {S}P0{E} .. P1{NE} -- cycle;

/*  Pen for filling in the sphere.                                            */
pen fillp = grey + opacity(0.5);

/*  Pairs for displacements to create the infinitesimal area.                 */
pair dx = (0.05, 0.00);
pair ds = (0.035, 0.035);

/*  Endpoints for the two arrows.                                             */
pair A_Start = Q + scale(0.5)*(dx + ds);
pair Z_End = A_Start + (0.0, arlength);
pair N_End = A_Start + scale(arlength)*expi(0.25*pi);

/*  Labels for the arrows.                                                    */
Label Z_Label = Label("$\hat{\mathbf{z}}$", position=1.0);
Label N_Label = Label("$\hat{\mathbf{n}}$", position=1.0);

/*  Draw the coordinate axes.                                                 */
draw(Label("$x$", position=1.0), O -- X, SW, SharpArrow(arsize));
draw(Label("$y$", position=1.0), O -- Y, E, SharpArrow(arsize));
draw(Label("$z$", position=1.0), O -- Z, N, SharpArrow(arsize));

/*  Color in the sphere.                                                      */
filldraw(g, fillp, black);

/*  Draw an arrow for the z direction.                                        */
draw(Z_Label, A_Start -- Z_End, redpen, SharpArrow(arsize));

/*  Draw an arrow for the normal.                                             */
draw(N_Label, A_Start -- N_End, bluepen, SharpArrow(arsize));

/*  Draw the infinitesimal area.                                              */
filldraw(Q -- (Q+dx) -- (Q+dx+ds) -- (Q+ds) -- cycle, rectpen);

/*  Label the infinitesimal area.                                             */
label("$\textrm{d}a$", A_Start, S, fontsize(small_font));
