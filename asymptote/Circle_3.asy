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

/*  Draw the image on a PDF file.                                             */
import settings;
settings.outformat = "pdf";

/*  Custom arrows mimicing the tikz style. _custom_arrows.asy must be in      *
 *  your path when creating this figure.                                      */
import _custom_arrows;

/* Size of the output figure.                                                 */
size(256);

/*  Default pen for drawing figures.                                          */
defaultpen(black + linewidth(0.5pt) + fontsize(7pt));

/*  A thinner pen for drawing.                                                */
pen thinp  = black + linewidth(0.3pt);

/*  Default size of arrowheads.                                               */
real arsize = 5bp;

/*  Pen for drawing axes.                                                     */
pen axesp  = black + linewidth(0.7pt) + fontsize(9pt);

/*  Filler for the triangles.                                                 */
pen fillp = red+opacity(0.5);

/* Given an array of pairs, draw a polygonal curve through the point.         */
path PolyFromPoints(pair[] Pts, int ArSize, bool closed)
{
    /*  Declare necessary variables.                                          */
    path g;
    int i;

    /*  Assert that the collection of points has at least 2 points.           */
    assert(ArSize>1);

    /*  Start the path going from the zeroth point to the first.              */
    g = Pts[0]--Pts[1];

    /* Loop through the array and construct the path.                         */
    for (i=2; i<ArSize; ++i)
        g = g--Pts[i];

    /* If the closed Boolean is true, close the path into a cycle.            */
    if (closed)
        g = g--cycle;

    return g;
}
/*  End of PolyFromPoints.                                                    */

/*  Radius of the circle and length of the axes.                              */
real R = 1.0;
real len = 1.2;

/*  Transform for scaling by radius.                                          */
transform T = scale(R, R);

/*  The origin and points for the x and y axes.                               */
pair O   = (0.0, 0.0);
pair[] X = {(-len, 0.0), (len, 0.0)};
pair[] Y = {(0.0, -len), (0.0, len)};

/*  Points for the object inside circle.                                      */
pair[] ObjPts = {T*expi(pi/4), T*expi(5pi/4), T*expi(3pi/4), T*expi(7pi/4)};
int ObjN = 4;

/*  Draw the circle.                                                          */
draw(circle(O, R));

/*  Draw and label the axes.                                                  */
draw(Label("$x$", position=1), X[0]--X[1], S, axesp, SharpArrows(arsize));
draw(Label("$y$", position=1), Y[0]--Y[1], W, axesp, SharpArrows(arsize));

/*  And draw the object inside of the circle.                                 */
filldraw(PolyFromPoints(ObjPts, ObjN, true), fillp, thinp);
