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
 *  Date:       August 19, 2020                                               *
 ******************************************************************************/

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Module needed for the animation.                                          */
import animation;

/*  Size of the gif.                                                          */
size(1024);

/*  Necessary variables for drawing the surfaces and creating the .GIF file.  */
animation a;

/*  Pens used for the drawing.                                                */
defaultpen(black + linewidth(0.5pt) + fontsize(24pt));
pen axesp = black + linewidth(1.2pt);
pen thinp = black + linewidth(0.3pt);

/*  Size of arrow heads.                                                      */
real arsize = 20bp;

/*  Start and end of the x and y axes.                                        */
real start = -0.4;
real end = 1.4;

/*  The value of interest.                                                    */
real x0 = 0.5*end;

/*  Radius used to draw dots.                                                 */
real rdot = 0.008;

/*  Integer for indexing.                                                     */
int n;

/*  The number of frames in the GIF.                                          */
int n_frames = 100;

/*  Variable for looping over values of epsilon.                              */
real eps;

/*  Set up the background of the picture. This is the axes, the function, and *
 *  the labels of points of interest.                                         */
label("$f(x)=x$", (0.6*end, 0.7*end));
label("$x_{0}$", (x0, -0.08));
label("$f(x_{0})$", (-0.08, x0));

/*  Mark dots are x0 and f(x0).                                               */
filldraw(circle((x0, 0.0), rdot), black, black);
filldraw(circle((0.0, x0), rdot), black, black);

/*  Labels for the axes.                                                      */
Label xlabel = Label("$x$", position = 1.0);
Label ylabel = Label("$y$", position = 1.0);

/*  Draw the axes.                                                            */
draw(xlabel, (start, 0.0) -- (end, 0.0), N, axesp, SharpArrow(arsize));
draw(ylabel, (0.0, start) -- (0.0, end), E, axesp, SharpArrow(arsize));
draw((end, end) -- (start, start));
draw((0.0, x0) -- (x0, x0) -- (x0, 0.0), thinp);

/*  Function for drawing dashed lines for the epsilon-delta problem.          */
void draw_frame(real x, real epsilon)
{
    real xminus = x - epsilon;
    real xplus = x + epsilon;

    draw((xminus, 0.0) -- (xminus, xminus) -- (0.0, xminus), dashed);
    draw((xplus, 0.0) -- (xplus, xplus) -- (0.0, xplus), dashed);
    draw((xminus, xplus) -- (xminus, xminus) -- (xplus, xminus), dashed);
}
/*  End of draw_frame.                                                        */

/*  Loop over the frames and draw the GIF.                                    */
for (n = 0; n < n_frames; ++n)
{
    /*  Save the background so we don't need to redraw it every time.         */
    save();

    /*  Compute the current epsilon and draw the frame.                       */
    eps = 1.0 / (0.2*n+20.0);
    draw_frame(x0, eps);

    /*  Add the frame to the GIF.                                             */
    a.add();

    /*  Reset the picture so it's just the background again.                  */
    restore();
}

/*  Render the gif.                                                           */
erase();
a.movie(delay=16);
