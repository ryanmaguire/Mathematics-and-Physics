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

/*  Size of the figure.                                                       */
size(256);

/*  Pen for drawing.                                                          */
pen dpen = black + linewidth(0.3pt);
pen handlep = black + linewidth(0.8pt);
pen dashp = black + linewidth(0.6pt);

pair line_eval(pair A, pair B, real t)
{
    return scale(t)*B + scale(1.0 - t)*A;
}

pair orth(pair A)
{
    return (-A.y, A.x);
}

pair line_orth(pair A, pair B, real t)
{
    pair mid = line_eval(A, B, 0.5);
    pair orth = (-mid.y, mid.x);
    return mid + scale(t)*orth;
}

void draw_handle(pair A, pair B, real t, real s, real theta)
{
    pair H00 = line_eval(A, B, t);
    pair H01 = line_eval(A, B, 1.0 - t);
    pair H02 = line_orth(H00, H01, s);
    pair H10 = H00 + (0.8*s, 0.0);
    pair H11 = line_eval(H10, H01, 0.6);
    pair H12 = line_orth(H00, H01, 0.5*s);

    path g1 = H00{B - A} .. H02 .. H01{B - A};
    path g2 = H10{orth(B - A)} .. H12 .. H11{orth(A - B)};
    path g3 = H02{A - B} .. H12{B - A};

    transform T = shift(-line_eval(H00, H01, 0.5));
    transform invT = shift(line_eval(H00, H01, 0.5));
    transform rot = rotate(theta);

    g1 = invT*(rot*(T*g1));
    g2 = invT*(rot*(T*g2));
    g3 = invT*(rot*(T*g3));
    filldraw(g1 -- reverse(g2) -- cycle, white, white);
    draw(g1, handlep);
    draw(g2, handlep);
    draw(g3, dashp);
}

pair V0 = (0.0, 0.0);
pair V1 = (1.0, 0.0);
pair V2 = (0.5, 1.0);
pair V3 = (1.5, 1.0);
pair V4 = (2.5, 1.0);

pair temp = (1.7, 0.5);

pair A0 = (0.55, 0.3);
pair A1 = (0.65, 0.63);
pair A2 = (0.95, 0.61);

pair B0 = (0.8, 0.15);
pair B1 = (0.78, 0.32);
pair B2 = (0.98, 0.32);
pair B3 = (1.2, 0.55);
pair B4 = (1.28, 0.6);
pair B5 = (1.36, 0.4);

dot(V0);
dot(V1);
dot(V2);
dot(V3);
dot(V4);

draw(V0 -- V2, dpen);
draw(V1 -- V2, dpen);
draw(V1 -- V3, dpen);
draw(V1 -- V4, dpen);
draw_handle(V0, V3, 0.3, 0.25, 0.0);
draw_handle(V0, V4, 0.45, 0.1, -50.0);
draw_handle(V0, temp, 0.4, 0.15, 30.0);

draw(V0{NE} .. A0 .. A1{NE} .. A2 .. V3{NE}, dpen);
draw(V0{E} .. B0{N} .. B1{NE} .. B2{E} .. B3 .. B4{E} .. B5{E} .. V4{E}, dpen);
