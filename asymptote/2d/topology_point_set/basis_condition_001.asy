/******************************************************************************
 *                                  LICENSE                                   *
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
 *  Purpose:                                                                  *
 *      Draws the intersection of a plane with a cube, revealing a hexagon.   *
 *      This is what you'd get if you dipped a cube into water with one of    *
 *      vertices of the cube facing down.                                     *
 ******************************************************************************/

/*  PDF is easiest to use in LaTeX, so output this.                           */
import settings;
settings.outformat = "pdf";

/*  Size of the figure.                                                       */
size(256);

/*  Path used later for drawing all of the curves.                            */
path g;

/*  Pens used for filling and drawing.                                        */
defaultpen(black + linewidth(0.5pt) + fontsize(12pt));
pen Vpen = red + opacity(0.5);
pen Upen = blue + opacity(0.5);
pen Wpen = magenta + opacity(0.5);
pen dashpen = black + linewidth(0.4pt) + linetype("4 4");

/*  Radius used for drawing dots.                                             */
real rDot = 0.025;

/*  Position of the points x and y.                                           */
pair xpt = (2.1, 0.0);

/*  Given an array of pairs and an array of reals, draw a path between the    *
 *  pairs with angle specified by the array of reals.                         */
path PathFromPointsAndAngles(pair[] Pts, real[] Dirs, int ArSize, bool closed)
{
    /*  Declare necessary variables.                                          */
    path g;
    int i;

    /*  Assert that the collection of points has at least 2 points.           */
    assert(ArSize > 1);

    /*  Set the start of the path.                                            */
    g = Pts[0]{dir(Dirs[0])} .. Pts[1]{dir(Dirs[1])};

    /*  Loop through the arrays and construct the path.                       */
    for (i = 2; i < ArSize; ++i)
        g = g .. Pts[i]{dir(Dirs[i])};

    /*  If the closed Boolean is true, close the path into a cycle.           */
    if (closed)
        g = g..cycle;

    return g;
}
/*  End of PathFromPointsAndAngles.                                           */

/*  Points for the topological space X and the open sets U and V.             */
pair[] Xpts = {(0.0, 0.3), (1.5, 1.2), (4.0, 0.0), (2.0, -1.0), (0.0, -0.5)};
real[] Xangles = {90.0, 0.0, -90.0, 180.0, 150.0};
int nXpts = 5;

pair[] Vpts = {(1.5, 0.0), (2.0, 0.6), (3.5, 0.0), (3.2, -0.6), (1.6, -0.8)};
real[] Vangles = {30.0, 0.0, -90.0, 180.0, 150.0};
int nVpts = 5;

pair[] Upts = {(0.8, 0.0), (0.9, 0.6), (2.5, 0.0), (2.2, -0.6), (1.5, -0.4)};
real[] Uangles = {70.0, 0.0, -90.0, 180.0, 150.0};
int nUpts = 5;

pair[] Wpts = {
    xpt + (0.0, 0.3),
    xpt + (0.3, 0.2), 
    xpt + (0.3, 0.0),
    xpt + (0.0, -0.4),
    xpt + (-0.2, -0.3)
};
real[] Wangles = {0.0, -80.0, -100.0, 180.0, 160.0};
int nWpts = 5;

/*  Draw X, U, and V.                                                         */
g = PathFromPointsAndAngles(Xpts, Xangles, nXpts, true);
draw(g);

g = PathFromPointsAndAngles(Upts, Uangles, nUpts, true);
filldraw(g, Upen, dashpen);

g = PathFromPointsAndAngles(Vpts, Vangles, nVpts, true);
filldraw(g, Vpen, dashpen);

g = PathFromPointsAndAngles(Wpts, Wangles, nWpts, true);
filldraw(g, Wpen, dashpen);

/*  Draw dots for the points x and y.                                         */
filldraw(circle(xpt, rDot), black, black);

/*  Label X, U, V, and the points x and y.                                    */
label("$x$", xpt, NE);
label("$\mathcal{W}$", xpt, S + SE);
label("$X$", (1.7, 1.0));
label("$\mathcal{U}$", (1.0, 0.3));
label("$\mathcal{V}$", (3.2, -0.4));
