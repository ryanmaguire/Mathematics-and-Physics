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

/*  PDF works best in LaTeX, so use this.                                     */
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(128);

/*  Default pen used for drawing.                                             */
defaultpen(black + linewidth(0.6pt) + fontsize(7pt));

/*  Projection of the figure-eight parameterization onto the xy-plane.        */
pair figeight(real t)
{
    real c2t = cos(2.0*t);
    real c3t = cos(3.0*t);
    real s3t = sin(3.0*t);
    real factor = 2.0 + c2t;
    return (c3t*factor, s3t*factor);
}

/*  Draw the knot in pieces to mimic crossings.                               */
draw(graph(figeight, 0.0, 0.51, operator ..));
draw(graph(figeight, 0.54, 2.08, operator ..));
draw(graph(figeight, 2.11, 3.65, operator ..));
draw(graph(figeight, 3.68, 5.22, operator ..));
draw(graph(figeight, 5.255, 2.0*pi, operator ..));

/*  Label the crossings.                                                      */
label("$0$", figeight(pi/6.0) + (0.0, 0.3));
label("$1$", figeight(4.0*pi/3.0) + (0.3, 0.0));
label("$2$", figeight(pi/3.0) + (-0.3, 0.0));
label("$3$", figeight(7.0*pi/6.0) + (0.0, -0.3));