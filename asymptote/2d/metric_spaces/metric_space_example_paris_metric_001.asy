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
int n_roads = 8;
real road_width = 0.12;
real road_start = 0.3;
real road_end = 2.2;
pair A, B, C, D;
pen grayp = gray(0.5);
pair P = (1.0, 1.0);
pair Q = (1.0, -1.0);
real x, y, theta;
filldraw(circle(0.0, 1.2*road_start), grayp, invisible);

for (n = 0; n < n_roads; ++n)
{
    theta = 2.0 * pi * n / n_roads;
    x = cos(theta);
    y = sin(theta);
    A = (road_start*x + road_width*y, road_start*y - road_width*x);
    B = (road_start*x - road_width*y, road_start*y + road_width*x);
    C = (road_end*x - road_width*y, road_end*y + road_width*x);
    D = (road_end*x + road_width*y, road_end*y - road_width*x);
    filldraw(A -- B -- C -- D -- cycle, grayp, invisible);
}

draw(P -- (0.0, 0.0) -- Q);
dot(P);
dot(Q);
