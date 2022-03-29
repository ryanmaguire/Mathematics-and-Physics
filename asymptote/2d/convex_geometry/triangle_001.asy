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
 *      Figure from convex geometry notes. This shows a triangle with a       *
 *      perpendicular to the x-axis drawn. All sides and lengths are labelled.*
 ******************************************************************************/

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(128);

/*  Default pen used for drawing.                                             */
defaultpen(black + linewidth(0.4pt) + fontsize(7pt));

/*  Function for computing the midpoint of two points in the plane.           */
pair MidPoint(pair A, pair B)
{
    return scale(0.5)*(A + B);
}
/*  End of MidPoint.                                                          */

/*  Locations of the points on the triangle, and the origin.                  */
pair O  = (0.0, 0.0);
pair X0 = (-1.0, 0.0);
pair Y0 = (0.0, 1.0);
pair Z0 = (0.3, 0.0);

/*  Radius of the arc of the circle used to represent an angle.               */
real r = 0.2;

/*  The angle to be drawn in the triangle.                                    */
real angle = atan((Y0.y - X0.y)/(Y0.x - X0.x));

/*  Draw the lines and label them.                                            */
draw("$a$", Y0 -- Z0, NE);
draw("$b$", Z0 -- X0, S);
draw("$c$", X0 -- Y0, NW);
draw("$h$", Y0 -- O,  SW);

/*  Draw the angle.                                                           */
draw("$\alpha$", arc(X0, r, 0, 180.0*angle/pi));

/*  And label the lines at their midpoints.                                   */
label("$\ell_{1}$", MidPoint(X0, O), N);
label("$\ell_{2}$", MidPoint(Z0, O), N);
