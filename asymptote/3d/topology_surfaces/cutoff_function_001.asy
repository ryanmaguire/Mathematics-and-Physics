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
 *      Draw a "bump" function, or a cutoff function, in R^3.                 *
 ******************************************************************************/

/*  Used for rendering parameterized 3D objects.                              */
import graph3;

/*  PDF works best with LaTeX, output this. Also set the render factor high.  */
import settings;
settings.outformat = "pdf";
settings.render = 8;

/*  Size of the output figure.                                                */
size(256);

/*  Camera angle.                                                             */
currentprojection = perspective(10.0, 8.0, 4.0);

/*  Arrow size.                                                               */
real arsize = 5bp;

/*  Parameters for the bump function. For points p with ||p|| < r1, the       *
 *  bump function is 1. For points p with ||p|| > r2, the bump function is 0. *
 *  The function smoothly transitions from 1 to 0 between r1 and r2.          */
real r1 = 1.0;
real r2 = 1.5;

/*  Number of samples for the surface in the radial and azimuthal directions. */
int nr = 30;
int ntheta = 40;

/*  Pen for mesh lines on the surface.                                        */
pen mpen = black + linewidth(0.3pt);

/*  Real valued bump function.                                                */
real f(real t)
{
    if (t <= 0.0)
        return 0.0;
    else
        return exp(-1.0/t);
}
/*  End of f.                                                                 */

/*  Another bump function on R that is 1 for t > r2 and 0 for t < r1.         */
real g(real t)
{
    real a, b;
    a = f(r2-t);
    b = f(t-r1);

    return a/(a+b);
}
/*  End of g.                                                                 */

/*  Bump function on R^2.                                                     */
triple h(pair z)
{
    /*  The input z = (z.x, z.y) is of the form z = (r, theta). That is, z    *
     *  is written in polar coordinates. Extract these values.                */
    real r = z.x;
    real theta = z.y;

    /*  Convert to Cartesian coordinates.                                     */
    real x = r*cos(theta);
    real y = r*sin(theta);

    /*  The point on the surface is of the form (x, y, f(x, y)). The          *
     *  function f is radially symmetric, defined only in terms of r. Return  *
     *  the point (x, y, g(r)) = (x, y, f(x, y)).                             */
    return (x, y, g(r));
}
/*  End of h.                                                                 */

/*  Create the surface.                                                       */
surface s = surface(h, (0.0, 0.0), (2.0, 2.0*pi), nr, ntheta, Spline);

/*  Draw axes.                                                                */
xaxis3(Label("$x$"), 0, 2.3, black, Arrow3(arsize));
yaxis3(Label("$y$"), 0, 2.3, black, Arrow3(arsize));
zaxis3(Label("$z$"), 0, 1.8, black, Arrow3(arsize));

/*  Draw the surface.                                                         */
draw(s, lightgray, nolight, meshpen=mpen, render(merge=true));
