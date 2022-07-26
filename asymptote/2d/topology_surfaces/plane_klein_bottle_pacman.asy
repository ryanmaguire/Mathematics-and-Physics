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

/*  Points for the square.                                                    */
pair A = (0.0, 0.0);
pair B = (1.0, 0.0);
pair C = (1.0, 1.0);
pair D = (0.0, 1.0);

/*  Centers of the two Pac-Man.                                               */
pair P0 = (0.6, 0.6);
pair P1a = (1.0, 0.3);
pair P1b = (0.0, 0.3);
pair P2a = (0.75, 1.0);
pair P2b = (0.25, 0.0);

/*  Radii of the Pac-Men.                                                     */
real r = 0.1;
real rDot = 0.015;

/*  Displacement for the eyes.                                                */
pair ds = (0.4*r, 0.6*r);

int m, n;
int N = 8;

transform T;
transform ref = reflect(scale(0.5)*(A+B), scale(0.5)*(C+D));

/*  Positions for the arrows.                                                 */
position pos1 = 0.47;
position pos2 = 0.57;

for (m = 0; m < N; ++m)
{
    for (n = 0; n < N; ++n)
    {
        T = shift(m, n);

        /*  Draw the square.                                                  */
        if (n % 2 == 0)
            draw(T*(B -- A), blue, MidArrow(arsize));
        else
            draw(T*(A -- B), blue, MidArrow(arsize));

        draw(T*(B -- C), red, Arrow(arsize, pos1), Arrow(arsize, pos2));
        draw(T*(A -- D), red, Arrow(arsize, pos1), Arrow(arsize, pos2));

        /*  This one is flipped as well.                                      */
        if (n % 2 == 0)
        {
            /*  Draw some Pac-Men.                                            */
            filldraw(T*(P0 -- arc(P0, r, 30, 330) -- cycle), yellow);
            filldraw(circle(T*(P0 + ds), rDot), black, black);

            /*  This Pac-Man is "cut" in half by the edge of the square.      */
            filldraw(T*(P1a -- arc(P1a, r, 90, 270) -- cycle), blue);
            filldraw(T*(arc(P1b, r, 90, 30) -- P1b -- arc(P1b, r, 330, 270) -- cycle), blue);
            filldraw(circle(T*(P1b + ds), rDot), black, black);

            filldraw(T*(P2a -- arc(P2a, r, -30, -180) -- cycle), red);
            filldraw(T*(P2b -- arc(P2b, r, 150, 0) -- cycle), red);
            filldraw(T*circle(P2b + (-ds.x, ds.y), rDot), black, black);
        }
        else
        {
            /*  Draw some Pac-Men.                                            */
            filldraw(T*(ref*(P0 -- arc(P0, r, 30, 330) -- cycle)), yellow);
            filldraw(T*(ref*(circle(P0 + ds, rDot))), black, black);

            /*  This Pac-Man is "cut" in half by the edge of the square.      */
            filldraw(T*(ref*(P1a -- arc(P1a, r, 90, 270) -- cycle)), blue);
            filldraw(T*(ref*(arc(P1b, r, 90, 30) -- P1b -- arc(P1b, r, 330, 270) -- cycle)), blue);
            filldraw(T*(ref*(circle(P1b + ds, rDot))), black, black);

            filldraw(T*(ref*(P2a -- arc(P2a, r, -30, -180) -- cycle)), red);
            filldraw(T*(ref*(P2b -- arc(P2b, r, 150, 0) -- cycle)), red);
            filldraw(T*(ref*circle(P2b + (-ds.x, ds.y), rDot)), black, black);
        }
    }
}

for (m = 0; m < N; ++m)
    draw(shift(m, n)*(B -- A), blue, MidArrow(arsize));
