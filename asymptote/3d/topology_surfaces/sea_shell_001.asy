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
 *      Draw a sea shell.                                                     *
 ******************************************************************************/

/*  Used for rendering parameterized 3D objects.                              */
import graph3;

/*  Used for creating color gradients on surfaces.                            */
import palette;

/*  PDF works best with LaTeX, output this. Also set the render factor high.  */
import settings;
settings.outformat = "pdf";
settings.render = 8;

/*  Size of the created image.                                                */
size(256);

/*  Set camera location.                                                      */
currentprojection = perspective(-2.0, -5.0, 2.0);

/*  Mesh pen for the surface.                                                 */
pen mpen = black + linewidth(0.5pt);

/*  Start and end values for the parameterization.                            */
pair start = (0.0, 0.0);
pair end = (2.0*pi, 2.0*pi);

/*  Number of samples for the parameterization.                               */
int ntheta = 30;
int nphi = 50;

/*  Some parameters for the surface.                                          */
real R = 1.0;
real N = 3.6;
real H = 2.0;
real P = 1.9;

/*  The sea shell surface.                                                    */
triple sea_shell(pair t)
{
    real a = t.x / (2.0*pi*R);
    real cosy = cos(t.y);

    real x = a * cos(N*t.x)*(1.0 + cosy);
    real y = a * sin(N*t.x)*(1.0 + cosy);
    real z = -a * sin(t.y) - H*(a^P);

    triple out = (x, y, z);
    return out;
}
/*  End of sea_shell.                                                         */

/*  Create the surface.                                                       */
surface s = surface(sea_shell, start, end, nphi, ntheta, Spline);

/*  Create a color gradient in the x direction from blue to green.            */
s.colors(palette(s.map(xpart), Gradient(blue, green)));

/*  Draw the sea shell.                                                       */
draw(s, meshpen=mpen, render(merge=true));
