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
 ******************************************************************************/

import three;
import graph3;
import settings;
settings.outformat = "pdf";
settings.render=8;

size(1024);

/*  Camera angle.                                                             */
currentprojection = perspective(-10, -8, 4);

currentlight = light(diffuse  = new pen[]    {white},
                     specular = new pen[]    {white},
                     position = new triple[] {-0.25*X -0.25*Y + Z});

int N = 30;
int m, n;
real start = 0.0;
real end = 1.0;
real dx = (end - start) / N;

real x[] = new real[N];
real y[] = new real[N];
real z0[][] = new real[N][N];
real z1[][] = new real[N][N];

real arsize = 8bp;
pen meshp = black + linewidth(0.7pt);
pen axesp = black + linewidth(1.2pt);

material blob0 = material(
    diffusepen = gray(0.8),
    emissivepen = gray(0.2),
    specularpen = gray(0.2)
);

material blob1 = material(
    diffusepen = gray(0.6),
    emissivepen = gray(0.2),
    specularpen = gray(0.2)
);

x[0] = start;
y[0] = start;

z0[0][0] = 0.0;
z1[0][0] = 0.0;

for (n = 1; n < N; ++n)
{
    x[n] = x[n-1] + dx;
    y[n] = y[n-1] + dx;
}

for (n = 1; n < N; ++n)
{
    z0[n][0] = z0[0][0];
    z1[0][n] = z1[0][0];
}

for (n = 0; n < N; ++n)
{
    for (m = 1; m < N; ++m)
    {
        z0[n][m] = z0[n][m-1] - x[n]*dx;
        z1[m][n] = z1[m-1][n] + y[n]*dx;
    }
}

draw(surface(z0, x, y), meshpen=meshp, surfacepen=blob0, render(merge=true));
draw(surface(z1, x, y), meshpen=meshp, surfacepen=blob1, render(merge=true));

xaxis3(Label("$x$"), 0, 1.2*end, axesp, Arrow3(arsize));
yaxis3(Label("$y$"), 0, 1.2*end, axesp, Arrow3(arsize));
zaxis3(Label("$z$"), 0, 1.2*end, axesp, Arrow3(arsize));

