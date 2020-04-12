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
pen ap = black+linewidth(0.8pt);

// Pen for the circle and triangles.
pen cpen = black+linewidth(0.4pt);
pen tpen = black+linewidth(0.2pt);

// Filler for the triangles.
pen fpen = red+opacity(0.5);

real ar = 5bp;

pair O = (0.0, 0.0);

real R = 1.0;

real len = 1.2;

draw(circle(O, R), cpen);

draw(Label("$x$", position=1), (-len, 0.0)--(len, 0.0), S, ap, SharpArrows(ar));
draw(Label("$y$", position=1), (0.0, -len)--(0.0, len), W, ap, SharpArrows(ar));

path g = scale(R)*expi(pi/4)--scale(R)*expi(5pi/4)--
         scale(R)*expi(3pi/4)--scale(R)*expi(7pi/4)--cycle;

filldraw(g, fpen, tpen);
