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
size(128);

import settings;
settings.outformat = "pdf";

/*  Value for the edge of the square.                                         */
real edge = 1.5;

/*  Coordinates for the link.                                                 */
real r = 0.1;

pair A0 = (-edge, 0.0);
pair A1 = (0.0, edge);
pair A2 = (edge, 0.0);
pair A3 = (0.0, -edge);

int n, m;
int N = 2;

/*  Pairs for the square representing the torus.                              */
pair B0 = (-edge, -edge);
pair B1 = (edge, -edge);
pair B2 = (-edge, edge);
pair B3 = (edge, edge);
pair P0, P1, P2, P3;
pair V0, V1, V2, V3;
pair O;
transform T;
path g;

for (m = 0; m < N; ++m)
{
    for (n = 0; n < N; ++n)
    {
        O = (2.0*edge*m, 2.0*edge*n);
        T = shift(2.0*edge*m, 2.0*edge*n);
        P0 = T*A0;
        P1 = T*A1;
        P2 = T*A2;
        P3 = T*A3;

        V0 = T*B0;
        V1 = T*B1;
        V2 = T*B2;
        V3 = T*B3;

        /*  Draw in the link.                                                 */
        draw(P0 -- P2);
        draw(P1 -- P3);

        filldraw(circle(O, r), blue, black);

        /*  Draw in lines to indicate the square.                             */
        draw(V0 -- V1, blue + linewidth(1.0));
        draw(V2 -- V3, blue + linewidth(1.0));
        draw(V0 -- V2, red + linewidth(1.0));
        draw(V1 -- V3, red + linewidth(1.0));
    }
}

g = (0.0, 0.0) -- (2.0*edge, 0.0) -- (2.0*edge, 2.0*edge) -- (0.0, 2.0*edge) -- cycle;
filldraw(g, grey + opacity(0.5), black);
