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

/*  Pen for filling in the sphere.                                            */
pen fpen = gray(0.7) + opacity(0.5);

/*  Pen for drawing axes.                                                     */
pen apen = black + linewidth(1.0pt);

/*  Normal drawing pen.                                                       */
pen cpen = black + linewidth(0.5pt);

/*  Pen for drawing dashed lines.                                             */
pen dpen = black + linewidth(0.3pt) + dashed;

/*  Points for the origin and the point on the sphere.                        */
pair O = (0.0, 0.0);
pair A = (1.0, 2.0);

/*  Radius of the drawing.                                                    */
real R = 1.4;

/*  Radius for a dot indicating a point.                                      */
real rDot = 0.02;

/*  Radius of the sphere.                                                     */
real sphere_radius = 1.0;

/*  Radius of the arc of circle used to represent an angle.                   */
real thetar = 0.15;

/*  The scale factor used to draw an arc of an ellipse to represent the       *
 *  equator in the sphere.                                                    */
real yscale = 0.5;

/*  Eccentricity factor for drawing the prime meridian in the sphere.         */
real escale = sqrt(2.0*yscale*yscale / (1.0 + yscale*yscale));

/*  Size of an arrow.                                                         */
real arsize = 5bp;
real small_arr = 4bp;

/*  Default font size for labels.                                             */
real fsize = 7pt;

/*  Smaller font size for smaller labels.                                     */
real fsize2 = 5pt;

/*  Margins to prevent lines and arcs from overlapping labels.                */
margin margins = TrueMargin(0.0, 0.07cm);

/*  These 2D points help mimic a 3D Cartesian coordinate system.              */
pair X = (-0.7071067811865476, -0.7071067811865476);
pair Y = (1.0, 0.0);
pair Z = (0.0, 1.0);

/*  Function for mimicing 3D drawings with 2D vectors.                        */
pair xyzpoint(real x, real y, real z)
{
    return scale(x)*X + scale(y)*Y + scale(z)*Z;
}
/*  End of xyzpoint.                                                          */

/*  Inverse Stereographic projection from the plane to the unit sphere.       */
pair Plane2Sphere(pair P)
{
    /*  To compute the factors for stereographic projection we solve where    *
     *  the line passing through (0, 0, 1) and (x, y, z) hits the xy-plane.   *
     *  Inverse stereographic projection goes in reverse, from the plane back *
     *  to the sphere via the same line.                                      */
    real w = 1.0 + P.x*P.x + P.y*P.y;
    real rcpr_w = 1.0 / w;
    real u = 2.0*P.x*rcpr_w;
    real v = 2.0*P.y*rcpr_w;
    w = (w - 2.0)/w;
    return xyzpoint(u, v, w);
}
/*  End of Plane2Sphere.                                                      */

/*  Function for computing the orthgraphic projection of the point on the     *
 *  unit sphere corresponding to the inverse stereographic projection of a    *
 *  given point in the plane.                                                 */
pair Plane2Plane(pair P)
{
    /*  Same procedure as inverse stereographic projection, but set the z     *
     *  term to zero.                                                         */
    real w = 1.0 + P.x*P.x + P.y*P.y;
    real rcpr_w = 1.0 / w;
    real u = 2.0*P.x*rcpr_w;
    real v = 2.0*P.y*rcpr_w;
    return xyzpoint(u, v, 0.0);
}
/*  End of Plane2Plane.                                                       */

/*  Function for projecting a point down the x-axis in 3D coordinates.        */
pair XProj(pair U)
{
    real u = U.y;
    real v = U.y;
    return (u, v);
}
/*  End of XProj.                                                             */

/*  Function for projection down the y-axis in 3D coordinates.                */
pair YProj(pair U)
{
    real u = U.x - U.y;
    real v = 0.0;
    return (u, v);
}
/*  End of YProj.                                                             */

