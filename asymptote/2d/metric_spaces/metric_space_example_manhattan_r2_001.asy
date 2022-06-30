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

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(256);

/*  Default pen for drawings.                                                 */
defaultpen(black + linewidth(0.7pt));

int m, n;
int n_roads = 6;
real road_width = 0.15;
pair A, B, C, D;
pen grayp = gray(0.5);
pair P = (1.0, 2.0);
pair Q = (3.0, 3.0);

for (n = 0; n < n_roads; ++n)
{
    for (m = 0; m < n_roads; ++m)
    {
        A = (-0.5, n - road_width);
        B = (-0.5, n + road_width);
        C = (n_roads - 0.5, n + road_width);
        D = (n_roads - 0.5, n - road_width);
        filldraw(A -- B -- C -- D -- cycle, grayp, invisible);

        A = (n - road_width, -0.5);
        B = (n + road_width, -0.5);
        C = (n + road_width, n_roads - 0.5);
        D = (n - road_width, n_roads - 0.5);
        filldraw(A -- B -- C -- D -- cycle, grayp, invisible);
    }
}

draw(P -- (Q.x, P.y) -- Q);
dot(P);
dot(Q);
