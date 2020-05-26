// Some boiler plate stuff.
import settings;
import graph;
import _custom_arrows;
settings.render = 8;
settings.outformat="pdf";

// Size of the output figure.
size(128);

// Lengths of the plots.
real start = -0.4;
real fin   =  1.7;

// Start and end of the curve.
real xmin = -0.3;
real xmax =  1.5;

// Label for the axes.
Label L;

// Number of samples used for curves.
int samples = 20;

// Size of the arrow head.
real arsize = 5bp;

// Pen used for axes.
pen apen = black+linewidth(0.5pt);

// Path for drawing curves.
path g;

// Curve to be drawn.
real f(real x){return exp(x-1.0);}

// Draw the axes.
L = Label("$x$", position=1, S);
draw(L, (start, 0.0)--(fin, 0.0), apen, SharpArrow(arsize));

L = Label("$y$", position=1, W);
draw(L, (0.0, start)--(0.0, fin), apen, SharpArrow(arsize));

// Draw a curve.
g = graph(f, xmin, xmax, samples, operator ..);
draw(g, deepblue, SharpArrow(StealthHead, arsize));

// Add a curve with the same slope as the previous one.
g = reflect((0.0, 0.0), (1.0, 1.0))*g;
draw(g, deepred, SharpArrow(StealthHead, arsize));

// Add another curve with the same slope.
xmax += 0.1;
draw((xmin, xmin)--(xmax, xmax), deepgreen, SharpArrow(StealthHead, arsize));

// Put a dot at the point of interest.
dot("$p$", (1, 1), S);