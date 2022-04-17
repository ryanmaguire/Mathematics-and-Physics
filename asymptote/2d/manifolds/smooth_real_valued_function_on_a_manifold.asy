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
 ******************************************************************************/

/*  Make sure custom_arrows.asy is in your path. This file is found in the    *
 *  asymptote/ folder of this project. You'll need to edit the                *
 *  ASYMPTOTE_DIR environment variable to include this.                       */
import custom_arrows;

/*  Draw the image on a PDF file.                                             */
import settings;
settings.outformat = "pdf";

/*  Size of the output figure.                                                */
size(256);

/*  Default pen for drawing figures.                                          */
defaultpen(black + linewidth(0.5pt) + fontsize(7pt));

/*  Needed for the use of mathbb and mathcal commands.                        */
texpreamble('\usepackage{amssymb}');

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

/*  Size of the arrow head.                                                   */
real arsize = 5bp;

/*  Used for drawing paths.                                                   */
path g;

/*  Pen for curves and dashes.                                                */
pen cpen = black + linewidth(0.5pt);
pen dpen = black + linewidth(0.2pt)+dashed;

/*  Pen for an open interval on the real line.                                */
pen rpen = blue + linewidth(0.8pt);

/*  Shifts for the manifold.                                                  */
real xshift = 3.0;
real yshift = 4.5;
transform TShift = shift(xshift, yshift);

/*  Points for the blob in R^n.                                               */
pair[] blobpts = {(0.5, 1.5), (1.2, 1.9), (1.9, 1.4), (1.4, 0.2), (0.4, 0.3)};

/*  Angles for the blob in R^n.                                               */
real[] blobangles = {30.0, 0.0, -90.0, 180.0, 150.0};

/*  Number of points in the blob.                                             */
int nblobpts = 5;

/*  Points for the manifold X.                                                */
pair[] Xpts = {
    (0.0, 0.0), (1.0, 1.0), (2.0, 1.0), (4.0, 0.0), (2.0, -2.5), (0.0, -2.5)
};

/*  Angles for the manifold X.                                                */
real[] Xangles = {90.0, 0.0, -30.0, -90.0, 180.0, 150.0};

/*  Number of points specifying X.                                            */
int nXpts = 6;

/*  Points for the blob U in the manifold X.                                  */
pair[] Upts = {(2.0, 0.0), (2.7, 0.5), (3.5, 0.0), (3.2, -0.9), (2.2, -0.8)};

/*  Angles for the blob U in the manifold X.                                  */
real[] Uangles = {30.0, 0.0, -90.0, 180.0, 150.0};

/*  Number of points specifying U.                                            */
int nUpts = 5;

/*  Draw the axes for R^n.                                                    */
draw((-1.0, 0.0) -- (3.0, 0.0), SharpArrow(arsize));
draw((0.0, -1.0) -- (0.0, 3.0), SharpArrow(arsize));

/*  Create a path for the blob and fill it in.                                */
g = PathFromPointsAndAngles(blobpts, blobangles, nblobpts, true);
filldraw(g, red + white, dpen);

/*  Label R^n and label the blob as the image of U under phi.                 */
label("$\mathbb{R}^{n}$", (0.5, 3.0));
label("$\varphi[\mathcal{U}]$", (1.1, 1.0));

/*  Label the function phi.                                                   */
g = (1.3, 2.0){dir(90.0)} .. {dir(0.0)}(4.7, 4.2);
draw("$\varphi$", g, NW, cpen, BeginSharpArrow(arsize));

/*  Draw the manifold X.                                                      */
g = PathFromPointsAndAngles(Xpts, Xangles, nXpts, true);
draw(TShift*g);

/*  Draw a donut hole in X.                                                   */
draw(TShift*((0.5, -1.7){dir(310.0)} .. {dir(50.0)}(1.8, -1.7)));
draw(TShift*((0.6, -1.8){dir(50.0)} .. {dir(310.0)}(1.7, -1.8)));

/*  Draw the blob U in the manifold X.                                        */
g = g = PathFromPointsAndAngles(Upts, Uangles, nUpts, true);
filldraw(TShift*g, blue + white, dpen);

/*  Label the open set U and the manifold X.                                  */
label("$\mathcal{U}$", TShift*(2.8, -0.2));
label("$X$", TShift*(1.0,  0.6));

/*  Draw the real line.                                                       */
g = (6.0, 0.0) -- (10.0, 0.0);
draw(Label("$\mathbb{R}$", position=1.0), g, N, SharpArrows(arsize));

/*  Label the function f from the manifold to the real line.                  */
g = (6.7, 4.2){dir(0.0)} .. {dir(270.0)}(8.0, 0.2);
draw("$f$", g, E, cpen, SharpArrow(arsize));

/*  Label an open interval in the real line and draw it blue.                 */
draw(arc((9.0 - 0.5, 0.0), 0.5, -15.0, 15.0), rpen);
draw(arc((7.0 + 0.5, 0.0), 0.5, 165.0, 195.0), rpen);
draw((7.0, 0.0) -- (9.0, 0.0), rpen);

/*  Label the composition f with phi inverse, which is a function from an     *
 *  open subset of R^n to the real line.                                      */
g = (1.2, -0.2){dir(-30.0)} .. {dir(30.0)}(7.8, -0.2);
draw("$f\circ\varphi^{-1}$", g, N, cpen, SharpArrow(arsize));
