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
size(512);

/*  Coordinates for the vertices of the graph.                                */
pair[] A = {(-0.5, 1.0), (0.5, 1.0), (1.5, 1.0)};
pair[] B = {(-0.5, 0.0), (0.5, 0.0), (1.5, 0.0)};

/*  Size of the house and labels.                                             */
real radius = 0.3;

/*  Default fontsize for labels.                                              */
defaultpen(fontsize(12pt));

void draw_house(pair center, real size)
{
    pair V0 = center + scale(size)*expi(0.25*pi);
    pair V1 = center + scale(size)*expi(0.75*pi);
    pair V2 = center + scale(size)*expi(1.25*pi);
    pair V3 = center + scale(size)*expi(1.75*pi);

    pair roof = center + (0.0, 1.2*size);

    pair door0 = scale(0.2)*(V3 - V2) + V2;
    pair door1 = scale(0.45)*(V3 - V2) + V2;
    pair door2 = door1 + (0.0, 0.6*size);
    pair door3 = door0 + (0.0, 0.6*size);

    pair window0 = scale(0.6)*(V3-V2) + V2 + (0.0, 0.4*size);
    pair window1 = window0 + (0.0, 0.4*size);
    pair window2 = window1 + (0.4*size, 0.0);
    pair window3 = window0 + (0.4*size, 0.0);
    pair pane0 = window0 + (0.0, 0.2*size);
    pair pane1 = window3 + (0.0, 0.2*size);
    pair pane2 = window0 + (0.2*size, 0.0);
    pair pane3 = window1 + (0.2*size, 0.0);

    filldraw(V0 -- V1 -- V2 -- V3 -- cycle, gray, black);
    filldraw(V0 -- roof -- V1 -- cycle, brown, black);
    filldraw(door0 -- door1 -- door2 -- door3 -- cycle, deepgreen, black);
    filldraw(window0 -- window1 -- window2 -- window3 -- cycle, yellow, black);
    draw(pane0 -- pane1);
    draw(pane2 -- pane3);

}

draw_house(A[0], radius);
draw_house(A[1], radius);
draw_house(A[2], radius);

draw(ellipse(B[0], 0.8*radius, 0.4*radius));
draw(ellipse(B[1], 0.8*radius, 0.4*radius));
draw(ellipse(B[2], 0.8*radius, 0.4*radius));

label("Water", B[0], fontsize(12pt));
label("Gas", B[1], fontsize(12pt));
label("Electricity", B[2], fontsize(12pt));
