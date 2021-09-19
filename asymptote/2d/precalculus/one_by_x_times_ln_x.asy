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

/*  Used for plotting the function.                                           */
import graph;

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the drawing.                                                      */
size(256, IgnoreAspect);

/*  Length of the x and y axes.                                               */
real xlen = 2.2;
real ylen = 10.2;

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  Number of samples in the drawing.                                         */
int n_samples = 100;

/*  The function to be plotted, 1 / xln(x).                                   */
real f(real x)
{
    real denom = x*log(x);
    return 1.0 / denom;
}

/*  Function used to avoid plotting the points where f is undefined.          */
bool3 branch(real x)
{
    int sign;
    bool b;
    static int lastsign = 0;

    if (x <= 0.0 || x == 1.0)
        return false;

    sign = sgn(f(x));
    b = (lastsign == 0 || sign == lastsign);
    lastsign = sign;

    if (b)
        return b;
    else
        return default;
}

/*  Graph the function.                                                       */
draw(graph(f, 0.0, xlen, n=n_samples, branch, operator ..), deepblue);

/*  Crop the drawing to avoid the asymptotes.                                 */
scale(false);
xlimits(-xlen, xlen);
ylimits(-ylen, ylen);
crop();

/*  Draw the axes.                                                            */
xaxis("$x$", RightTicks(NoZero), SharpArrows(arsize));
yaxis("$y$", LeftTicks(NoZero), SharpArrows(arsize));

/*  Label the function.                                                       */
label("$f(x)=\frac{1}{x\ln(x)}$", (-1.0, 2.0), deepblue);
