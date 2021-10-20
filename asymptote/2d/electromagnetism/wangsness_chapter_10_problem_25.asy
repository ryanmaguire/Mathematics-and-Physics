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

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output.                                                       */
size(128);

/*  Pen for drawing.                                                          */
pen dpen = black + linewidth(0.4pt);

/*  Pen for axes                                                              */
pen apen = black + linewidth(0.8pt);

/*  Font size for labels.                                                     */
real fsize = 7pt;

/*  Some lengths.                                                             */
real xlength = 4.0;
real ylength = 3.0;
real d = 1.0;
real dx = 0.3;
real rx = 0.2;
real ry = 0.3;

/*  Points for the x and y axes.                                              */
pair[] XAxes = {(0.0, 0.0), (xlength, 0.0)};
pair[] YAxes = {(0.0, 0.0), (0.0, ylength)};

/*  Points marking the line segment.                                          */
pair A = (d, ylength);
pair B = (d, 0.0);

/*  Locations of the centers of the two ellipses.                             */
pair center0 = (-dx, 0.5 * ylength);
pair center1 = (dx, 0.5 * ylength);

/*  The tops and bottoms of the two ellipses.                                 */
pair top0 = center0 + (0.0, ry);
pair bottom0 = center0 - (0.0, ry);

pair top1 = center1 + (0.0, ry);
pair bottom1 = center1 - (0.0, ry);

/*  Draw the axes.                                                            */
draw(XAxes[0] -- XAxes[1], apen);
draw(YAxes[0] -- YAxes[1], apen);

/*  Draw in the line.                                                         */
draw(A -- B, dpen);

/*  Draw in two ellipses for region Delta a.                                  */
draw(ellipse(center0, rx, ry), dpen);
draw(ellipse(center1, rx, ry),  dpen);

/*  Draw in lines connecting the two ellipses to make a cylinder.             */
draw(top0 -- top1, dpen);
draw(bottom0 -- bottom1, dpen);

/*  Label everything.                                                         */
label("$x$", XAxes[1], SW, fontsize(fsize));
label("$\Delta{a}$", center1, fontsize(fsize));
label("$d$", (0.5*d, 0.0), N, fontsize(fsize));
label("$\kappa_{e}$", (0.5*d, ylength), S, fontsize(fsize));
label("$\mathrm{Area}=A$", (0.5*xlength, 0.5*ylength), fontsize(fsize));
