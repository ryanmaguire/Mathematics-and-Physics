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

/*  Pens for the manifolds and open subsets.                                  */
pen dpen = black + linewidth(0.5pt) + linetype("4 4");
pen Upen = blue + opacity(0.5);
pen Vpen = red + opacity(0.5);

/*  Default size of arrowheads.                                               */
real arsize = 5bp;

/*  Path for drawing curves later.                                            */
path g;

/*  Label for axes later.                                                     */
Label L;

/*  Needed for the use of mathbb and mathcal commands.                        */
texpreamble("\usepackage{amssymb}");

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

/*  Points defined the two manifolds M and N.                                 */
pair[] Mpts = {
    (0.0, 0.0), (1.0, 1.0), (5.0, 1.0), (5.0, -1.0), (3.0, -1.0), (1.0, -1.0)
};
real[] Mangles = {90.0, -30.0, -40.0, -90.0, 180.0, 130.0};
int nMpts = 6;

pair[] Npts = {
    (0.0, 0.0), (2.0, 1.0), (4.0, 1.0), (5.0, -0.5), (3.0, -1.5), (0.0, -1.2)
};
real[] Nangles = {90.0, -30.0, -20.0, -90.0, 180.0, 130.0};
int nNpts = 6;

/*  The open sets U and phi^{-1}[V] in the manifold M.                        */
pair[] Upts = {(2.5, -0.5), (4.0, -0.4), (4.5,  0.3), (4.0,  0.8)};
real[] Uangles = {-60.0, 40.0, 90.0, -170.0};
int nUpts = 4;

pair[] VPpts = {(2.8, -0.5), (4.4, -0.8), (4.8, -0.8), (4.5,  0.4)};
real[] VPangles = {-60.0, 30.0, 50.0, -170.0};
int nVPpts = 4;

/*  The open sets V and phi[U] in the manifold N.                             */
pair[] Vpts = {(1.0, -0.5), (3.2, -1.0), (3.7, 0.0), (2.7, 0.5)};
real[] Vangles = {-60.0, 70.0, 90.0, -170.0};
int nVpts = 4;

pair[] ImUpts = {(0.5, -0.2), (2.5, -0.7)};
real[] ImUangles = {-60.0, 90.0};
int nImUpts = 2;

/*  Open sets in R^m, the image of U and phi^{-1}[V] under varphi.            */
pair[] varphiUpts = {(0.0, 0.0), (2.7, 0.1), (3.1, 2.1), (1.0, 2.1)};
real[] varphiUangles = {-60.0, 70.0, 90.0, -170.0};
int nvarphiUpts = 4;

pair[] varphiUVpts = {(1.0, 0.8), (3.1, 2.1), (1.0, 2.1)};
real[] varphiUVangles = {70.0, 90.0, -170.0};
int nvarphiUVpts = 3;

/*  Sets in R^n, the image of V under psi and psi[V cap phi[U]].              */
pair[] psiVpts = {(0.2, 0.9), (2.4, 0.3), (3.0, 1.0), (1.5, 1.9)};
real[] psiVangles = {-60.0, 30.0, 90.0, -170.0};
int npsiVpts = 4;

pair[] psiUVpts = {(1.5, 1.9), (0.2, 0.9), (2.0, 1.2)};
real[] psiUVangles = {-170.0, -60.0, 90.0};
int npsiUVpts = 3;

transform NShift = shift(6.4, 0.0);
transform RmShift = shift(0.0, -5.0);
transform RnShift = shift(8.0, -5.0);

/*  Draw M and N and the open sets inside the two manifolds.                  */
g = PathFromPointsAndAngles(Mpts, Mangles, nMpts, true);
draw(g);

g = PathFromPointsAndAngles(Upts, Uangles, nUpts, true);
filldraw(g, Upen, dpen);

g = PathFromPointsAndAngles(VPpts, VPangles, nVPpts, true);
filldraw(g, Vpen, dpen);

g = PathFromPointsAndAngles(Npts, Nangles, nNpts, true);
draw(NShift*g);

