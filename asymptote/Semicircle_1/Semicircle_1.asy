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

// Axes pen.
pen apen = black+linewidth(0.8pt);

// Pen for the circle and triangles.
pen cpen = black+linewidth(0.2pt);

// Filler for the triangles.
pen fpen = red+opacity(0.5);

real R = 1.0;
real ar = 5bp;
real xlen = 1.3;
real ylen = 0.2;

pair O = (0.0, 0.0);
pair A = scale(R)*expi(3pi/8);
pair B = scale(R)*expi(pi);
pair C = scale(-0.38)*A;
pair T = (A.y, -A.x);

draw(Label("$x$", position=1), (-xlen, 0)--(xlen, 0), N, apen, SharpArrow(ar));
draw(Label("$y$", position=1), (0, -ylen)--(0, xlen), E, apen, SharpArrow(ar));

filldraw(arc(O, R, 0, 180)--cycle, fpen, cpen);
draw("$\ell_{\theta}$", C--A);
draw(B--(B+2*T));
draw(A--(A+T));
draw(A--(A-T));

label("$A$", C, SW);
label("$B$", A, NE);
