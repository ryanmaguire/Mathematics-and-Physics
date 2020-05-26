// Seting output format to "pdf".
import settings;

// Make sure _euc_geo.asy is in your ASYMPTOTE_DIR environment variable.
// This file is found in the asymptote/ folder.
import _euc_geo;

if(settings.render < 0)    settings.render    = 8;
if(!settings.multipleView) settings.batchView = false;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

defaultpen(fontsize(7pt));

// Size of the output figure.
size(128);

// Pen used for the circle and triangle.
pen cpen = deepblue;
pen tpen = red+opacity(0.5);

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

// Draw the circle and mark the three points.
draw(circle(P, R), cpen);
filldraw(circle(X0, r), black);
filldraw(circle(Y0, r), black);
filldraw(circle(Z0, r), black);

// Draw axes.
draw((-max, 0.0)--(min, 0.0));
draw((0.0, -min)--(0.0, max));

// Draw and fill in the triangle.
filldraw(X0--Y0--Z0--cycle, tpen);

// Label points on the x and y axes.
label("$-1$", (-1.02, -0.1));
label("$1$",  ( 0.10,  1.0));
