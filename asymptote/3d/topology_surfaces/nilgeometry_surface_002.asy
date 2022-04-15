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

/*  Start and end for Euler's method.                                         */
real start = 0.0;
real end = 1.0;

/*  Step size for Euler's method.                                             */
real dx = (end - start) / N;

/*  Equations of the two surfaces.                                            */
real surfa (pair P)
{
    return P.x*P.y;
}

real surfb (pair P)
{
    return -P.x*P.y;
}

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

/*  Create the two surfaces.                                                  */
surface sa = surface(surfa, (start, start), (end, end), N, N, Spline);
surface sb = surface(surfb, (start, start), (end, end), N, N, Spline);

/*  Draw the surfaces, and give them a mesh.                                  */
draw(sa, meshpen=meshp, surfacepen=blob0, render(merge=true));
draw(sb, meshpen=meshp, surfacepen=blob1, render(merge=true));

/*  Add the axes.                                                             */
xaxis3(Label("$x$"), 0, 1.2*end, axesp, Arrow3(arsize));
yaxis3(Label("$y$"), 0, 1.2*end, axesp, Arrow3(arsize));
zaxis3(Label("$z$"), 0, 1.2*end, axesp, Arrow3(arsize));
