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
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 5, 2021                                               *
 ******************************************************************************/

/*  Used for creating the GIF.                                                */
import animate;

/*  Graphing tools are here.                                                  */
import graph;

/*  tikz style arrows are here.                                               */
import custom_arrows;

/*  The GIF is stored in this variable.                                       */
animation a;

/*  The function being plotted.                                               */
real func(real x)
{
    return x*x;
}

/*  Size of the GIF.                                                          */
size(1024);

/*  Number of samples for the function.                                       */
int samples = 30;

/*  Variable for indexing.                                                    */
int n;

/*  Number of frames in the GIF.                                              */
int n_frames = 60;

/*  Start and end for the x and y axes.                                       */
real start = -1.2;
real end = 1.2;

/*  Start and end points for the function.                                    */
real fstart = -1.0;
real fend = 1.0;

/*  Boundaries of the image (used for cropping).                              */
real xstart = -1.2;
real xend = 1.2;
real ystart = -0.5;
real yend = 1.4;

/*  Size of arrow heads.                                                      */
real arsize = 5bp;

/*  The point we care about.                                                  */
real x0 = 0.2;
real y0 = func(x0);
pair P0 = (x0, y0);

/*  Variables for the secant line.                                            */
pair P1, Q0, Q1;

/*  Starting value for the displacement.                                      */
real dx = 0.7;

/*  Multiplicative factor for the displacement. Make this between 0 and 1.    */
real factor = 0.95;

/*  Factors for the slope-intercept form of the secant line.                  */
real m, b;

/*  Pens for the axes and function.                                           */
pen axesp = black + linewidth(1.0pt) + fontsize(24pt);
pen drawp = black + linewidth(0.6pt);
pen funcp = deepblue + linewidth(0.8pt);

/*  Labels for the axes.                                                      */
Label xl = Label("$x$", position = 1.0);
Label yl = Label("$y$", position = 1.0);

/*  Draw the axes.                                                            */
draw(xl, (start, 0.0) -- (end, 0.0), N, axesp, SharpArrow(arsize));
draw(yl, (0.0, start) -- (0.0, end), E, axesp, SharpArrow(arsize));

/*  And draw the function.                                                    */
draw(graph(func, fstart, fend, n=samples, operator ..), funcp);

/*  Loop through the frames of the GIF.                                       */
for (n = 0; n < n_frames; ++n)
{
    /*  Save the current image with the axis and function.                    */
    save();

    /*  Compute the other point for the secant line.                          */
    P1 = (x0 + dx, func(x0 + dx));

    /*  Compute the slope and y-intercept of the secant line.                 */
    m = (P1.y - P0.y)/(P1.x - P0.x);
    b = y0 - m*x0;

    /*  Compute two points on the secant line.                                */
    Q0 = (fstart, m*fstart + b);
    Q1 = (fend, m*fend + b);

    /*  Draw the secant line.                                                 */
    draw(Q0 -- Q1, drawp);

    /*  Crop the drawing to avoid the asymptotes.                             */
    scale(false);
    xlimits(xstart, xend);
    ylimits(ystart, yend);
    crop();

    /*  Add the frame to the GIF.                                             */
    a.add();

    /*  Compute the next displacement.                                        */
    dx *= factor;

    /*  Reset the image to just the axes and function.                        */
    restore();
}
/*  End of for-loop over the frames of the GIF.                               */

/*  Render the GIF.                                                           */
erase();
a.movie(delay=60);
