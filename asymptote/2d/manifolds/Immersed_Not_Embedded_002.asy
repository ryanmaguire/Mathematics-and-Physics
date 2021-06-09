// Some boiler plate stuff.
import settings;
import graph;
import _custom_arrows;
settings.render = 4;
settings.outformat="pdf";

// Size of the output figure.
size(128);

// Pens used for drawing.
pen dpen = deepblue+linewidth(0.4pt);
pen bpen = black+linewidth(0.4pt);

// Margin for the lemniscate arrows.
margin margins = TrueMargin(0.05cm, 0.05cm);

// Label for the axes.
Label L;

// Size of the arrow head.
real arsize = 5bp;

// Lengths of the axes.
real xlen = 1.2;
real ylen = 1.2;

// Variable used for drawing lines.
path p;

// Parametric equation for the lemiscate.
pair f(real theta){return (sin(theta), sin(2*theta));}

// Fill in two circles representing the holes.
L = Label("$x$", position=1, S, fontsize(9pt));
draw(L, (-xlen, 0.0)--(xlen, 0.0), bpen, SharpArrow(arsize));

L = Label("$y$", position=1, W, fontsize(9pt));
draw(L, (0.0, -ylen)--(0.0, ylen), bpen, SharpArrow(arsize));

// Draw the lemniscate.
p = graph(f, 0, 2pi, 300, operator ..);
draw(p, dpen, SharpArrows(StealthHead, arsize), margins);