/*  Function for computing the zenith angle of a point in the xy-plane.       */
real ZenithAngle(pair P)
{
    real w = 1.0 + P.x*P.x + P.y*P.y;
    real rcpr_w = 1.0 / w;
    real u = 2.0*P.x*rcpr_w;
    real v = 2.0*P.y*rcpr_w;
    real rho = sqrt(u*u + v*v);
    w = (w-2.0)/w;

    /*  The value 180/pi is roughly 57.29577951308232. Most drawing functions *
     *  unfortunately want angles in degrees.                                 */
    return 57.29577951308232*atan(rho/w);
}
/*  End of ZenithAngle.                                                       */

/*  Compute the point on the sphere from the given point in the plane, and    *
 *  compute the projection onto the unit disk in the xy-plane.                */
pair PointOnSphere = Plane2Sphere(A);
pair PointOnPlane = Plane2Plane(A);

/*  Get the angle this point makes in the plane.                              */
real theta = ZenithAngle(A);

/*  Points for drawing the three axes.                                        */
pair XEnd = scale(R)*X;
pair YEnd = scale(R)*Y;
pair ZEnd = scale(R)*Z;

/*  Point on the equator to later indicate the radius of the sphere.          */
pair Equator = scale(escale)*(-X.x, X.y);

/*  And a point for the prime meridian.                                       */
pair PrimeMeridian = scale(escale)*X;

/*  Labels for the axes.                                                      */
Label X_Label = Label("$x$", position=1.0, SW, fontsize(fsize));
Label Y_Label = Label("$y$", position=1.0, E, fontsize(fsize));
Label Z_Label = Label("$z$", position=1.0, N, fontsize(fsize));

/*  Draw the axes.                                                            */
draw(X_Label, O -- XEnd, apen, SharpArrow(arsize));
draw(Y_Label, O -- YEnd, apen, SharpArrow(arsize));
draw(Z_Label, O -- ZEnd, apen, SharpArrow(arsize));

/*  Draw dashed lines to indicate where the point is in the xy-plane.         */
draw(PointOnPlane -- XProj(PointOnPlane), dpen);
draw(PointOnPlane -- YProj(PointOnPlane), dpen);

/*  And drop a perpendicular dashed line to indicate the z component.         */
draw(PointOnSphere -- PointOnPlane, dpen);

/*  Draw a dashed line from the origin to the xy projection to show the angle.*/
draw(O -- PointOnPlane, dpen);

/*  A label for the radius of the sphere, which is "a" in the problem.        */
Label Equator_Label = Label("$a$", position=0.7, W, fontsize(fsize2));

/*  Draw and label a line from the origin to the equator.                     */
draw(Equator_Label, O -- Equator, cpen);

/*  Fill in the spherical region.                                             */
filldraw(circle(O, sphere_radius), fpen, cpen);

/*  Draw the equator.                                                         */
draw(scale(1.0, yscale)*arc(O, sphere_radius, 180, 360), cpen);

/*  Draw the prime meridian.                                                  */
draw(Z{X} .. PrimeMeridian{S}, cpen);

/*  Label for the position and velocity vectors.                              */
Label Pos_Label = Label("$\mathbf{r}$", position=0.4, N, fontsize(fsize));
Label Vec_Label = Label("$\mathbf{v}$", position=0.4, W, fontsize(fsize));

/*  Draw the position and velocity vectors.                                   */
draw(Pos_Label, O -- PointOnSphere, cpen + blue,
     SharpArrow(StealthHead, small_arr), margins);
draw(Vec_Label, PointOnSphere -- (PointOnSphere+(0.2, 0.3)), cpen + red,
     SharpArrow(StealthHead, small_arr), margins);

/*  Draw a dot for the point of interest.                                     */
filldraw(circle(PointOnSphere, rDot), black);

/*  Draw and label the angle.                                                 */
Label Theta_Label = Label("$\theta$", position=0.7, N, fontsize(fsize2));
draw(Theta_Label, arc(O, thetar, 90, theta), cpen);

/*  Label the charge on the sphere Q.                                         */
label("$Q$", (-0.5, 0.7), fontsize(fsize));
