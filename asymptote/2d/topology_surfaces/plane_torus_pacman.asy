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

import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(512);

/*  Size of the arrowhead.                                                    */
real arsize = 5bp;

/*  Variables for indexing.                                                   */
int m, n;

/*  Number of squares to draw.                                                */
int N = 8;

/*  Pairs used for the drawing later.                                         */
pair A, B, C, D, P0, P1a, P1b;

/*  Transform for shifting the square around.                                 */
transform T;

/*  Points for the square.                                                    */
pair V0 = (0.0, 0.0);
pair V1 = (1.0, 0.0);
pair V2 = (1.0, 1.0);
pair V3 = (0.0, 1.0);

/*  Centers of the two Pac-Man.                                               */
pair W0 = (0.6, 0.6);
pair W1a = (1.0, 0.3);
pair W1b = (0.0, 0.3);

/*  Radii of the Pac-Men.                                                     */
real r = 0.1;

/*  Displacement for the eyes.                                                */
pair ds = (0.4*r, 0.6*r);

/*  Positions for the arrows.                                                 */
position pos1 = 0.47;
position pos2 = 0.57;

for (m = 0; m < N; ++m)
{
    for (n = 0; n < N; ++n)
    {
        /*  Compute the current shift.                                        */
        T = shift(m, n);

        /*  Calculate the location of the points of this square and Pac-Men.  */
        A = T * V0;
        B = T * V1;
        C = T * V2;
        D = T * V3;
        P0 = T * W0;
        P1a = T * W1a;
        P1b = T * W1b;

        /*  Draw the square.                                                  */
        draw(A -- B, blue, MidArrow(arsize));
        draw(D -- C, blue, MidArrow(arsize));
        draw(B -- C, red, Arrow(arsize, pos1), Arrow(arsize, pos2));
        draw(A -- D, red, Arrow(arsize, pos1), Arrow(arsize, pos2));

        /*  Draw some Pac-Men.                                                */
        filldraw(P0 -- arc(P0, r, 30, 330) -- cycle, yellow, black);
        dot(P0 + ds);

        /*  This Pac-Man is "cut" in half by the edge of the square.          */
        filldraw(arc(P1a, r, 90, 270) -- cycle, green, black);
        filldraw(arc(P1b, r, 90, 30) -- P1b -- arc(P1b, r, 330, 270) -- cycle,
                 green, black);
        dot(P1b + ds);
    }
}
