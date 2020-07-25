// Make sure _custom_arrows.asy and _asy_preamble_2d are in your ASYMPTOTE_DIR
// environment variable. These files are found in the asymptote/ folder.
import _asy_preamble_2d;
import _custom_arrows;

// Size of the output figure.
size(128);

// Radius of the big circle, length of the axes, and radius of circle for angle.
real R = 1.0;
real len = 1.8;
real rAng = 0.2;

// Various points on the circle used to draw the rectangle.
pair A = scale(R)*expi(3pi/4);
pair B = scale(R)*expi(-pi/4);
pair D = scale(R)*expi(pi/4);
pair X = (len, 0.0);
pair Y = (0.0, len);
pair O = (0.0, 0.0);

// The angle the point D makes.
real delta = atan(D.y/D.x);

// Draw the circle and add axes.
draw(circle(O, R));
draw(Label("$B$", position=1), O--X, S, axesp, SharpArrow(arsize));
draw(Label("$A$", position=1), O--Y, W, axesp, SharpArrow(arsize));

// Draw the rectangle.
draw(A--(A+D)--(B+D)--B--cycle);
draw(O--D);

// Add the angle and label.
draw("$\delta$", arc(O, rAng, 90, 180*delta/pi), N+0.5E);
