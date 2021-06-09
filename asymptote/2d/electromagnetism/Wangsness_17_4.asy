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

defaultpen(fontsize(7pt));

// Size of the output figure.
size(128);

pen dpen = black+linewidth(0.5pt)+linetype("4 4");
pen apen = deepblue+linewidth(0.5pt)+fontsize(4pt);

pair O = (0.0, 0.0);
pair P = (2.0, 1.3);

real xlen = 3.0;
real ylen = 2.0;
real dx   = 0.7;
real dy   = 0.7;
real arsize = 5bp;

real R = 0.5;
real r = 0.3;
real fsize = 0.5pt;

pair Q = P+scale(r)*expi(pi/4);

draw(Label("$x$", position=1.0), O--(xlen, 0.0), N, SharpArrow(arsize));
draw(Label("$y$", position=1.0), O--(0.0, ylen), E, SharpArrow(arsize));
draw(circle(P, R), black);

draw(Label("$r$", fontsize(fsize)), P--Q);
draw("$\rho$", (0.0, Q.y)--Q, N, dpen);
draw(Label("$a$", fontsize(fsize)), P--(P+scale(R)*expi(9pi/5)), SW);

arsize = 3bp;
draw(Label("$\tilde{x}$", position=1.0), P--(P+(dx, 0)),
     N, apen, SharpArrow(arsize));

draw(Label("$\tilde{y}$", position=1.0), P--(P+(0, dy)),
     E, apen, SharpArrow(arsize));
