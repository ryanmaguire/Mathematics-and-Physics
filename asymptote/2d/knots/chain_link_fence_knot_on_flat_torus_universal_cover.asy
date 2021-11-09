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

/*  PDF works best in LaTeX, so use this.                                     */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(512);

/*  Value for the edge of the square.                                         */
real edge = 1.5;

/*  Coordinates for the link.                                                 */
real r = 0.1;

pair P0 = (-edge, 0.0);
pair P1 = (0.0, edge);
pair P2 = (edge, 0.0);
pair P3 = (0.0, -edge);

pair A = (0.3*edge, -0.3*edge);
pair B = scale(-1.0)*A;

pair C = (-0.4*edge, -0.4*edge);
pair D = scale(-1.0)*C;

/*  Pairs for the square representing the torus.                              */
pair V0 = (-edge, -edge);
pair V1 = (edge, -edge);
pair V2 = (-edge, edge);
pair V3 = (edge, edge);

int n, m;
int N = 6;
transform T;

for (m = 0; m < N; ++m)
{
    for (n = 0; n < N; ++n)
    {
        T = shift(2.0*edge*m, 2.0*edge*n);

        /*  Draw in the link.                                                 */
        draw(T*(P0{SE} .. A{NE}));
        filldraw(T*circle(C, r), white, white);
        draw(T*(P2{NW} .. B .. P3{SE}));
        filldraw(T*circle(D, r), white, white);
        draw(T*(A{NE} .. P1{NW}));

        /*  Draw in lines to indicate the square.                             */
        draw(T*(V0 -- V1), blue + linewidth(1.0));
        draw(T*(V2 -- V3), blue + linewidth(1.0));
        draw(T*(V0 -- V2), red + linewidth(1.0));
        draw(T*(V1 -- V3), red + linewidth(1.0));
    }
}
