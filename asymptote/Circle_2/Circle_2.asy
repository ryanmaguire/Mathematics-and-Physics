// Boilerplate stuff.
import settings;
import graph;
import _custom_arrows;

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

pair O = (0.0, 0.0);
real R = 1.0;
real r = 0.2;
pair A = scale(R)*expi(3pi/4);
pair B = scale(R)*expi(-pi/4);
pair D = scale(R)*expi(pi/4);

real delta = atan(D.y/D.x);

draw(circle(O, R));
draw(O--(2.0, 0.0), SharpArrow());
draw(O--(0.0, 2.0), SharpArrow());

draw(A--(A+D)--(B+D)--B--cycle);
draw(O--D);

draw("$\delta$", arc(O, r, 90, 180*delta/pi), N+0.5E);

label("$A$", A+D, NW);
label("$B$", B+D, NE);