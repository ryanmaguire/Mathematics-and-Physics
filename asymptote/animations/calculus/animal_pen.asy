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
 *  Date:       October 21, 2021                                              *
 ******************************************************************************/

/*  Used for drawing the function.                                            */
import graph;

/*  tikz-like arrows found here.                                              */
import custom_arrows;

/*  GIF tools are here.                                                       */
import animate;

/*  Size of the GIF.                                                          */
size(1024);

/*  The GIF will be created with this variable.                               */
animation a;

/*  Number of samples for the parabola.                                       */
int n_samples = 6;

/*  Number of frames in the GIF.                                              */
int n_frames = 150;

/*  Variable for indexing.                                                    */
int n;

/*  Pens used throughout the drawing.                                         */
pen thickp = black + linewidth(0.8pt);
pen waterp = blue + 0.2*green;
pen drawp = black + linewidth(0.4pt);
pen dashp = black + linewidth(0.4pt) + linetype("4 4");
pen grassp = green;

/*  The dimensions of the river.                                              */
real river_length = 1.1;
real river_width = 0.2;

/*  The length of the fence available.                                        */
real L = 1.0;

/*  Width and height of the axes for the plot.                                */
real xlen = 0.6;
real ylen = 0.6;

/*  Variables for the width and height of the fenced in area.                 */
real w, h;

/*  Shift factor so the plot isn't drawn on top of the drawing.               */
real shift = 1.5;

/*  Size of arrow heads for the plot.                                         */
real arsize = 5bp;

/*  The point on the plot corresponding to the current drawing.               */
real x0, y0;

/*  Size of a dot for labels.                                                 */
real rdot = 0.01;

/*  Variables for looping over different values of w.                         */
real theta = 0.0;
real dtheta = 0.01;

/*  The function of area vs. width.                                           */
real area_func(real x)
{
    /*  Shift the plot.                                                       */
    real y = x - shift;

    /*  Scale it in the y-axis so it's easier to read.                        */
    return 2.0*(L*y - 2.0*y*y);
}

/*  Points for the river.                                                     */
pair R0 = (river_length, 0.0);
pair R1 = (river_length, -river_width);
pair R2 = (-river_length, -river_width);
pair R3 = (-river_length, 0.0);

/*  Draw the river.                                                           */
filldraw(R0 -- R1 -- R2 -- R3 -- cycle, waterp, invisible);
draw(R0 -- R3, drawp);
draw(R1 -- R2, drawp);

/*  Draw the function.                                                        */
draw(graph(area_func, shift, shift+0.5*L, n=n_samples, operator ..), drawp);

/*  Draw the axes.                                                            */
draw((shift, 0.0) -- (shift + xlen, 0.0), thickp, SharpArrow(arsize));
draw((shift, 0.0) -- (shift, ylen), thickp, SharpArrow(arsize));

/*  Label the graph.                                                          */
label("Area", (shift + 0.1, ylen));
label("Width", (shift + xlen, -0.2));

/*  Loop over the possible values for w.                                      */
for (n = 0; n < n_frames; ++n)
{
    /*  Save the current background with the river and function drawn.        */
    save();

    /*  Compute the current w and h values for the fence.                     */
    w = sin(theta);
    w = 0.5*L*w;
    h = L - 2.0*w;

    /*  Using these values, compute the four corners of the region.           */
    pair V0 = (h, 0.0);
    pair V1 = (h, w);
    pair V2 = (-h, w);
    pair V3 = (-h, 0.0);

    /*  Label this area on the graph.                                         */
    x0 = shift + w;
    y0 = area_func(x0);
    draw((x0, y0) -- (x0, 0.0), dashp);
    filldraw(circle((x0, y0), rdot), black, black);

    /*  Draw the fenced in area.                                              */
    filldraw(V0 -- V1 -- V2 -- V3 -- cycle, grassp, drawp);

    /*  Add this current frame to the GIF.                                    */
    a.add();

    /*  Increment theta.                                                      */
    theta += dtheta;

    /*  Reset the background to just the river and the function.              */
    restore();
}
/*  End of for-loop over the frames of the GIF.                               */

/*  Render the GIF.                                                           */
erase();
a.movie(delay=30);
