
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

/*  PDF works best in LaTeX, so use this.                                     */
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(128);

/*  Projection of the trefoil parameterization onto the xy plane.             */
pair tref(real t)
{
    return (2*sin(2*t)-sin(t), 2*cos(2*t)+cos(t));
}

/*  Draw in the arcs of the trefoil.                                          */
draw(graph(tref, -0.75, 1.315));
draw(scale(1.1)*graph(tref, -0.773, 1.292));

draw(graph(tref, 1.345, 3.41));
draw(scale(1.1)*graph(tref, 1.32, 3.388));

draw(graph(tref, 3.44, 5.505));
draw(scale(1.1)*graph(tref, 3.415, 5.48));

