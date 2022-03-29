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
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Draw a parallel circuit. This figure is for an intro course in        *
 *      electromagnetism or in circuit theory.                                *
 ******************************************************************************/

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(128);

/*  Pen for the circuit.                                                      */
defaultpen(black + linewidth(0.6pt) + fontsize(6pt));

/*  Radius of the circles.                                                    */
real r = 0.1;

/*  Draw the circuit.                                                         */
draw((0.0, 0.0) -- (1.0, 0.0));
draw((1.0, -1.0) -- (1.0, 1.0));
draw((1.0, 1.0) -- (2.0, 1.0));
draw((1.0, -1.0) -- (2.0, -1.0));
draw((2.0, 0.5) -- (2.0, 1.5));
draw((2.0, -0.5) -- (2.0, -1.5));
draw((2.5, 0.5) -- (2.5, 1.5));
draw((2.5, -0.5) -- (2.5, -1.5));
draw((2.5, 1.0) -- (3.5, 1.0));
draw((2.5, -1.0) -- (3.5, -1.0));
draw((3.5, -1.0) -- (3.5, 1.0));
draw((3.5, 0.0) -- (4.5, 0.0));

/*  Mark the start and end of the circuit with circles.                       */
filldraw(circle((0.0, 0.0), r), white, black);
filldraw(circle((4.5, 0.0), r), white, black);

/*  Label the plates.                                                         */
label("$C_{1}$", (2.25, 1.5));
label("$C_{2}$", (2.25, -1.5));
