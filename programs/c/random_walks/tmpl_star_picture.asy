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

if (settings.render < 0)
    settings.render = 8;

settings.outformat = "pdf";
size(512, 512);

int n;
pair A, B;

for (n = 0; n < 10; ++n)
{
    if ((n % 2) == 0)
    	A = expi(2*pi*n / 5.0);
    else
    	A = expi(2*pi*(n+1) / 5.0);

    B = 0.5*expi((2*n+1)*pi / 5.0);
    draw(A--B);
}

