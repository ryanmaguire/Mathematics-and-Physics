// Make sure _asy_preamble_2d.asy and _euc_geo_2d.asy are in your ASYMPTOTE_DIR
// environment variable. These are found in the asymptote/ folder.
import _asy_preamble_2d;
import _euc_geo_2d;

// Size of the output figure.
size(128);

// Pen used for the circle and triangle.
pen fillp = red+0.3*white+opacity(0.7);

// Length of the axes.
real min = 0.2;
real max = 1.2;

// The three points on the circle we care about.
pair[] TriPts = {(-1.0, 0.0), (0.0, 1.0), (0.1, 0.0)};
int TriN = 3;

// Obtain the center of the circle these points define and compute radius.
pair P = FindCenterTwo(TriPts[0], TriPts[1], TriPts[2]);
real R = EucNormTwo(P-TriPts[0]);

// Draw and fill in the triangle.
filldraw(PolyFromPoints(TriPts, TriN, true), fillp, defaultpen);

// Draw the circle and mark the three points.
draw(circle(P, R));
filldraw(circle(TriPts[0], rDot), black);
filldraw(circle(TriPts[1], rDot), black);
filldraw(circle(TriPts[2], rDot), black);

// Draw axes.
draw((-max, 0.0)--(min, 0.0), axesp);
draw((0.0, -min)--(0.0, max), axesp);

// Label points on the x and y axes.
label("$-1$", (-1.02, -0.1));
label("$1$",  ( 0.10,  1.0));
