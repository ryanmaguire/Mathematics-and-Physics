// Boilerplate stuff.
import settings;

// Make sure _custom_arrows.asy is in your ASYMPTOTE_DIR environment variable.
// This file is found in the asymptote/ folder.
import _custom_arrows;

if(settings.render < 0)    settings.render    = 8;
if(!settings.multipleView) settings.batchView = false;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Pen used for labels and drawing.
defaultpen(fontsize(7pt));

// Size of the output figure.
size(128);

// Size of the arrowhead.
real arsize = 5bp;

// The origin.
pair O = (0.0, 0.0);

// Radius of the big circle.
real R = 1.0;

// Length of the axes.
real len = 1.8;

// Radius for drawing and labelling the angle delta.
real r = 0.2;

// Various points on the circle used to draw the rectangle.
pair A = scale(R)*expi(3pi/4);
pair B = scale(R)*expi(-pi/4);
pair D = scale(R)*expi(pi/4);

// The angle the point D makes.
real delta = atan(D.y/D.x);

// Draw the circle and add axes.
draw(circle(O, R));
draw(O--(len, 0.0), SharpArrow(arsize));
draw(O--(0.0, len), SharpArrow(arsize));

// Draw the rectangle.
draw(A--(A+D)--(B+D)--B--cycle);
draw(O--D);

// Add the angle and label everything.
draw("$\delta$", arc(O, r, 90, 180*delta/pi), N+0.5E);
label("$A$", A+D, NW);
label("$B$", B+D, NE);
