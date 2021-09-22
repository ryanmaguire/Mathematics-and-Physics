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

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the graph.                                                        */
size(256);

/*  Default pen for the function.                                             */
defaultpen(black + linewidth(0.4pt));

/*  Pen for the axes.                                                         */
pen apen = black + linewidth(0.7pt);

/*  Radius of a dot.                                                          */
real rdot = 0.005;

/*  Integers for looping over fractions.                                      */
int p, q;

/*  The maximum depth of the popcorn function.                                */
int max = 200;

/*  Variables for the x and y values of the points being plotted.             */
real x, y;

/*  Start and end values for the axes.                                        */
real xstart = -0.1;
real xend = 2.1;
real ystart = -0.1;
real yend = 1.1;

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  Labels for the axes.                                                      */
Label x_label = Label("$x$", position = 1.0);
Label y_label = Label("$y$", position = 1.0);

/*  Function for computing the gcd of two numbers.                            */
int gcd(int n0, int n1)
{
    /*  Special case. The while loop can be infinite if one of the entries is *
     *  zero. GCD(n, 0) = n, so use this.                                     */
    if (n0 == 0)
        return n1;
    else if (n1 == 0)
        return n0;

    while(n0 != n1)
    {
        if(n0 > n1)
            n0 -= n1;
        else
            n1 -= n0;
    }
    return n0;
}
/*  End of gcd.                                                               */

/*  Draw the axes.                                                            */
draw(x_label, (xstart, 0.0) -- (xend, 0.0), (0, 1), apen, SharpArrow(arsize));
draw(y_label, (0.0, ystart) -- (0.0, yend), (1, 0), apen, SharpArrow(arsize));

/*  Loop over denominators.                                                   */
for (q = 1; q <= max; ++q)
{
    /*  The function returns f(p/q) = 1/q, so save the value 1/q.             */
    y = 1.0 / (real)q;

    /*  Loop over numerators.                                                 */
    for (p = 1; p <= max; ++p)
    {

        /*  Only plot if p and q are coprime. Otherwise we'll be plotting the *
         *  same point twice, which is redundant.                             */
        if (gcd(p, q) != 1)
            continue;

        /*  y = 1/q, and the x value is p/q, so simply compute p*y.           */
        x = p * y;

        /*  We're only plotting up to x = 2.                                  */
        if (x >= 2.0)
            continue;

        /*  Draw the point.                                                   */
        filldraw(circle((x, y), rdot), black, black);
    }
    /*  End of for loop for numerator.                                        */
}
/*  End of for loop for denominator.                                          */
