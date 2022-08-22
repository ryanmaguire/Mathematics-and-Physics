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
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 29, 2021                                            *
 ******************************************************************************/

/*  Used for drawing surfaces in 3D.                                          */
import graph3;

/*  Used for coloring the Boy surface.                                        */
import palette;

/*  Needed to output a PDF.                                                   */
import settings;
settings.render = 8;
settings.outformat = "pdf";

/*  Size of the created image.                                                */
size(256);

/*  Setup the camera.                                                         */
currentprojection = orthographic(
    camera = (40.0, 30.0, 20.0),
    target = (0.0, 0.0, 0.0)
);

/*  Precompute sqrt(2).                                                       */
real SQRT_2 = sqrt(2.0);

/*  Apery's immersion for the Boy Surface, a model for RP^2.                  */
triple real_proj_plane(pair t)
{
    real u = t.x;
    real v = t.y;
    real cu = cos(u);
    real su = sin(u);
    real cv = cos(v);
    real s2v = sin(2.0*v);
    real c2u = cos(2.0*u);
    real s2u = sin(2.0*u);
    real s3u = sin(3.0*u);
    real denom = 1.0 / (2.0 - SQRT_2*s3u*s2v);

    real x0 = (SQRT_2*cv*cv*c2u + cu*s2v)*denom;
    real x1 = (SQRT_2*cv*cv*s2u - su*s2v)*denom;
    real x2 = 3.0*cv*cv*denom;

    return (x0, x1, x2);
}
/*  End of real_proj_plane.                                                   */

/*  Create the surface.                                                       */
surface s=surface(real_proj_plane, (0.0, 0.0), (2.0*pi, pi), 40, 40, Spline);

/*Give the surface a color gradient.                                          */
s.colors(palette(s.map(zpart), Gradient(blue, green)));

/*  Draw it with mesh lines.                                                  */
draw(s, meshpen=black+linewidth(0.3pt), render(merge=true));
