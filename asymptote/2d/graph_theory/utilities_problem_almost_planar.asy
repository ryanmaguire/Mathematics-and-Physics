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

/*  Size of the figure.                                                       */
size(256);

/*  Coordinates for the vertices of the graph.                                */
pair[] A = {(-1.0, 0.5), (1.0, 0.0), (1.0, -1.0)};
pair[] B = {(0.0, 0.0), (2.0, 0.5), (0.0, -1.0)};

/*  Radius of the dots.                                                       */
real radius = 0.2;

/*  Size of the houses.                                                       */
real size = 0.3;

/*  Function for drawing a house with a door and window.                      */
void draw_house(pair center, real size)
{
    /*  The four corners of the house lie on a circle.                        */
    pair V0 = center + scale(size)*expi(0.25*pi);
    pair V1 = center + scale(size)*expi(0.75*pi);
    pair V2 = center + scale(size)*expi(1.25*pi);
    pair V3 = center + scale(size)*expi(1.75*pi);

    /*  The point of the roof is centered.                                    */
    pair roof = center + (0.0, 1.2*size);

    /*  Four points for a rectangular door off to the left side of the house. */
    pair door0 = scale(0.2)*(V3 - V2) + V2;
    pair door1 = scale(0.45)*(V3 - V2) + V2;
    pair door2 = door1 + (0.0, 0.6*size);
    pair door3 = door0 + (0.0, 0.6*size);

    /*  Four points for a window on the right side of the house.              */
    pair window0 = scale(0.6)*(V3-V2) + V2 + (0.0, 0.4*size);
    pair window1 = window0 + (0.0, 0.4*size);
    pair window2 = window1 + (0.4*size, 0.0);
    pair window3 = window0 + (0.4*size, 0.0);

    /*  Four points for the cross-thing that windows have.                    */
    pair pane0 = window0 + (0.0, 0.2*size);
    pair pane1 = window3 + (0.0, 0.2*size);
    pair pane2 = window0 + (0.2*size, 0.0);
    pair pane3 = window1 + (0.2*size, 0.0);

    /*  Draw the house.                                                       */
    filldraw(V0 -- V1 -- V2 -- V3 -- cycle, gray, black);

    /*  Draw and color the roof.                                              */
    filldraw(V0 -- roof -- V1 -- cycle, brown, black);

    /*  Next, do the door.                                                    */
    filldraw(door0 -- door1 -- door2 -- door3 -- cycle, deepgreen, black);

    /*  Finally, draw the window.                                             */
    filldraw(window0 -- window1 -- window2 -- window3 -- cycle, yellow, black);
    draw(pane0 -- pane1);
    draw(pane2 -- pane3);
}
/*  End of draw_house.                                                        */

/*  Function for drawing a water symbol.                                      */
void draw_water(pair center, real size)
{
    /*  Shift the drawing a bit.                                              */
    pair new_center = center - (0.0, 0.45*size);

    /*  The "tip" of the water molecule.                                      */
    pair A = new_center + (0.0, 2.2366*size);

    /*  The location of the reflection in the water.                          */
    pair B = new_center + (-0.3*size, 0.9*size);

    /*  Path for the outline of the water molecule.                           */
    path g = arc(new_center, size, 150.0, 390.0) -- A -- cycle;

    /*  Draw the water molecule.                                              */
    filldraw(g, lightblue, blue + linewidth(0.1pt));

    /*  Path for the reflection.                                              */
    g = rotate(60.0)*ellipse((0.0, 0.0), 0.4*size, 0.2*size);

    /*  Add some reflection.                                                  */
    filldraw(shift(B)*g, white, lightblue);
}
/*  End of draw_water.                                                        */

/*  Function for drawing lightning.                                           */
void draw_lightning(pair center, real size)
{
    /*  Shift the center slightly to the left.                                */
    pair new_center = center - (0.1*size, 0.0);

    /*  Vertices for the lightning.                                           */
    pair A = new_center + scale(size)*expi(0.35*pi);
    pair B = new_center - (0.2*size, 0.05*size);
    pair C = new_center + (0.1*size, -0.1*size);
    pair D = new_center + scale(size)*expi(1.4*pi);
    pair E = new_center + (0.6*size, 0.0);
    pair F = new_center + (0.25*size, 0.15*size);

    /*  Path for the outline of the lightning.                                */
    path g = A -- B -- C -- D -- E -- F -- cycle;

    /*  Draw the lightning.                                                   */
    filldraw(g, yellow, yellow + linewidth(0.1pt));
}
/*  End of draw_lightning.                                                    */

/*  Function for drawing fire.                                                */
void draw_fire(pair center, real size)
{
    /*  Points for the outline of the fire.                                   */
    pair V0 = scale(size)*expi(1.5pi);
    pair V1 = (0.8*size, 0.0);
    pair V2 = scale(0.8*size)*expi(0.15*pi);
    pair V3 = scale(1.2*size)*expi(0.5*pi);
    pair V4 = scale(0.7*size)*expi(0.7*pi);
    pair V5 = scale(0.7*size)*expi(pi);

    /*  Shift for drawing a copy of this, one red one yellow.                 */
    pair shift0 = center - (0.0, 0.15*size);
    pair shift1 = shift0 - (0.0, 0.5*size);

    /*  Path for the fire.                                                    */
    path g = V0 .. V1 .. V2 .. {NW}V3{SW} .. V4 .. V5 .. cycle;

    /*  Draw the fire.                                                        */
    filldraw(shift(shift0)*g, red);
    filldraw(shift(shift1)*scale(0.5)*g, yellow);
}
/*  End of draw_fire.                                                         */

/*  Draw the edges.                                                           */
draw(A[0] -- B[0]);
draw(A[0] -- B[1]);
draw(A[0] -- B[2]);
draw(A[1] -- B[0]);
draw(A[1] -- B[1]);
draw(A[1] -- B[2]);

/*  There's a crossing, so overwrite with white so we can simulate one edge   *
 *  passing over the other.                                                   */
draw(A[2] -- B[0], white + linewidth(2.0pt));
draw(A[2] -- B[0]);
draw(A[2] -- B[1]);
draw(A[2] -- B[2]);

/*  Draw the houses.                                                          */
draw_house(A[0], size);
draw_house(A[1], size);
draw_house(A[2], size);

/*  Draw circles to indicate the three utilities.                             */
filldraw(circle(B[0], radius), blue, black);
filldraw(circle(B[1], radius), orange, black);
filldraw(circle(B[2], radius), deepred, black);

/*  Draw symbols for the three utilities.                                     */
draw_water(B[0], 0.08);
draw_lightning(B[1], 0.1);
draw_fire(B[2], 0.1);
