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
defaultpen(black + linewidth(0.4pt) + fontsize(8pt));

margin margins = TrueMargin(0.2cm, 0.2cm);
real arsize = 5bp;
int n;
real a, b;
int n_ints = 10;
pair A, B, C;

real f(int n)
{
    if (n % 2 == 0)
        return 0.5*n;
    else
        return (-1-n)/2;
}

label("$0$", (0.0, 0.0), N);
dot((0.0, 0.0));

for (n = 0; n < n_ints; ++n)
{
    b = f(n+1);

    A = (a, 0.0);
    B = (b, 0.0);
    if (b > a)
        C = (0.5*(a + b), 0.3 + 0.3*n);
    else
        C = (0.5*(a + b), -(0.3 + 0.3*n));

    draw(A .. C .. B, SharpArrow(arsize), margins);

    if (b < 0)
        label("$"+string(b)+"$", B, NW);
    else
        label("$"+string(b)+"$", B, NE);

    a = b;
    dot((a, 0.0));
}
