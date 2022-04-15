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
 *      Draw a genus 2 surface using an implicit definition.                  *
 ******************************************************************************/

/*  Used for rendering implicitly defined 3D objects.                         */
import smoothcontour3;

/*  PDF works best with LaTeX, output this. Also set the render factor high.  */
import settings;
settings.outformat = "pdf";
settings.render = 8;

/*  Size of the image. For 3D objects it seems best to have this set to a     *
 *  power of 2, otherwise weird vertical or horizontal black lines may appear.*/
size(256);

/*  How the image is being drawn on a 2D picture.                             */
currentprojection = perspective(5.0, 4.0, 6.0);

/*  Two radii defining the torus.                                             */
real R = 1.2;
real r = 0.5;
real a = sqrt(2.0);

/*  Squares of these parameters.                                              */
real Rsqr = R*R;
real rsqr = r*r;
real asqr = a*a;

/*  Differences, and squares of the differences.                              */
real diffsqr = Rsqr-rsqr;
real sqrdiffsqr = diffsqr*diffsqr;
real twsumsqr = 2.0*(rsqr + Rsqr);
real twdiffsqr = 2.0*diffsqr;

/*  Material the 2-genus surface is made out of.                              */
material blob = material(
    diffusepen = gray(0.7),
    emissivepen = gray(0.2),
    specularpen = gray(0.2)
);

/*  Start and end parameters for drawing the implicitly defined surface.      */
triple eps = (1.0e-2, 1.0e-2, 1.0e-2);
triple start = (-2.0*(r + R), -r - R, -r - a) + eps;
triple end = (2.0*(r + R), r + R, r + a) + eps;

/*  Implicit equation for genus-2 surface.                                    */
real f(real x, real y, real z)
{
    real ysqr = y*y;
    real zsqr = z*z;

    real p = (-r - R + x)*(-r - R + x);
    real q = (r + R + x)*(r + R + x);

    real fac1 = p + ysqr + zsqr;
    real fac2 = q + ysqr + zsqr;
    real fac3 = twdiffsqr*zsqr;

    real c = sqrdiffsqr - twsumsqr*(p + ysqr) + fac3 + fac1*fac1;
    real d = sqrdiffsqr - twsumsqr*(q + ysqr) + fac3 + fac2*fac2;

    return -asqr + c*d;
}
/*  End of f.                                                                 */

/*  Draw the implicitly defined surface f(x, y, z) = 0.                       */
draw(implicitsurface(f, start, end, overlapedges=true), surfacepen=blob);
