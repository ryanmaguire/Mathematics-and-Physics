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

/*  Needed for drawing functions.                                             */
import graph;

/*  PDF works best for LaTeX docs, so use this.                               */
import settings;
settings.outformat = "pdf";

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Default pen for drawing.                                                  */
defaultpen(black + linewidth(0.4pt));

/*  Size of the output figure.                                                */
size(128);

/*  Pen for the function, axes, dashed lines, and filling.                    */
pen funcpen = deepblue + linewidth(0.5pt);
pen apen = black + linewidth(0.8pt);
pen dpen = linewidth(0.2pt) + linetype("8 8");

/*  Size of the arrow head.                                                   */
real arsize = 5bp;

/*  Radius of the dots to be drawn.                                           */
real rbig = 0.01;
real rsmall = 0.005;

/*  Continuous function to be plotted.                                        */
real f(real x)
{
    return exp(-x*x) + 1.3*x*x - 0.7;
}

/*  Variable used for indexing.                                               */
int n;

/*  Number of points in the sequence.                                         */
int N = 6;

/*  Number of samples in the function.                                        */
int samples = 128;

/*  First and last x values to be plotted.                                    */
real start = 0.0;
real end = 1.0;

/*  Min and max values for the x-axis.                                        */
real xmin = -0.1;
real xmax = 1.15;

/*  Min and max values for the y-axis.                                        */
real ymin = -0.1;
real ymax = 1.1;

/*  Number of tick marks in the x and y axes.                                 */
int nx_ticks = (int)(4.0*xmax);
int ny_ticks = (int)(4.0*ymax);

/*  Set the point about which continuity is being demonstrated.               */
real x0 = 0.67;
real y0 = f(x0);

/*  Variables used for drawing the sequence.                                  */
real xn, yn;
real dx = 0.35;

/*  Variables for looping over for the tick marks.                            */
real tick;

/*  Plot the x axis.                                                          */
draw((xmin, 0.0) -- (xmax, 0.0), S, apen, SharpArrow(arsize));

/*  And the y axis.                                                           */
draw((0.0, ymin) -- (0.0, ymax), W, apen, SharpArrow(arsize));

/*  Add tick marks to the x axis.                                             */
for (n = 1; n <= nx_ticks; ++n)
{
    /*  Distance along the x-axis of the current tick mark.                   */
    tick = 0.25*n;

    /*  Label every fourth tick with a number.                                */
    if ((n % 4) == 0)
    {
        draw((tick, 0) -- (tick, -0.05));
        label("$"+string((int)tick)+"$", (tick, -0.1), fontsize(7pt));
    }
    else
        draw((tick, 0) -- (tick, -0.025));
}
/*  End of for-loop for ticks in the x-axis.                                  */

/*  Add tick marks to the y axis.                                             */
for (n = 1; n <= ny_ticks; ++n)
{
    /*  Distance along the y-axis of the current tick mark.                   */
    tick = 0.25*n;

    /*  Label every fourth tick with a number.                                */
    if ((n % 4) == 0)
    {
        draw((0, tick) -- (-0.05, tick));
        label("$"+string((int)tick)+"$", (-0.1, tick), fontsize(7pt));
    }
    else
        draw((0, tick) -- (-0.025, tick));
}
/*  End of for-loop for tick marks in the y-axis.                             */

/*  Plot the function.                                                        */
draw(graph(f, start, end, n=samples), funcpen);

/*  Draw lines from the axes to the point of interest.                        */
draw((x0, 0) -- (x0, y0) -- (0, y0));

/*  Draw the sequence.                                                        */
for (n = 0; n < N; ++n)
{
    /*  Compute the current point in the sequence.                            */
    xn = x0 - dx;
    yn = f(xn);

    /*  Draw dashed lines indicating the x and y components of the sequence.  */
    draw((xn, 0) -- (xn, yn) -- (0, yn), dpen);

    /*  Place a dot at the point.                                             */
    filldraw(circle((xn, yn), rsmall), black);

    /*  Update the incrementing factor.                                       */
    dx *= 0.5;
}
/*  End of for-loop drawing the sequence.                                     */

/*  Label the y axis.                                                         */
label("$y_{0}$", (-0.03, y0), W, fontsize(7pt));
label("$y$", (0.0, ymax), E, fontsize(7pt));

/*  Label the x axis.                                                         */
label("$x_{0}$", (x0, -0.03), S, fontsize(7pt));
label("$x$", (xmax, 0.0), S, fontsize(7pt));

/*  Place a dot at the point of interest.                                     */
filldraw(circle((x0, y0), rbig), black);

/*  Label the function.                                                       */
label("$f$", (0.9, 0.9), fontsize(9pt));
