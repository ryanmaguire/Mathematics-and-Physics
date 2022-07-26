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
 *  Date:       July 26, 2022                                                 *
 ******************************************************************************/

/*  Settings for higher render factor.                                        */
import settings;

/*  Tools for drawing the quotient here.                                      */
import graph3;

/*  Tube for the boundary of the blob.                                        */
import tube;

/*  Set the render factor to high.                                            */
settings.render = 8;
settings.outformat = "pdf";

/*  We're drawing four renditions of the gluing process.                      */
int n;
int n_figs = 4;

/*  Samples for the blob.                                                     */
int samples = 30;

/*  Samples for the boundary of the blob.                                     */
int boundary_samples = 80;

/*  Variable for looping over the sphere homotopy.                            */
real s = 0.0;
real ds = 1.0 / n_figs;

/*  Threshold for the zenith angle. It can't be zero without divide-by-zero.  */
real zen_min = 0.01;

/*  Surface for the blob.                                                     */
surface surf;

/*  Transform for shifting the images.                                        */
transform3 TShift;

/*  Size of the created image.                                                */
size(512);

/*  Camera setup.                                                             */
currentprojection = perspective(
    camera = (0.0, -20.0, 5.0),
    up     = (0.0, 0.0, 1.0),
    target = (0.0, 0.0, 0.0),
    zoom   = 1.0
);

/*  Lighting for the drawing.                                                 */
currentlight = light(
    diffuse = new pen[] {white},
    specular = new pen[] {white},
    position = new triple[] {(100.0, 100.0, 400.0)}
);

material blob = material(
    diffusepen = gray(0.5),
    emissivepen = gray(0.2),
    specularpen = gray(0.2)
);

material pipe = material(
    diffusepen = blue + 0.3*green,
    emissivepen = gray(0.20),
    specularpen = gray(0.20)
);

/*  Parameterization of the sphere (embedding into R^3).                      */
triple sphere_embedding(pair t)
{
    /*  Pre-compute sine and cosine to reduce total calculations.             */
    real cos_u = cos(t.x);
    real sin_u = sin(t.x);
    real cos_v = cos(t.y);
    real sin_v = sin(t.y);

    /*  Compute the x, y, and z factors and return.                           */
    return (cos_u*sin_v, sin_u*sin_v, cos_v);
}
/*  End of sphere_embedding.                                                  */

pair stereographic_projection(triple P)
{
    real factor = 1.0 / (1.0 - P.z);
    return (P.x*factor, P.y*factor);
}

pair plane_to_disk_homeo(pair P)
{
    real norm_P = sqrt(P.x*P.x + P.y*P.y);
    return P / (1.0 + norm_P);
}

triple inclusion_map(pair P)
{
    return (P.x, P.y, 0.0);
}

triple straight_line_homotopy(pair t)
{
    triple P = sphere_embedding(t);
    triple Q = inclusion_map(plane_to_disk_homeo(stereographic_projection(P)));
    return s*P + (1.0 - s)*Q;
}

path3 boundary()
{
    pair T = (0.0, zen_min);
    path3 g = straight_line_homotopy(T);
    int m;
    real dt = 2.0*pi / boundary_samples;
    for (m = 0; m <= boundary_samples + 1; ++m)
    {
        T = (T.x + dt, T.y);
        g = g .. straight_line_homotopy(T);
    }
    return g;
}

/*  Loop over the frames and create the GIF.                                  */
for (n = 0; n <= n_figs; ++n)
{
    /*  Create the surface.                                                   */
    surf = surface(
        straight_line_homotopy,
        (0.0, zen_min),
        (2.0*pi, pi),
        samples,
        samples,
        Spline
    );

    /*  Draw the surface to the actual frame.                                 */
    TShift = shift(-3.0 + 2.0*n, 0.0, 0.0);
    draw(TShift*surf, surfacepen = blob, render(merge = true));
    draw(tube(TShift*boundary(), scale(0.02)*unitcircle), surfacepen=pipe);

    /*  Increment x.                                                          */
    s += ds;
}