g = PathFromPointsAndAngles(ImUpts, ImUangles, nImUpts, true);
filldraw(NShift*g, Upen, dpen);

g = PathFromPointsAndAngles(Vpts, Vangles, nVpts, true);
filldraw(NShift*g, Vpen, dpen);

/*  Draw R^m and the open sets varphi[U], varphi[U cap phi^{-1}[v]].          */
draw(RmShift * ((-0.5, 0.0) -- (3.0, 0.0)));

L = Label("$\mathbb{R}^{m}$", position=1.0);
draw(L, RmShift*((0.0, -0.5) -- (0.0, 3.0)), E, SharpArrow(arsize));

g = PathFromPointsAndAngles(varphiUpts, varphiUangles, nvarphiUpts, true);
filldraw(RmShift*g, Upen, dpen);

g = PathFromPointsAndAngles(varphiUVpts, varphiUVangles, nvarphiUVpts, true);
filldraw(RmShift*g, Vpen, dpen);

/*  Draw R^n and the open set psi[V], and psi[V cap phi[U]].                  */
L = Label("$\mathbb{R}^{n}$", position=1.0);
draw(RnShift*((-0.5, 0.0) -- (3.0, 0.0)), SharpArrow(arsize));
draw(L, RnShift*((0.0, -0.5) -- (0.0, 3.0)), E, SharpArrow(arsize));

g = PathFromPointsAndAngles(psiVpts, psiVangles, npsiVpts, true);
filldraw(RnShift*g, Vpen, dpen);

g = PathFromPointsAndAngles(psiUVpts, psiUVangles, npsiUVpts, true);
filldraw(RnShift*g, Upen, dpen);

/*  Draw a donut hole inside the manifold M.                                  */
draw((0.5, 0.1){dir(-50.0)} .. (1.8, 0.1){dir(50.0)});
draw((0.6, 0.0){dir(50.0)} .. (1.7, 0.0){dir(-50.0)});

/*  Draw and label the function phi between M and N.                          */
g = (5.2, 1.0){dir(30.0)} .. {dir(-30.0)}(6.8, 1.0);
draw("$\phi$", g, N, SharpArrow(arsize));

/*  Label things in the manifold M.                                           */
label("$M$", (1.5, -0.8));
label("$\mathcal{U}$", (3.6, 0.5));
label("$\phi^{-1}[\mathcal{V}]$", (4.4, -0.6));
label("$\mathcal{U}\cap\phi^{-1}[\mathcal{V}]$", (3.45, -0.2));

/*  Label things in the manifold N.                                           */
label("$N$", NShift*(4.0, -0.8));
label("$\phi[\mathcal{U}]$", NShift*(1.1, 0.4));
label("$\mathcal{V}$", NShift*(2.8, -0.4));
label("$\mathcal{V}\cap\phi[\mathcal{U}]$", NShift*(1.75, -0.4));

/*  Label things in R^m.                                                      */
label("$\varphi[\mathcal{U}]$", RmShift * (1.6, 0.4));

L = "$\varphi\Big[\mathcal{U}\cap\phi^{-1}[\mathcal{V}]\Big]$";
label(L, RmShift * (1.6, 1.7));

/*  Label things in R^n.                                                      */
label("$\psi[\mathcal{V}]$", RnShift * (2.4, 1.1));

L = "$\psi\Big[\mathcal{V}\cap\phi[\mathcal{U}]\Big]$";
label(L, RnShift * (1.1, 1.2));

/*  Label functions and charts on the two manifolds.                          */
L = Label("$\psi\circ\phi\circ\varphi^{-1}$");
draw(L, (3.5, -4.5){dir(-30)} .. (7.5, -4.5){dir(30)}, SharpArrow(arsize));

L = Label("$\varphi$");
draw(L, (2.0, -1.5) -- (1.5, -2.5), SharpArrow(arsize));

L = Label("$\psi$");
draw(L, (9.2, -1.7) -- (9.6, -2.7), SharpArrow(arsize));
