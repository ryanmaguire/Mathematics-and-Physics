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
 *  Date:       September 24, 2021                                            *
 ******************************************************************************/

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Module needed for the animation.                                          */
import animation;

/*  Used for drawing functions.                                               */
import graph;

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
real end = 1.0;

/*  Radius used to draw dots.                                                 */
real rdot = 0.008;

/*  Integer for indexing.                                                     */
int n;

/*  The number of frames in the GIF.                                          */
int n_frames = 50;

/*  The value of interest.                                                    */
real x0 = 0.5*end;
real dx = 0.5*end / n_frames;

/*  Number of samples for plotting f(x) = x^2.                                */
int n_samples = 100;

/*  Variable for looping over values of epsilon.                              */
real eps = 0.1;

/*  The function f(x) = x^2.                                                  */
real square(real x)
{
    return x*x;
}

/*  Set up the background of the picture. This is the axes, the function, and *
 *  the labels of points of interest.                                         */
label("$f(x)=x^{2}$", (0.6*end, 0.7*end));

/*  Labels for the axes.                                                      */
Label xlabel = Label("$x$", position = 1.0);
Label ylabel = Label("$y$", position = 1.0);

/*  Draw the axes.                                                            */
draw(xlabel, (start, 0.0) -- (end, 0.0), N, axesp, SharpArrow(arsize));
draw(ylabel, (0.0, start) -- (0.0, end), E, axesp, SharpArrow(arsize));

/*  Draw the function.                                                        */
draw(graph(square, start, end, n=n_samples, operator ..));

/*  Function for drawing dashed lines for the epsilon-delta problem.          */
void draw_frame(real x, real epsilon)
{
    real y = square(x);
    real delta = min(0.5*x, 0.5*epsilon/x);

    real xminus = x - delta;
    real xplus = x + delta;
    real yminus = y - epsilon;
    real yplus = y + epsilon;

    filldraw(circle((x, 0.0), rdot), black, black);
    filldraw(circle((0.0, y), rdot), black, black);
    draw((0.0, y) -- (x, y) -- (x, 0.0), thinp);
    draw((xminus, 0.0) -- (xminus, yminus) -- (0.0, yminus), dashed);
    draw((xplus, 0.0) -- (xplus, yplus) -- (0.0, yplus), dashed);
    draw((xminus, yplus) -- (xminus, yminus) -- (xplus, yminus), dashed);
    label("$x_{0}$", (x, -0.08));
    label("$f(x_{0})$", (-0.08, y));
}
/*  End of draw_frame.                                                        */

/*  Loop over the frames and draw the GIF.                                    */
for (n = 0; n < n_frames; ++n)
{
    /*  Save the background so we don't need to redraw it every time.         */
    save();

    /*  Compute the current epsilon and draw the frame.                       */
    draw_frame(x0, eps);

    /*  Add the frame to the GIF.                                             */
    a.add();

    /*  Reset the picture so it's just the background again.                  */
    restore();

    /*  Increment x0.                                                         */
    x0 += dx;
}

/*  Render the gif.                                                           */
erase();
a.movie(delay=100);
