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
pen knotpen = black + linewidth(0.5pt);

/*  Size of the arrow heads.                                                  */
real arsize = 3bp;

/*  Distances for the rectangles.                                             */
real close = 0.3;
real far = 1.0;
real height = 1.0;

/*  Height for the crossings in the diagram.                                  */
real cross_high = 0.7*height;
real cross_low = 0.3*height;

/*  Angles the crossings make with the rectangles.                            */
real angle = atan(0.5*(cross_high - cross_low) / close) * 180.0/pi;

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
pair MidFarR = (0.3*close + 0.7*far, 0.0);
pair MidCloseR = (0.7*close + 0.3*far, 0.0);
pair MidFarL = (-MidFarR.x, 0.0);
pair MidCloseL = (-MidCloseR.x, 0.0);

/*  Draw the top crossing thing.                                              */
draw(X0 -- Y0, knotpen);

/*  Draw over the first line with with to give the appearance of the second   *
 *  line passing over it, like in most knot diagrams.                         */
draw(Y1 -- X1, white + linewidth(3.0pt));
draw(Y1 -- X1, knotpen);

/*  Draw the bottom crossing thing, same idea as before.                      */
draw(X2 -- Y2, knotpen);
draw(Y3 -- X3, white + linewidth(3.0pt));
draw(Y3 -- X3, knotpen);

/*  Draw the left rectangle.                                                  */
draw(AL -- BL -- CL -- DL -- cycle, rectpen);

/*  Draw the right rectangle.                                                 */
draw(AR -- BR -- CR -- DR -- cycle, rectpen);

/*  Draw the parts of the knot/link inside of the rectangle.                  */
draw(Y0{dir(angle)} .. MidFarR{dir(270.0)} .. Y2{dir(180.0-angle)}, knotpen);
draw(Y1{dir(-angle)} .. MidCloseR{dir(270.0)} .. Y3{dir(180.0+angle)}, knotpen);
draw(X0{dir(angle+180.0)} .. MidCloseL{dir(270.0)} .. X2{dir(-angle)}, knotpen);
draw(X1{dir(180.0-angle)} .. MidFarL{dir(270.0)} .. X3{dir(angle)}, knotpen);
