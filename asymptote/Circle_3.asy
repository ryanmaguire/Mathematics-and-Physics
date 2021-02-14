// Make sure _custom_arrows.asy, _asy_preamble_2d, and _euc_geo_2d are in your
// ASYMPTOTE_DIR environment variable. These are found in the asymptote/ folder.
import _asy_preamble_2d;
import _custom_arrows;
import _euclidean;

// Size of the output figure.
size(128);

// Filler for the triangles.
pen fillp = red+opacity(0.5);

// Radius of the circle and length of the axes.
real R = 1.0;
real len = 1.2;

// Transform for scaling by radius.
transform T = scale(R, R);

// The origin and points for the x and y axes.
pair O   = (0.0, 0.0);
pair[] X = {(-len, 0.0), (len, 0.0)};
pair[] Y = {(0.0, -len), (0.0, len)};

// Points for the object inside circle.
pair[] ObjPts = {T*expi(pi/4), T*expi(5pi/4), T*expi(3pi/4), T*expi(7pi/4)};
int ObjN = 4;

// Draw the circle.
draw(circle(O, R));

// Draw and label the axes.
draw(Label("$x$", position=1), X[0]--X[1], S, axesp, SharpArrows(arsize));
draw(Label("$y$", position=1), Y[0]--Y[1], W, axesp, SharpArrows(arsize));

// And draw the object inside of the circle.
filldraw(PolyFromPoints(ObjPts, ObjN, true), fillp, thinp);

