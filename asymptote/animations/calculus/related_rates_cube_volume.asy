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
 *  Date:       October 4, 2021                                               *
 ******************************************************************************/

/*  3D tools are here.                                                        */
import graph3;

/*  Needed for the GIF.                                                       */
import animation;

/*  Size of the GIF.                                                          */
size(1024);

/*  Setup the camera.                                                         */
currentprojection = perspective(5.0, 2.0, 2.0);

/*  The frames of the GIF will be stored in this variable.                    */
animation a;

/*  Variable for indexing over.                                               */
int n;

/*  Number of frames in the GIF.                                              */
int n_frames = 60;

/*  Pen for the axes.                                                         */
pen axesp = black + linewidth(1.4pt) + fontsize(24pt);

/*  Pen for marking the length of the diagonal of the cube.                   */
pen drawp = blue + linewidth(0.8pt) + fontsize(24pt);

/*  Start and end lengths for the cube over the course of the GIF.            */
real start_length = 0.5;
real end_length = 1.0;

/*  Size of the axes. Make this larger than the end length to avoid the       *
 *  camera needing to zoom out over time (which looks bad).                   */
real axis_length = 1.8;

/*  Change in length across frames.                                           */
real dr = (end_length - start_length) / n_frames;

/*  Variable for looping over sizes.                                          */
real r = start_length;

/*  The material the cube is made out of.                                     */
material blob = material(
    diffusepen = gray(0.7) + opacity(0.3),
    specularpen = gray(0.1),
    emissivepen = gray(0.1)
);

/*  Label for the length vector.                                              */
Label L = Label("$r$", position = 0.5);

/*  Draw the three axes. This will be "saved" so we don't need to redraw them *
 *  for every single frame.                                                   */
xaxis3("$x$", 0.0, axis_length, axesp, Arrow3);
yaxis3("$y$", 0.0, axis_length, axesp, Arrow3);
zaxis3("$z$", 0.0, axis_length, axesp, Arrow3);

/*  Function for drawing the cube.                                            */
void draw_cube(real length)
{
    triple O = (0.0, 0.0, 0.0);
    triple X = (r, 0.0, 0.0);
    triple Y = (0.0, r, 0.0);
    triple Z = (0.0, 0.0, r);
    draw(surface(plane(X, Y, O=O)), surfacepen=blob);
    draw(surface(plane(X, Z, O=O)), surfacepen=blob);
    draw(surface(plane(Y, Z, O=O)), surfacepen=blob);
    draw(surface(plane(Z, Y, O=X)), surfacepen=blob);
    draw(surface(plane(X, Y, O=Z)), surfacepen=blob);
    draw(surface(plane(X, Z, O=Y)), surfacepen=blob);
}

/*  Loop over the lengths and draw the cube growing.                          */
for (n = 0; n < n_frames; ++n)
{
    /*  Save the image without any cube drawn yet.                            */
    save();

    /*  Draw the cube and the position vector.                                */
    draw_cube(r);
    draw(L, O -- (r, r, r), drawp, Arrow3);

    /*  Add the image to the GIF.                                             */
    a.add();

    /*  Reset the image back to just the axes.                                */
    restore();

    /*  Increment the radius.                                                 */
    r += dr;
}
/*  End of for-loop over the radius of the cube.                              */

/*  Render the GIF.                                                           */
erase();
a.movie(delay=50);
