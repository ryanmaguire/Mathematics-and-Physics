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
 *      Draw a genus 3 surface using a lemniscate.                            *
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

/*  Material for the genus 3 surface.                                         */
material blob = material(
    diffusepen=gray(0.7),
    emissivepen=gray(0.2),
    specularpen=gray(0.2)
);

/*  Start and end parameters for the implicitly defined surface.              */
triple start = (-2.1, -1.2, -0.4);
triple end = (2.1, 1.2, 0.4);

/*  Parameter for the "thickness" of the genus 3 surface.                     */
real h = 0.2;

/*  Number of samples used for drawing the surface.                           */
int samples = 80;

/*  Lemniscate with 2 intersection points (so a "double" lemniscate).         */
real lem2(real x, real y)
{
    real u = 0.5*x;
    real factor = 4.0*u*u - 1.0;
    return y*y - factor * factor * (1.0 - u*u);
}
/*  End of lem2.                                                              */

/*  Implicit equation defining a genus 3 surface.                             */
real f(real x, real y, real z)
{
    real u = lem2(x, y);
    return u*u + z*z - h*h;
}
/*  End of f.                                                                 */

/*  Create the surface f(x, y, z) = 0.                                        */
surface s = implicitsurface(f, a=start, b=end);

/*  Draw the surface.                                                         */
draw(s, surfacepen=blob, samples, render(merge=true));
