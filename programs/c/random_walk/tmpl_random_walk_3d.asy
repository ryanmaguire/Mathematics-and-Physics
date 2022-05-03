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
import three;
import tube;
import graph3;

if (settings.render < 0)
    settings.render = 8;

settings.outformat = "pdf";
size(1024, 1024);

/*  The size of the walk. Very high values causes a segmentation fault. This  *
 *  may be a problem with the version of asymptote I used while making this.  */
int max = 1000;

/*  Variable for indexing the walk.                                           */
int n;

/*  The walk starts at the origin.                                            */
triple A = (0.0, 0.0, 0.0);
triple B;

/*  Pen for drawing a rainbow gradient.                                       */
pen[] mypen = Rainbow(max);

/*  Function for computing a random direction.                                */
triple Rtrip()
{
    int n = (int)floor(6.0 * (rand() / randMax));
    if (n == 0)
        return (1.0, 0.0, 0.0);
    else if (n == 1)
        return (-1.0, 0.0, 0.0);
    else if (n == 2)
        return (0.0, 1.0, 0.0);
    else if (n == 3)
        return (0.0, -1.0, 0.0);
    else if (n == 4)
        return (0.0, 0.0, 1.0);
    else
        return (0.0, 0.0, -1.0);
}

/*  Perform the random walk.                                                  */
for (n = 0; n < max; ++n)
{
    B = A + Rtrip();
    draw(A--B, mypen[n]);
    A = B;
}

/*  Draw the 3 axes.                                                          */
xaxis3(XZ()*"$x$", Bounds, red, InTicks(Label, 2, 2));
yaxis3(YZ()*"$y$", Bounds, red, InTicks(beginlabel=false, Label, 2, 2));
zaxis3(XZ()*"$z$", Bounds, red, InTicks);

