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

/*  Draw the image on a PDF file.                                             */
import settings;
import custom_arrows;
settings.outformat = "pdf";

/*  Default pen used for drawing.                                             */
defaultpen(black+linewidth(0.5pt)+fontsize(7pt));

/*  Default size of arrowheads.                                               */
real arsize = 5bp;

/* Size of the output figure.                                                 */
size(256);

/*  Pairs of points to draw arrows between.                                   */
pair O = (0, 0);
pair X = (1, 0);

/*  Path for the arrow.                                                       */
path g = O--X;

/*  Displacements used to shift the path.                                     */
real dy = -0.5;
real dx =  1.5;

/*  Loop through sharp plain arrow.                                           */
draw(shift(0*dx, 0*dy)*g, black, SharpArrow(arsize));
draw(shift(0*dx, 1*dy)*g, black, EndSharpArrow(arsize));
draw(shift(0*dx, 2*dy)*g, black, MidSharpArrow(arsize));
draw(shift(0*dx, 3*dy)*g, black, SharpArrows(arsize));
draw(shift(0*dx, 4*dy)*g, black, BeginSharpArrow(arsize));

/*  Loop through sharp dashed arrow.                                          */
draw(shift(1*dx, 0*dy)*g, black+dashed, SharpArrow(arsize));
draw(shift(1*dx, 1*dy)*g, black+dashed, EndSharpArrow(arsize));
draw(shift(1*dx, 2*dy)*g, black+dashed, MidSharpArrow(arsize));
draw(shift(1*dx, 3*dy)*g, black+dashed, SharpArrows(arsize));
draw(shift(1*dx, 4*dy)*g, black+dashed, BeginSharpArrow(arsize));

/*  Loop through plain stealth arrow.                                         */
draw(shift(2*dx, 0*dy)*g, black, SharpArrow(StealthHead, arsize));
draw(shift(2*dx, 1*dy)*g, black, EndSharpArrow(StealthHead, arsize));
draw(shift(2*dx, 2*dy)*g, black, MidSharpArrow(StealthHead, arsize));
draw(shift(2*dx, 3*dy)*g, black, SharpArrows(StealthHead, arsize));
draw(shift(2*dx, 4*dy)*g, black, BeginSharpArrow(StealthHead, arsize));

/*  Loop through dashed stealth arrow.                                        */
draw(shift(3*dx, 0*dy)*g, black+dashed, SharpArrow(StealthHead, arsize));
draw(shift(3*dx, 1*dy)*g, black+dashed, EndSharpArrow(StealthHead, arsize));
draw(shift(3*dx, 2*dy)*g, black+dashed, MidSharpArrow(StealthHead, arsize));
draw(shift(3*dx, 3*dy)*g, black+dashed, SharpArrows(StealthHead, arsize));
draw(shift(3*dx, 4*dy)*g, black+dashed, BeginSharpArrow(StealthHead, arsize));

