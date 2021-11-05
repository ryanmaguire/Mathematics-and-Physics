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

/*  Draw in the arcs of the trefoil.                                          */
draw(graph(tref, -0.75, -0.35), MidSharpArrow(arsize));
draw(graph(tref, -0.35, 1.29), MidSharpArrow(arsize));
draw(graph(tref, 1.35, 2.90), MidSharpArrow(arsize));
draw(graph(tref, 2.90, 3.38), MidSharpArrow(arsize));
draw(graph(tref, 3.45, 4.90), MidSharpArrow(arsize));
draw(graph(tref, 4.90, 5.48), MidSharpArrow(arsize));

/*  Label the crossings.                                                      */
label("$0+$", scale(r)*tref(a));
label("$2+$", scale(r)*tref(b));
label("$1+$", scale(r)*tref(c));

