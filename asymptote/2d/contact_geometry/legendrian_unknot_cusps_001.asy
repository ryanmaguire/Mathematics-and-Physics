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

/*  Needed for making the output a PDF file.                                  */
import settings;

/*  Used for drawing parametric equations.                                    */
import graph;

/*  PDF works best in LaTeX, so use this.                                     */
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(256);

/*  Projection of the Legendrian unknot parameterization onto the xz plane.   */
pair f(real t)
{
    return (cos(t), sin(t)^3);
}

/*  Draw in the arcs of the trefoil.                                          */
draw(graph(f, 0.0, 2.0*pi));
