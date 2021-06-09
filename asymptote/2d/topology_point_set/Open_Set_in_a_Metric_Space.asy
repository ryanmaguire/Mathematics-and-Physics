// Seting output format to "pdf".
import settings;
import graph;

if(settings.render < 0)    settings.render    = 4;
if(!settings.multipleView) settings.batchView = false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Needed for the use of mathbb and mathcal commands.
texpreamble("\usepackage{amssymb}");

// Size of the output figure.
size(240);

// Used for drawing paths.
path g;

// Variables for the dot x.
real radius = 0.25;
pair A = (2.8, -0.3);
pair B = A + scale(radius)*expi(pi/6);

// Pens used for filling and drawing.
pen fpen = red+0.3*white;
pen dpen = linewidth(0.5pt);

// Draw the manifold X, shifted over to the left.
g = (0.0,  0.0){dir(90)}..(2.0,   1.0){dir(0)}..
    (4.0,  0.0){dir(-90)}..(2.0, -1.0){dir(180)}..
    (0.0, -1.0){dir(150)}..cycle;

draw(g, dpen);

// Draw a cyan blob for U.
fpen = gray(0.8);

g = (2.0, 0.0){dir(30)}.. (2.7,  0.5){dir(0)}..
    (3.5, 0.0){dir(-90)}..(3.2, -0.6){dir(180)}..
    (2.2, -0.8){dir(150)}..cycle;

filldraw(g, fpen, dpen+linetype("8 4"));

// Pen for ball about the point x.
fpen = cyan;
filldraw(shift(A)*scale(radius)*unitcircle, fpen, dpen+linetype("8 4"));
dot(A);
label("$x$", A, SW);
draw("$\varepsilon$", A--B, dpen);

// Add some labels.
label("$\mathcal{U}$", (3.2, 0.0));
label("$X$", (1.0,  0.4));