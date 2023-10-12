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
size(256);

pair normalize(pair P)
{
    real mag = sqrt(P.x*P.x + P.y*P.y);
    real factor = mag / (1.0 + mag);
    return (factor*P.x, factor*P.y);
}

triple torus (pair P, real phi)
{
    P = normalize(P);
    real r0 = 1.5;
    real r1 = sqrt(P.x*P.x + P.y*P.y);
    real theta = atan2(P.y, P.x);
    real x = (r0 + r1*cos(theta))*cos(phi);
    real y = (r0 + r1*cos(theta))*sin(phi);
    real z = r1*sin(theta);
    return (x, y, z);
}


int n;
int N = 200;
real dphi = 2.0*pi/(real)N;
real angle = 0.0;
real scale_factor = 0.5;
pair P = (1.0, 0.0);
pair Q = (scale_factor, 0.0);
triple p0[] = new triple[N];
triple p1[] = new triple[N];
real threshold = 0.03;
p0[0] = torus(P, 0.0);
p1[0] = torus(Q, 0.0);

for (n = 0; n < N; ++n)
{
    angle += dphi;
    pair P = (cos(angle), sin(angle));
    pair Q = (scale_factor*P.x, scale_factor*P.y);
    real perp = atan2(P.y, P.x);
    p0[n] = torus(P, perp);
    p1[n] = torus(Q, perp);
}

for (n = 0; n < N - 1; ++n)
{
    P = (p0[n].x, p0[n].y);
    Q = (p1[n].x, p1[n].y);

    real dist = abs(P-Q);

    if (dist > threshold)
    {
        draw((p0[n].x, p0[n].y) -- (p0[n+1].x, p0[n+1].y));
        draw((p1[n].x, p1[n].y) -- (p1[n+1].x, p1[n+1].y));
    }
    else if (p0[n].z < p1[n].z)
    {
        draw((p0[n].x, p0[n].y) -- (p0[n+1].x, p0[n+1].y), invisible);
        draw((p1[n].x, p1[n].y) -- (p1[n+1].x, p1[n+1].y));
    }
    else
    {
        draw((p0[n].x, p0[n].y) -- (p0[n+1].x, p0[n+1].y));
        draw((p1[n].x, p1[n].y) -- (p1[n+1].x, p1[n+1].y), invisible);
    }
}

draw((p0[0].x, p0[0].y) -- (p0[N-1].x, p0[N-1].y));
draw((p1[0].x, p0[0].y) -- (p1[N-1].x, p1[N-1].y));

