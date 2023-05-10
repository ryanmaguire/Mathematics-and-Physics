/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************/

import settings;
import palette;

if (settings.render < 0)
    settings.render = 8;

settings.outformat = "pdf";
size(1024, 1024);

/*  Variable for indexing the random walk.                                    */
int n;

/*  Size of the random walk. 32765 is the total number of distinct colors in  *
 *  asymptotes rainbow pen.                                                   */
int max = 32765;

/*  The random walk starts at the origin.                                     */
pair A = (0.0, 0.0);
pair B = (0.0, 0.0);

/*  Pen for coloring with a rainbow gradient.                                 */
pen[] mypen = Rainbow(max);

/*  Function for returning a random point on the unit circle.                 */
pair Rpair()
{
    real x = (real)(rand()/randMax);
    return (cos(x*2.0*pi), sin(x*2.0*pi));
}

/*  Perform the random walk.                                                  */
for (n=0; n<max; ++n)
{
    B = A + Rpair();
    draw(A--B, mypen[n]);
    A = B;
}

/*  Color the background black.                                               */
shipout(bbox(currentpicture, Black, Fill));


