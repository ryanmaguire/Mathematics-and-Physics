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

import custom_arrows;

/*  Size of the figure.                                                       */
size(128);

real r = 0.5;

pair A0 = expi(1.167*pi);
pair B0 = expi(1.833*pi);
pair C0 = expi(0.5*pi);

pair A1 = scale(r)*(rotate(60)*A0);
pair B1 = scale(r)*(rotate(60)*B0);
pair C1 = scale(r)*(rotate(60)*C0);

real arsize = 5bp;

path g = A0 .. A1 .. B1 .. C0{W} .. C1 .. A1 .. B0 ..B1 .. C1 .. cycle;
int samples = 40;
int n, m;
real rcpr_samples = 1.0 / samples;

real current_point;
real current_pos;
real next_pos;

pair P0, P1;
pair O0, O1, O2, O3;
current_pos = 0.0;

real rect_size = 0.5;
real rect_length = 1.0;

pair orth(pair A, pair B)
{
    return (A.y - B.y, B.x - A.x);
}

pair orth_line(pair A, pair B, real t, real s)
{
    pair O = orth(A, B);
    return scale(1.0 - t)*A + scale(t)*B + scale(s)*O;
}

for (m = 0; m < 12; ++m)
{
    current_point = m;
    for (n = 1; n < samples; ++n)
    {
        next_pos = current_point + n*rcpr_samples;
        P0 = point(g, current_pos);
        P1 = point(g, next_pos);
        current_pos = next_pos;

        O0 = orth_line(P0, P1, 1.0 - rect_length, rect_size);
        O1 = orth_line(P0, P1, rect_length, rect_size);
        O2 = orth_line(P0, P1, rect_length, -rect_size);
        O3 = orth_line(P0, P1, 1.0 - rect_length, -rect_size);

        filldraw(O0 -- O1 -- O2 -- O3 -- cycle,
                 white, white + linewidth(0.1pt));
        draw(P0 -- P1);
    }
}

g = A0 .. A1 .. B1 .. C0{W} .. C1 .. A1 .. B0 ..B1 .. C1 .. cycle;
draw(g, invisible, MidSharpArrow(arsize));

g = A1 .. B1 .. C0{W} .. C1 .. A1 .. B0 ..B1 .. C1 .. A0 .. cycle;
draw(g, invisible, MidSharpArrow(arsize));

g = B1 .. C0{W} .. C1 .. A1 .. B0 ..B1 .. C1 .. A0 .. A1 .. cycle;
draw(g, invisible, MidSharpArrow(arsize));

g = C0{W} .. C1 .. A1 .. B0 ..B1 .. C1 .. A0 .. A1 .. B1 .. cycle;
draw(g, invisible, MidSharpArrow(arsize));

g = C1 .. A1 .. B0 ..B1 .. C1 .. A0 .. A1 .. B1 .. C0{W} .. cycle;
draw(g, invisible, MidSharpArrow(arsize));

g = A1 .. B0 ..B1 .. C1 .. A0 .. A1 .. B1 .. C0{W} .. C1 .. cycle;
draw(g, invisible, MidSharpArrow(arsize));

g = B0 .. B1 .. C1 .. A0 .. A1 .. B1 .. C0{W} .. C1 .. A1 .. cycle;
draw(g, invisible, MidSharpArrow(arsize));

g = B1 .. C1 .. A0 .. A1 .. B1 .. C0{W} .. C1 .. A1 .. B0 .. cycle;
draw(g, invisible, MidSharpArrow(arsize));

g = C1 .. A0 .. A1 .. B1 .. C0{W} .. C1 .. A1 .. B0 .. B1 .. cycle;
draw(g, invisible, MidSharpArrow(arsize));
