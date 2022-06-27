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

/*  Size of the output figure.                                                */
size(256);

/*  Default pen for drawing.                                                  */
defaultpen(black + linewidth(0.4pt) + fontsize(14pt));

margin margins = TrueMargin(0.5cm, 0.5cm);
real arsize = 5bp;
int n = 1;
int m = 1;
int N = 5;
pair P = (m, N-n);
pair Q;
bool up = false;

while (n <= N || m <= N)
{
    label("$\frac{"+string(m)+"}{"+string(n)+"}$", P);
    if (up)
    {
        if (n == 1)
        {
            ++m;
            up = false;
        }
        else
        {
            m = m + 1;
            n = n - 1;
        }
    }
    else
    {
        if (m == 1)
        {
            ++n;
            up = true;
        }
        else
        {
            m = m - 1;
            n = n + 1;
        }
    }

    Q = (m, N-n);
    draw(P -- Q, MidSharpArrow(arsize), margins);
    P = Q;
}
clip((-0.7, N+0.7) -- (N+0.7, N+0.7) -- (N+0.7, -0.7) -- (-0.7, -0.7) -- cycle);
