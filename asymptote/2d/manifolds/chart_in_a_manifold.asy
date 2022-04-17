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

/*  Default size of arrowheads.                                               */
real arsize = 5bp;

/*  Needed for the use of mathbb and mathcal commands.                        */
texpreamble("\usepackage{amssymb}");

/*  Commonly used pens.                                                       */
pen axesp = black + linewidth(0.7pt) + fontsize(9pt);
pen dashp = defaultpen + linetype("8 4");
pen labelp = defaultpen + fontsize(10pt);

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

/*  Variables for shifting and drawing.                                       */
path g, g0, g1, gX, gU, gImU;
real xshift = -8.0;
real yshift = 1.3;
transform TShift = shift(xshift, yshift);

/*  Pens used for filling.                                                    */
pen[] fillp = {cyan, red + 0.3*white};

/*-------------------------SPECIFY POINTS AND ANGLES--------------------------*/

/*  Points used to define the x and y axes.                                   */
pair[] XAxes = {(-0.5,  0.0), (3.0, 0.0)};
pair[] YAxes = {( 0.0, -0.5), (0.0, 3.0)};

/*  Points and angles for the manifold X, the open set U, and its image.      */
pair[] UPts = {(2.0, 0.0), (2.7, 0.5), (3.5, 0.0), (3.2, -0.9), (2.2, -0.8)};
pair[] ImUPts = {(0.5, 1.5), (1.2, 1.9), (1.9, 1.4), (1.4, 0.2), (0.4, 0.3)};
pair[] XPts = {
    (0.0, 0.0), (1.0,  0.8), (2.0,  0.8), (4.0, 0.0), (2.0, -1.5), (0.0, -1.5)
};

real[] UAng = {30.0, 0.0, -90.0, 180.0, 150.0};
real[] ImUAng = {30.0, 0.0, -90.0, 180.0, 150.0};
real[] XAng = {90.0, 0.0, -30.0, -90.0, 180.0, 150.0};

/*  The number of points for X, U, and the image of U.                        */
int XN = 6;
int UN = 5;
int ImUN = 5;

/*  Location and angles of the donut hole in the manifold X.                  */
pair[] DonutPts = {(0.5, -0.7), (1.8, -0.7), (0.6, -0.8), (1.7, -0.8)};
real[] DonutAngle = {-50, 50};

/*  Location and angles for the arrow indicating the function.                */
pair[] PhiPts = {(-3.6, 1.2), (-1.0, 1.2)};
real[] PhiAngle = {30, -30};

/*  Locations for labels.                                                     */
pair ImULabel = (1.1, 1.0);
pair ULabel = TShift*(2.8,-0.2);
pair XLabel = TShift*(1.0, 0.4);

/*--------------------------------DRAW CURVES---------------------------------*/

/*  Draw the coordinate axes for R^n.                                         */
draw(XAxes[0] -- XAxes[1], axesp, SharpArrow(arsize));

/*  Create a label for the Euclidean space R^n.                               */
Label L = Label("$\mathbb{R}^{n}$", position=1);

/*  Draw the y axis, adding the label R^n at the top of it.                   */
draw(L, YAxes[0] -- YAxes[1], E, axesp, SharpArrow(arsize));

/*  Create the paths for X, U, and ImU using PathFromPointsAndAngles.         */
gX = PathFromPointsAndAngles(XPts, XAng, XN, true);
gU = PathFromPointsAndAngles(UPts, UAng, UN, true);
gImU = PathFromPointsAndAngles(ImUPts, ImUAng, ImUN, true);

/*  The manifold and the open set are shifted to the left so that they don't  *
 *  sit on top of the drawing for Euclidean space.                            */
gX = TShift*gX;
gU = TShift*gU;

/*  Draw the manifold, the open set, and its image.                           */
draw(gX);
filldraw(gU, fillp[0], dashp);
filldraw(gImU, fillp[1], dashp);

/*  Add a donut hole in the manifold.                                         */
g0 = DonutPts[0]{dir(DonutAngle[0])} .. {dir(DonutAngle[1])}DonutPts[1];
g1 = DonutPts[2]{dir(DonutAngle[1])} .. {dir(DonutAngle[0])}DonutPts[3];

/*  Shift the donut so it lies in the manifold.                               */
g0 = TShift*g0;
g1 = TShift*g1;

/*  Draw the donut.                                                           */
draw(g0);
draw(g1);

/*  Add some labels.                                                          */
label("$\mathcal{U}$", ULabel, labelp);
label("$X$", XLabel, labelp);
label("$\varphi[\mathcal{U}]$", ImULabel, labelp);

/*  Arrow representing the mapping phi.                                       */
g = PhiPts[0]{dir(PhiAngle[0])} .. {dir(PhiAngle[1])}PhiPts[1];
draw("$\varphi$", g, SharpArrow(StealthHead, arsize));
