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

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Used for drawing parametric equations.                                    */
import graph;

/*  PDF works best in LaTeX, so use this.                                     */
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(256);

/*  Default pen for drawings and text.                                        */
defaultpen(black + linewidth(0.6pt) + fontsize(7pt));

real r0 = 0.4;
real r1 = 0.6;
real r2 = 1.5;
real r3 = 0.5*(r0 + r1);
real xshift = 4.5;
real yshift = 0.8660254037844386*xshift;
real arsize = 5bp;

real a = 30.0*pi/180.0;
real b = 0.5*pi;
real c = 150.0*pi/180.0;
real d = 210.0*pi/180.0;
real e = 1.5*pi;
real f = 330.0*pi/180.0;
real dtheta = 0.5;

pair A0 = scale(r0)*expi(a);
pair A1 = scale(r1)*expi(a);
pair A2 = scale(r3)*expi(a+dtheta);
pair A3 = scale(r3)*expi(a-dtheta);
pair B = scale(r2)*expi(b);
pair C0 = scale(r0)*expi(c);
pair C1 = scale(r1)*expi(c);
pair C2 = scale(r3)*expi(c+dtheta);
pair C3 = scale(r3)*expi(c-dtheta);
pair D = scale(r2)*expi(d);
pair E0 = scale(r0)*expi(e);
pair E1 = scale(r1)*expi(e);
pair E2 = scale(r3)*expi(e+dtheta);
pair E3 = scale(r3)*expi(e-dtheta);
pair F = scale(r2)*expi(f);
pair labelpos = scale(r2)*expi(c);

path g0 = A1 .. B .. C1 .. D .. E1 .. F .. cycle;
path g1 = A0 .. C0 .. E0 .. cycle;
path g2;
pen whitepen = white + linewidth(2.4pt);

margin diagmarg = TrueMargin(1.0cm, 1.0cm);
margin horimarg = TrueMargin(0.9cm, 0.9cm);

/*  Projection of the trefoil parameterization onto the xy plane.             */
pair tref(real t)
{
    return (sin(2*t)-0.5*sin(t), cos(2*t)+0.5*cos(t));
}

/*  Draw in the arcs of the trefoil.                                          */
draw(shift(0.0, yshift)*graph(tref, -0.73, 1.28));
draw(shift(0.0, yshift)*graph(tref, 1.36, 3.37));
draw(shift(0.0, yshift)*graph(tref, 3.46, 5.46));

/*  Label the crossings.                                                      */
label("$3$", shift(0.0, yshift)*(scale(1.4)*tref(pi/4.0)));
label("$1$", shift(0.0, yshift)*(scale(1.4)*tref(pi/4.0+2.0*pi/3.0)));
label("$2$", shift(0.0, yshift)*(scale(1.4)*tref(pi/4.0+4.0*pi/3.0)));

draw(g0);
draw(g1);

g0 =  A2 .. B .. C1 .. D .. E1 .. F .. A3 .. E0 .. C0 .. cycle;
draw(shift(xshift, yshift)*g0);

g0 = rotate(-120)*g0;
draw(shift(xshift, 0.0)*g0);

g0 = rotate(-120)*g0;
draw(shift(xshift, -yshift)*g0);

g0 = C2 .. D .. E1 .. F .. A3 .. E0 .. cycle;
g1 = A2 .. B .. C3 .. cycle;

g0 = rotate(-120)*g0;
g1 = rotate(-120)*g1;
draw(shift(2.0*xshift, yshift)*g0);
draw(shift(2.0*xshift, yshift)*g1);

g0 = rotate(120)*g0;
g1 = rotate(120)*g1;
draw(shift(2.0*xshift, 0.0)*g0);
draw(shift(2.0*xshift, 0.0)*g1);

g0 = rotate(120)*g0;
g1 = rotate(120)*g1;
draw(shift(2.0*xshift, -yshift)*g0);
draw(shift(2.0*xshift, -yshift)*g1);

g0 = A2 .. B .. C3 .. cycle;
g1 = C2 .. D .. E3 .. cycle;
g2 = E2 .. F .. A3 .. cycle;
draw(shift(3.0*xshift, 0.0)*g0);
draw(shift(3.0*xshift, 0.0)*g1);
draw(shift(3.0*xshift, 0.0)*g2);

draw((0.0, 0.0) -- (xshift, yshift), SharpArrow(arsize), diagmarg);
draw((0.0, 0.0) -- (xshift, -yshift), SharpArrow(arsize), diagmarg);
draw((0.0, 0.0) -- (xshift, 0.0), SharpArrow(arsize), horimarg);
draw((xshift, 0.0) -- (2.0*xshift, yshift), SharpArrow(arsize), diagmarg);
draw((xshift, 0.0) -- (2.0*xshift, -yshift), SharpArrow(arsize), diagmarg);
draw((2.0*xshift, yshift) -- (3.0*xshift, 0.0), SharpArrow(arsize), diagmarg);
draw((2.0*xshift, -yshift) -- (3.0*xshift, 0.0), SharpArrow(arsize), diagmarg);
draw((xshift, yshift) -- (2.0*xshift, 0.0), whitepen, diagmarg);
draw((xshift, -yshift) -- (2.0*xshift, 0.0), whitepen, diagmarg);
draw((xshift, yshift) -- (2.0*xshift, 0.0), SharpArrow(arsize), diagmarg);
draw((xshift, -yshift) -- (2.0*xshift, 0.0), SharpArrow(arsize), diagmarg);
draw((2.0*xshift, 0.0) -- (3.0*xshift, 0.0), SharpArrow(arsize), horimarg);
draw((xshift, yshift) -- (2.0*xshift, yshift), SharpArrow(arsize), horimarg);
draw((xshift, -yshift) -- (2.0*xshift, -yshift), SharpArrow(arsize), horimarg);

label("$AAA$", labelpos);
label("$AAB$", shift(xshift, yshift)*labelpos);
label("$ABA$", shift(xshift, 0.0)*labelpos);
label("$BAA$", shift(xshift, -yshift)*labelpos);
label("$ABB$", shift(2.0*xshift, yshift)*labelpos);
label("$BBA$", shift(2.0*xshift, -yshift)*labelpos);
label("$BAB$", shift(2.0*xshift, 0.0)*labelpos);
label("$BBB$", shift(3.0*xshift, 0.0)*labelpos);
