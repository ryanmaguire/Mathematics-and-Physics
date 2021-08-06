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

/*  Size of the figure.                                                       */
size(256);
import settings;
settings.outformat = "pdf";

/*  The value 2*pi / 6.                                                       */
real TWO_PI_BY_SIX = 1.0471975511965976;

/*  The angle made with the x axis and the first point.                       */
real theta = pi / 6.0;

/*  Function for drawing a hexagon.                                           */
void draw_hex(pair Center, real radius)
{
    /*  Pairs for the hexagon.                                                */
    pair[] V;

    /*  Variable for indexing.                                                */
    int n;

    /*  Path for the hexagon.                                                 */
    path g;

    /*  Compute the points for the hexagon.                                   */
    for (n = 0; n < 6; ++n)
        V[n] = Center + scale(radius)*expi(TWO_PI_BY_SIX*n + theta);

    /*  Start the path.                                                       */
    g = V[0] -- V[1];

    /*  Construct the path.                                                   */
    for (n = 1; n < 6; ++n)
        g = g -- V[n];

    /*  Finish the cycle.                                                     */
    g = g -- cycle;

    /*  Draw the hexagon.                                                     */
    filldraw(g, white, black);
}
/*  End of draw_hex.                                                          */

/*  Variables for indexing.                                                   */
int m, n;

/*  Size of the grid (it will be N hexes wide and N hexes diagonal.           */
int N = 7;

/*  Radii of the hexagons.                                                    */
real r = 1.0;

/*  Width of the hexagon.                                                     */
real outter_width = r*cos(theta);

/*  Transform for shifting later.                                             */
transform T;

/*  Shift factors used to tile the plane with hexagons.                       */
pair dx = (2.0*outter_width, 0.0);
pair ds = scale(2.0*outter_width)*expi(0.6666667*pi);

/*  Pair for the origin.                                                      */
pair O = (0.0, 0.0);

/*  Pairs for drawing the background colors.                                  */
pair mid = shift(scale(0.5*N)*ds)*O;
pair A0 = O - ds - dx;
pair B0 = A0 + scale(N+1.0)*ds;
pair C0 = B0 + scale(N+1.0)*dx;
pair D0 = A0 + scale(N+1.0)*dx;

pair A1 = O;
pair B1 = shift(scale(N-1)*ds)*O;
pair C1 = shift(scale(N-1)*(dx+ds))*O;
pair D1 = shift(scale(N-1)*dx)*O;

/*  Draw in background colors for the edge of the board.                      */
filldraw(A0 -- A1 -- B1 -- B0 -- cycle, blue);
filldraw(A0 -- A1 -- D1 -- D0 -- cycle, red);
filldraw(D0 -- D1 -- C1 -- C0 -- cycle, blue);
filldraw(B0 -- B1 -- C1 -- C0 -- cycle, red);


/*  Draw the hex board.                                                       */
for (m = 0; m < N; ++m)
{
    for (n = 0; n < N; ++n)
    {
        /*  Compute the current shift factor.                                 */
        T = shift(scale(m)*dx + scale(n)*ds);

        /*  Draw the current hexagon.                                         */
        draw_hex(T*O, r);
    }
}


