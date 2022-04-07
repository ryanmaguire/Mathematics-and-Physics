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

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(128);

/*  Pen for the rectangles.                                                   */
pen rectpen = green + linewidth(0.7pt);

/*  Pen for the knot.                                                         */
pen knotpen = blue + linewidth(0.5pt);

/*  Size of the arrow heads.                                                  */
real arsize = 3bp;

/*  Distances for the rectangles.                                             */
real close = 0.3;
real far = 1.0;
real height = 1.0;

/*  Height for the crossings in the diagram.                                  */
real cross_high = 0.7*height;
real cross_low = 0.3*height;

/*  Points for the left rectangle.                                            */
pair AL = (-far, height);
pair BL = (-far, -height);
pair CL = (-close, -height);
pair DL = (-close, height);

/*  Points for the left rectangle.                                            */
pair AR = (far, height);
pair BR = (far, -height);
pair CR = (close, -height);
pair DR = (close, height);

/*  Position of points for the top crossing thing.                            */
pair X0 = (-close, 0.3);
pair X1 = (-close, 0.7);
pair Y0 = (close, 0.7);
pair Y1 = (close, 0.3);

/*  Position of points for the bottom crossing thing.                         */
pair X2 = (-close, -0.3*height);
pair X3 = (-close, -0.7*height);
pair Y2 = (close, -0.7*height);
pair Y3 = (close, -0.3*height);

/*  Midpoints of the rectangle used for drawing Bezier cubics later.          */
pair MidFarL = (-0.3*close - 0.7*far, 0.0);
pair MidCloseL = (-0.7*close - 0.3*far, 0.0);

/*  Points in the center of the image for the Bezier cubics.                  */
pair MidTopA = (0.0, 0.4*height);
pair MidTopB = (0.0, 0.6*height);
pair MidBottomA = (0.0, -0.6*height);
pair MidBottomB = (0.0, -0.4*height);

/*  Draw the left rectangle.                                                  */
draw(AL -- BL -- CL -- DL -- cycle, rectpen);

/*  Draw the right rectangle.                                                 */
draw(AR -- BR -- CR -- DR -- cycle, rectpen);

/*  Draw the parts of the knot/link inside of the rectangle.                  */
path g = Y0{E} .. Y1{W} .. MidTopA{W} .. X0{W} ..
    MidCloseL{S} .. X2{E} .. MidBottomB{E} .. Y3{E} ..
    Y2{W} .. MidBottomA{W} .. X3{W} .. MidFarL{N} .. X1{E} ..
    MidTopB{E} .. cycle{E};

draw(reflect((0.0, 0.0), (0.0, 1.0))*g, knotpen);
