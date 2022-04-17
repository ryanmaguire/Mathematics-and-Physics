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
size(512);

/*  Default pen for drawing figures.                                          */
defaultpen(black + linewidth(0.5pt) + fontsize(12pt));

/*  Default size of arrowheads.                                               */
real arsize = 5bp;

/*  Needed for the use of mathbb and mathcal commands.                        */
texpreamble("\usepackage{amssymb}");

/*  Commonly used pens.                                                       */
pen dashp = black + linewidth(0.4pt) + linetype("8 4");

/*  Location of the point p in the manifold M.                                */
pair p = (3.5, 0.4);

/*  Second point used to label a tangent vector to M at p.                    */
pair p1 = (4.0, -0.2);

/*  Radius of dots used to label points.                                      */
real rDot = 0.05;

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

/*  Points for the manifold M.                                                */
pair[] Mpts = {
    (0.0, 0.0), (2.0,  1.0), (4.0,  0.5), (5.0, -0.5), (3.0, -1.0), (1.0, -1.0)
};

/*  Angles for the manifold M.                                                */
real[] Mangles = {90.0, -30.0, -40.0, -90.0, 180.0, 130.0};

/*  Number of points used to specify M.                                       */
int nMpts = 6;

/*  Points for the manifold N.                                                */
pair[] Npts = {
    (0.0, 0.0), (2.0,  1.0), (4.0,  1.0), (5.0, -0.5), (3.0, -1.5), (0.5, -1.0)
};

/*  Angles for the manifold N.                                                */
real[] Nangles = {90.0, -30.0, -40.0, -90.0, 180.0, 130.0};

/*  Number of points used to specify the manifold N.                          */
int nNpts = 6;

/*  Shifts for the manifold N so it is not on top of M.                       */
real xshift = 7.0;
real yshift = 0.0;
transform TShift = shift(xshift, yshift);

/*  The point phi(p) in the manifold N.                                       */
pair fp = TShift * (3.0, 0.0);

/*  Another point for a tangent vector in N centered at phi(p).               */
pair fp1 = TShift * (4.0, 0.2);

/*  Draw the manifolds M and N using the PathFromPointsAndAngles function.    */
path g = PathFromPointsAndAngles(Mpts, Mangles, nMpts, true);
draw(g);

g = PathFromPointsAndAngles(Npts, Nangles, nNpts, true);
draw(TShift*g);

/*  Add a donut hole to M.                                                    */
draw((0.5, 0.1){dir(-50.0)} .. (1.8, 0.1){dir(50.0)});
draw((0.6, 0.0){dir(50.0)} .. (1.7, 0.0){dir(-50.0)});

/*  Draw the tangent space at p.                                              */
draw((2.0, -0.5) -- (3.0, 1.5) -- (5.0, 1.5) -- (4.0, -0.5) -- cycle, dashp);

/*  Label the manifold M, the point p, and the tangent space T_{p}M.          */
filldraw(circle(p, rDot), black, black);
label("$p$", p, SW);
label("$M$", (1.4, -0.9));
label("$T_{p}M$", (4.4, 1.2));

/*  Draw the tangent vector and label it.                                     */
draw("$v$", p -- p1, NE, SharpArrow(arsize));

/*  Draw the tangent space at phi(p).                                         */
g = (2.0, -0.5) -- (2.5, 1.7) -- (5.0, 1.7) -- (4.5, -0.5) -- cycle;
draw(TShift * g, dashp);

/*  Label the manifold N, the point phi(p), and the tangent space T_{phi(p)}N.*/
filldraw(circle(fp, rDot), black, black);
label("$\phi(p)$", fp, SW);
label("$N$", TShift*(1.4, -0.9));
label("$T_{p}M$", TShift*(4.2, 1.4));

/*  Draw the tangent vector and label it.                                     */
draw("$\textrm{d}\,\phi_{p}(v)$", fp -- fp1, N, SharpArrow(arsize));

/*  Label the function phi.                                                   */
g = (5.0, 1.0){dir(30.0)} .. (7.0, 1.0){dir(-30.0)};
draw("$\phi$", g, N, SharpArrow(arsize));
