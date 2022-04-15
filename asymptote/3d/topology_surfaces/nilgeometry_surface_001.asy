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
 ******************************************************************************/

/*  3D tools here.                                                            */
import three;

/*  Surface function found here.                                              */
import graph3;

/*  PDF works best with LaTeX, so use this.                                   */
import settings;
settings.outformat = "pdf";

/*  Increase the render to 8 for a nice smooth picture.                       */
settings.render = 8;

/*  Size of the figure.                                                       */
size(256);

/*  Camera angle.                                                             */
currentprojection = perspective(-10.0, -8.0, 4.0);

/*  Setup the light.                                                          */
currentlight = light(
    diffuse  = new pen[] {white},
    specular = new pen[] {white},
    position = new triple[] {-0.25*X -0.25*Y + Z}
);

/*  Number of samples in the drawing.                                         */
int N = 30;

/*  Variables for indexing.                                                   */
int m, n;

/*  Start and end for Euler's method.                                         */
real start = 0.0;
real end = 1.0;

/*  Step size for Euler's method.                                             */
real dx = (end - start) / N;

/*  Variables for the two surfaces.                                           */
real x[] = new real[N];
real y[] = new real[N];
real z0[][] = new real[N][N];
real z1[][] = new real[N][N];

/*  Size of an arrow head.                                                    */
real arsize = 8bp;

/*  Pens for the mesh and axes.                                               */
pen meshp = black + linewidth(0.7pt);
pen axesp = black + linewidth(1.2pt);

/*  Material the top surface is made of.                                      */
material blob0 = material(
    diffusepen = gray(0.8),
    emissivepen = gray(0.2),
    specularpen = gray(0.2)
);

/*  Material of the bottom surface.                                           */
material blob1 = material(
    diffusepen = gray(0.6),
    emissivepen = gray(0.2),
    specularpen = gray(0.2)
);

/*  Initialize the zeroth element of the two arrays.                          */
x[0] = start;
y[0] = start;

/*  Initialize the value at the origin of the two surfaces.                   */
z0[0][0] = 0.0;
z1[0][0] = 0.0;

/*  Compute the values of the x and y arrays.                                 */
for (n = 1; n < N; ++n)
{
    x[n] = x[n-1] + dx;
    y[n] = y[n-1] + dx;
}

/*  Compute the values of the surfaces along and x and y axes.                */
for (n = 1; n < N; ++n)
{
    z0[n][0] = z0[0][0];
    z1[0][n] = z1[0][0];
}

/*  Use Euler's method on the two surfaces.                                   */
for (n = 0; n < N; ++n)
{
    for (m = 1; m < N; ++m)
    {
        z0[n][m] = z0[n][m-1] - x[n]*dx;
        z1[m][n] = z1[m-1][n] + y[n]*dx;
    }
}

/*  Draw the surfaces, and give them a mesh.                                  */
draw(surface(z0, x, y), meshpen=meshp, surfacepen=blob0, render(merge=true));
draw(surface(z1, x, y), meshpen=meshp, surfacepen=blob1, render(merge=true));

/*  Add the axes.                                                             */
xaxis3(Label("$x$"), 0, 1.2*end, axesp, Arrow3(arsize));
yaxis3(Label("$y$"), 0, 1.2*end, axesp, Arrow3(arsize));
zaxis3(Label("$z$"), 0, 1.2*end, axesp, Arrow3(arsize));
