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

/*  Needed for making the output a PDF file.                                  */
import settings;

/*  Needed for parameteric equations.                                         */
import graph;

import custom_arrows;

/*  PDF works best in LaTeX, so use this.                                     */
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(512);

/*  Default pen used for drawing.                                             */
defaultpen(black + linewidth(0.5pt) + fontsize(7pt));

/*  Projection of the figure-eight parameterization onto the xy-plane.        */
pair figeight(real t)
{
    real c2t = cos(2.0*t);
    real c3t = cos(3.0*t);
    real s3t = sin(3.0*t);
    real factor = 2.0 + c2t;
    return (c3t*factor, s3t*factor);
}

real dx = 0.5;

pair A0 = figeight(pi/6.0) + (0.0, dx);
pair A1 = figeight(pi/6.0) + (0.0, -dx);
pair A2 = figeight(pi/6.0) + (dx, 0.0);
pair A3 = figeight(pi/6.0) + (-dx, 0.0);
pair B = figeight(0.0);
pair C0 = figeight(7.0*pi/6.0) + (0.0, dx);
pair C1 = figeight(7.0*pi/6.0) + (0.0, -dx);
pair C2 = figeight(7.0*pi/6.0) + (dx, 0.0);
pair C3 = figeight(7.0*pi/6.0) + (-dx, 0.0);
pair D0 = figeight(pi/3.0) + (0.0, dx);
pair D1 = figeight(pi/3.0) + (0.0, -dx);
pair D2 = figeight(pi/3.0) + (dx, 0.0);
pair D3 = figeight(pi/3.0) + (-dx, 0.0);
pair E = figeight(1.5*pi);
pair F0 = figeight(4.0*pi/3.0) + (0.0, dx);
pair F1 = figeight(4.0*pi/3.0) + (0.0, -dx);
pair F2 = figeight(4.0*pi/3.0) + (dx, 0.0);
pair F3 = figeight(4.0*pi/3.0) + (-dx, 0.0);
pair G = figeight(pi);
pair H = figeight(0.5*pi);
pair labelpos = (1.8, -3.8);

real xshift = 9.0;
real yshift = 4.5;
real knotscale = 1.7;
path g0, g1, g2;
transform T = shift(0.2*xshift, 4.5*yshift);

/*  Draw the knot in pieces to mimic crossings.                               */
draw(T*(scale(knotscale)*graph(figeight, 0.00, 0.50, operator ..)));
draw(T*(scale(knotscale)*graph(figeight, 0.55, 2.07, operator ..)));
draw(T*(scale(knotscale)*graph(figeight, 2.12, 3.63, operator ..)));
draw(T*(scale(knotscale)*graph(figeight, 3.69, 5.21, operator ..)));
draw(T*(scale(knotscale)*graph(figeight, 5.26, 2.0*pi, operator ..)));

/*  Label the crossings.                                                      */
label("$0$", T*(scale(knotscale)*(figeight(pi/6.0) + (0.0, 0.4))));
label("$1$", T*(scale(knotscale)*(figeight(4.0*pi/3.0) + (0.4, 0.0))));
label("$2$", T*(scale(knotscale)*(figeight(pi/3.0) + (-0.4, 0.0))));
label("$3$", T*(scale(knotscale)*(figeight(7.0*pi/6.0) + (0.0, -0.4))));

/*  I royally messed up the order. The shifts indicate which is which, as do  *
 *  the comments. This is the 0110 resolution.                                */
g0 = A0 .. B .. C1 .. G .. cycle;
g1 = A1 .. F2 .. C0 .. D3 .. cycle;
g2 = D2 .. E .. F3 .. H .. cycle;
T = shift(2.0*xshift, yshift);
draw(T*g0);
draw(T*g1);
draw(T*g2);
label("$0110$", T*labelpos);

/*  This is the 0111 resolution.                                              */
g0 = A2 .. B .. C1 .. G .. A3 .. D3 .. C0 .. F2 .. cycle;
g1 = D2 .. E .. F3 .. H .. cycle;
T = shift(3.0*xshift, 3.0*yshift);
draw(T*g0);
draw(T*g1);
label("$0111$", T*labelpos);

