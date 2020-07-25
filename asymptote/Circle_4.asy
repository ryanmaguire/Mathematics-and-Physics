// Make sure _asy_preamble_2d.asy and _euc_geo.asy are in your ASYMPTOTE_DIR
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

// Size of the dots marking the points.
real r = 0.02;

// The three points on the circle we care about.
pair X0 = (-1.0, 0.0);
pair Y0 = ( 0.0, 1.0);
pair Z0 = ( 0.1, 0.0);

// Obtain the center of the circle these points define.
pair P = FindCenterTwo(X0, Y0, Z0);

// Find the radius of this circle.
real R = EucNormTwo(P-X0);

// Draw and fill in the triangle.
filldraw(X0--Y0--Z0--cycle, fillp, defaultpen);

// Draw the circle and mark the three points.
draw(circle(P, R));
filldraw(circle(X0, rDot), black);
filldraw(circle(Y0, rDot), black);
filldraw(circle(Z0, rDot), black);

// Draw axes.
draw((-max, 0.0)--(min, 0.0), axesp);
draw((0.0, -min)--(0.0, max), axesp);

// Label points on the x and y axes.
label("$-1$", (-1.02, -0.1));
label("$1$",  ( 0.10,  1.0));
