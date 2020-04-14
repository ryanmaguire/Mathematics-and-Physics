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

// Default pen used for the axes.
defaultpen(black+linewidth(0.8pt));

// Pen for the circle and triangles.
pen cpen = black+linewidth(0.4pt);
pen tpen = black+linewidth(0.2pt);

// Filler for the triangles.
pen fpen = red+opacity(0.5);

// Size of the arrow head.
real arsize = 5bp;

// The origin.
pair O = (0.0, 0.0);

// Radius of the circle.
real R = 1.0;

// Length of the axes.
real len = 1.2;

// Draw the circle.
draw(circle(O, R), cpen);

// Draw and label the axes.
draw(Label("$x$", position=1), (-len, 0.0)--(len, 0.0), S, SharpArrows(arsize));
draw(Label("$y$", position=1), (0.0, -len)--(0.0, len), W, SharpArrows(arsize));

// And draw the object inside of the circle.
path g = scale(R)*expi(pi/4)--scale(R)*expi(5pi/4)--
         scale(R)*expi(3pi/4)--scale(R)*expi(7pi/4)--cycle;
filldraw(g, fpen, tpen);
