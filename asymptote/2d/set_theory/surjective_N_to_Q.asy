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
defaultpen(black + linewidth(0.4pt) + fontsize(10pt));

margin margins = TrueMargin(0.3cm, 0.35cm);
real arsize = 5bp;
int n = 1;
int m = 1;
int N = 4;
real y;
pair P = (0, N-1);
pair Q = (1, N-1);
draw(P -- Q, SharpArrow(arsize), margins);
label("$\frac{0}{1}$", (0.0, N - 1.0));
label("$\frac{1}{1}$", (1.0, N - 1.0));

while (true)
{
    while (n != m+1)
    {
        P = Q;
        n = n + 1;
        Q = (m, N-n);
        draw(P -- Q, SharpArrow(arsize), margins);
        label("$\frac{"+string(m)+"}{"+string(n)+"}$", Q);
    }
    while (m != 1-n)
    {
        P = Q;
        m = m - 1;
        Q = (m, N-n);
        draw(P -- Q, SharpArrow(arsize), margins);
        label("$\frac{"+string(m)+"}{"+string(n)+"}$", Q);
    }
    while (n != 1)
    {
        P = Q;
        n = n - 1;
        Q = (m, N-n);
        draw(P -- Q, SharpArrow(arsize), margins);
        label("$\frac{"+string(m)+"}{"+string(n)+"}$", Q);
    }

    if (m == -N)
        break;

    m = abs(m) + 1;
    y = N + 0.3*fabs(m) - 0.9;
    P = Q;
    Q = (m, N - 1.0);
    draw(P -- (P.x, y) -- (Q.x, y) -- Q, SharpArrow(arsize), margins);
    label("$\frac{"+string(m)+"}{"+string(n)+"}$", Q);
}
