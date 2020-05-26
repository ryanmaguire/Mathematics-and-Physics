// Seting output format to "pdf".
import settings;
import graph;
import _custom_arrows;

if(settings.render < 0)    settings.render    = 4;
if(!settings.multipleView) settings.batchView = false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

defaultpen(black+linewidth(0.4pt)+fontsize(7pt));

// Size of the output figure.
size(128);

pair MidPoint(pair A, pair B){return scale(0.5)*(A+B);}

pair O  = ( 0.0, 0.0);
pair X0 = (-1.0, 0.0);
pair Y0 = ( 0.0, 1.0);
pair Z0 = ( 0.3, 0.0);

real r = 0.2;
real angle = atan((Y0.y-X0.y)/(Y0.x-X0.x));

draw("$a$", Y0--Z0, NE);
draw("$b$", Z0--X0, S);
draw("$c$", X0--Y0, NW);
draw("$h$", Y0--O,  SW);

draw("$\alpha$", arc(X0, r, 0, 180*angle/pi));

label("$\ell_{1}$", MidPoint(X0, O), N);
label("$\ell_{2}$", MidPoint(Z0, O), N);
