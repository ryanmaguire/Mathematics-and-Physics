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
 *      Draw a genus 2 surface using the lemniscate of Gerono.                *
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
currentprojection = perspective(20.0, 80.0, 30.0);

/*  Scales for the x and z axes.                                              */
real xscale = 1.0;
real zscale = 1.5;

/*  Parameters for the "thickness" of the genus 2 surface.                    */
real h = 0.03;

/*  Start and end parameters for the surface.                                 */
triple start = (-1.2, -1.0, -0.4);
triple end = (1.2, 1.0, 0.4);

/*  Material of the genus 2 surface.                                          */
material blob = material(
    diffusepen=gray(0.5),
    emissivepen=gray(0.2),
    specularpen=gray(0.2)
);

/*  Lemniscate of Gerono.                                                     */
real lem2(real x, real y)
{
    real u = xscale*x;
    real u2 = u*u;
    return u2*u2 - u2 + y*y;
}
/*  End of lem2.                                                              */

/*  Implicit equation for the genus 2 surface using the lemniscate of Gerono. *
 *  Just like the torus can be though of as a "thicker" circle, the genus 2   *
 *  surface can be thought of as thickening the lemniscate of Gerono.         */
real f(real x, real y, real z)
{
    real rho = lem2(x, y);
    real zval = zscale*z;
    return rho*rho + zval*zval - h;
}

/*  Compute points on the implicitly defined surface.                         */
surface s = implicitsurface(f, a=start, b=end);

/*  Draw the surface.                                                         */
draw(s, surfacepen=blob, render(merge=true));
