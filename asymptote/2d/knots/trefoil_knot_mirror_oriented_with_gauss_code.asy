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

/*  Used for drawing parametric equations.                                    */
import graph;

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  PDF works best in LaTeX, so use this.                                     */
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(128);

/*  Projection of the trefoil parameterization onto the xy plane.             */
pair tref(real t)
{
    return (2*sin(2*t)-sin(t), 2*cos(2*t)+cos(t));
}

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  Parameters for the labels.                                                */
real r = 1.4;
real a = pi/4.0;
real b = a + 2.0*pi/3.0;
real c = b + 2.0*pi/3.0;
real rDot = 0.05;

/*  Draw in the arcs of the trefoil.                                          */
draw(graph(tref, -1.29, 0.75), MidSharpArrow(arsize));
draw(graph(tref, 0.8, 2.85), MidSharpArrow(arsize));
draw(graph(tref, 2.9, 4.94), MidSharpArrow(arsize));
filldraw(circle(tref(pi), rDot), black, black);

/*  Label the crossings.                                                      */
label("$0$", scale(r)*tref(a));
label("$2$", scale(r)*tref(b));
label("$1$", scale(r)*tref(c));
label("start", scale(1.3)*tref(pi), fontsize(7pt));
label("O0 U1 O2 U0 O1 U2", (0.0, -2.8), fontsize(7pt));

