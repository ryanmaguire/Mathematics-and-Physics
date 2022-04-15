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
 *      Drawa 2 torii linked together.                                        *
 ******************************************************************************/

/*  Used for rendering parameterized 3D objects.                              */
import graph3;

/*  PDF works best with LaTeX, output this. Also set the render factor high.  */
import settings;
settings.outformat = "pdf";
settings.render = 8;

/*  Size of the image. For 3D objects it seems best to have this set to a     *
 *  power of 2, otherwise weird vertical or horizontal black lines may appear.*/
size(256);

/*  How the image is being drawn on a 2D picture.                             */
currentprojection = perspective(5.0, 4.0, 4.0);

/*  Two radii defining the torus.                                             */
real R = 3.0;
real a = 1.3;

/*  Material the two torii are made of.                                       */
material blueblob = material(
    diffusepen = blue + 0.25*green,
    emissivepen = gray(0.2),
    specularpen = gray(0.2)
);

material redblob = material(
    diffusepen = red,
    emissivepen = gray(0.2),
    specularpen = gray(0.2)
);

/*  Function for drawing the torus.                                           */
triple torus_parameterization(pair t)
{
    /*  The parameterization is in terms of sine and cosine of 2 pi t.x and   *
     *  2 pi t.y. Precompute these to avoid repetitive calculations.          */
    real u = 2.0*pi*t.x;
    real v = 2.0*pi*t.y;
    real cosu = cos(u);
    real cosv = cos(v);
    real sinu = sin(u);
    real sinv = sin(v);

    /*  Given the two angles u and v, the x, y, and z coordinates are:        */
    real x = (R + a*cosv)*cosu;
    real y = (R + a*cosv)*sinu;
    real z = a*sinv;

    /*  Return the point (x, y, z), which is a point on the surface.          */
    triple out = (x, y, z);
    return out;
}
/*  End of torus_parameterization.                                            */

/*  Create the first torus.                                                   */
surface t0 = surface(torus_parameterization, (0.0, 0.0), (1.0, 1.0), Spline);

/*  The second torus is obtained by rotating and shifting.                    */
surface t1 = shift((R, 0.0, 0.0))*(rotate(90.0, (1.0, 0.0, 0.0))*t0);

/*  Draw both of the torii.                                                   */
draw(t0, surfacepen = redblob, render(merge=true));
draw(t1, surfacepen = blueblob, render(merge=true));