/*  This is the 1110 resolution.                                              */
T = shift(3.0*xshift, -3.0*yshift);
g0 = rotate(180.0)*g0;
g1 = rotate(180.0)*g1;
draw(T*g0);
draw(T*g1);
label("$1110$", T*labelpos);

/*  This is the 0100 resolution.                                              */
g0 = A0 .. B .. C1 .. G .. cycle;
g1 = A1 .. F0 .. E .. D2 .. H .. F1 .. C0 .. D3 .. cycle;
T = shift(xshift, -yshift);
draw(T*g0);
draw(T*g1);
label("$0100$", T*labelpos);

/*  This is the 0010 resolution.                                              */
T = shift(xshift, yshift);
g0 = rotate(180.0)*g0;
g1 = rotate(180.0)*g1;
draw(T*g0);
draw(T*g1);
label("$0010$", T*labelpos);

/*  This is the 0101 resolution.                                              */
g0 = A2 .. B .. C1 .. G .. A3 .. D3 .. C0 .. F1 .. H .. D2 .. E .. F3 .. cycle;
T = shift(2.0*xshift, 3.0*yshift);
draw(T*g0);
label("$0101$", T*labelpos);

/*  This is the 0011 resolution.                                              */
T = shift(2.0*xshift, -5.0*yshift);
draw(T*(reflect((0.0, 0.0), (0.0, 1.0))*g0));
label("$0011$", T*labelpos);

/*  This is the 1100 resolution.                                              */
T = shift(2.0*xshift, 5.0*yshift);
g0 = reflect((0.0, 0.0), (1.0, 0.0))*g0;
draw(T*g0);
label("$1100$", T*labelpos);

/*  This is the 1010 resolution.                                              */
T = shift(2.0*xshift, -3.0*yshift);
g0 = reflect((0.0, 0.0), (0.0, 1.0))*g0;
draw(T*g0);
label("$1010$", T*labelpos);

/*  This is the 0000 resolution.                                              */
g0 = A0 .. B .. C1 .. G .. cycle;
g1 = A1 .. F0 .. E .. D0 .. cycle;
g2 = C0 .. D1 .. H .. F1 .. cycle;
T = shift(0.0, 0.0);
draw(T*g0);
draw(T*g1);
draw(T*g2);
label("$0000$", T*labelpos);

/*  This is the 1111 resolution.                                              */
g0 = A2 .. B .. C2 .. F2 .. cycle;
g1 = A3 .. G .. C3 .. D3 .. cycle;
g2 = D2 .. E .. F3 .. H .. cycle;
T = shift(4.0*xshift, 0.0);
draw(T*g0);
draw(T*g1);
draw(T*g2);
label("$1111$", T*labelpos);

/*  This the 0001 resolution.                                                 */
g0 = A2 .. F0 .. E .. D0 .. A3 .. G .. C1 .. B .. cycle;
g1 = C0 .. F1 .. H .. D1 .. cycle;
T = shift(xshift, 3.0*yshift);
draw(T*g0);
draw(T*g1);
label("$0001$", T*labelpos);

/*  This is the 1000 resolution.                                              */
g0 = reflect((0.0, 0.0), (1.0, 0.0))*g0;
g1 = reflect((0.0, 0.0), (1.0, 0.0))*g1;
T = shift(xshift, -3.0*yshift);
draw(T*g0);
draw(T*g1);
label("$1000$", T*labelpos);

/*  This is the 1011 resolution.                                              */
g0 = A2 .. B .. C2 .. F2 .. cycle;
g1 = A3 .. D0 .. E .. F3 .. H .. D1 ..C0 .. G .. cycle;
T = shift(3.0*xshift, yshift);
draw(T*g0);
draw(T*g1);
label("$1011$", T*labelpos);

/*  This is the 1101 resolution.                                              */
g0 = reflect((0.0, 0.0), (0.0, 1.0))*g0;
g1 = reflect((0.0, 0.0), (0.0, 1.0))*g1;
T = shift(3.0*xshift, -yshift);
draw(T*g0);
draw(T*g1);
label("$1101$", T*labelpos);

/*  This is the 1001 resolution.                                              */
g0 = A2 .. B .. C2 .. F1 .. H .. D1 .. C3 .. G .. A3 .. D0 .. E .. F0 .. cycle;
T = shift(2.0*xshift, -yshift);
draw(T*g0);
label("$1001$", T*labelpos);

