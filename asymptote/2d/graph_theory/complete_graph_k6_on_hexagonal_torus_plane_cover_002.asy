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

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Size of the output figure.                                                */
size(256);

pair MidPoint2D(pair A, pair B)
{
    real x = 0.5*(A.x + B.x);
    real y = 0.5*(A.y + B.y);
    pair mid = (x, y);
    return mid;
}

int k, n, m;
int N = 6;
pair[] V;
pair[] W;
real theta = pi / 6.0;
real phi = pi / 3.0;
real sin_theta = sin(theta);
real cos_theta = cos(theta);
real cos_phi = cos(phi);
real r0 = 1.0;
real r1 = r0*cos_theta / (1.0 + sin_theta);
real rDot = 0.05;
real arsize = 4bp;
real outter_width = cos_theta*r0;
real inner_width = cos_phi*r1;
real inner_height = sin(phi)*r1;
real tfactor = (outter_width - r1)*0.5773502691896257;

pair dx = (2.0*outter_width, 0.0);
pair ds = scale(2.0*outter_width)*expi(0.6666667*pi);

pair R0 = (-outter_width, tfactor);
pair R1 = (-r1, 1.1547005383792515*r1);

pair R2 = (outter_width, tfactor);
pair R3 = (inner_width, -3.0*inner_height + 1.1547005383792515*r1);

pair R4 = (r1, 1.1547005383792515*r1);
pair R5 = (-inner_width, -3.0*inner_height + 1.1547005383792515*r1);

transform T;
for (m = 0; m < N; ++m)
{
    for (n = 0; n < N; ++n)
    {
        T = shift(scale(m)*dx + scale(n)*ds);
        for (k = 0; k < 6; ++k)
        {
            V[k] = T*(scale(r0)*expi(0.16667*pi + 0.33333*pi*k));
            W[k] = T*(scale(r1)*expi(0.33333*pi*k));
        }

        draw(W[0] -- MidPoint2D(V[5], V[0]));
        draw(W[1] -- MidPoint2D(V[0], V[1]));
        draw(W[2] -- MidPoint2D(V[1], V[2]));
        draw(W[3] -- MidPoint2D(V[2], V[3]));
        draw(W[4] -- MidPoint2D(V[3], V[4]));
        draw(W[5] -- MidPoint2D(V[4], V[5]));
        draw(W[0] -- W[1] -- W[2] -- W[3] -- W[4] -- W[5] -- cycle);
        draw(W[0] -- W[2] -- W[4] -- cycle);
        draw(W[3] -- T*R0);
        draw(W[3] -- T*R1);
        draw(W[1] -- T*R2);
        draw(W[5] -- T*R3);
        draw(W[1] -- T*R4);
        draw(W[5] -- T*R5);

        filldraw(circle(W[0], rDot), blue, black);
        filldraw(circle(W[2], rDot), blue, black);
        filldraw(circle(W[4], rDot), blue, black);
        filldraw(circle(W[1], rDot), red, black);
        filldraw(circle(W[3], rDot), red, black);
        filldraw(circle(W[5], rDot), red, black);
    }
}

clip((0.0, 0.0) -- (r0*N, 0.0) -- (r0*N, r0*N) -- (0.0, r0*N) -- cycle);
