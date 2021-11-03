// Some boiler plate stuff.
import settings;
import graph;
import custom_arrows;
settings.outformat="pdf";

// Needed for mathbb command.
texpreamble("\usepackage{amssymb}");

// Size of the output figure.
size(256);

// Variables for size of the arrow head.
real arsize = 5bp;

// Path for drawing stuff.
path g;

// The origin.
pair O = (0.0, 0.0);

// Radius of the image.
real r = 1.3;

// For labelling the axes.
Label L;

// Used for reflecting later.
pair A, B;

// Shift for the second image.
real xshift = -3*r;
real yshift = 0.5*r;

// Scale for the ellipse in the second image.
real yscale = 0.3;

// Pen used for the main function.
pen dpen = deepblue;

int samples = 100;

real trefoil(real theta){
    real u = cos(1.5*theta);
    u = 1.0+u*u;
    return 0.5*u;
}

g = circle(O, r);
radialshade(g, gray(0.5)+opacity(0.5), O, 0, white+opacity(0.3), O, r);

L = Label("$x$", position=1.0, S);
draw(L, (-r,  0)--(r, 0), SharpArrow(arsize));

L = Label("$y$", position=1.0, W);
draw(L, ( 0, -r)--(0, r), SharpArrow(arsize));

g = polargraph(trefoil, 0, 2pi, samples, operator ..);
draw(g, dpen);

g = ellipse(O, r, yscale);
draw(shift(xshift, yshift)*g);

g = (r, 0)--(r, -r);
draw(shift(xshift, yshift)*g);
draw(shift(xshift-2*r, yshift)*g);

g = scale(1, yscale)*arc((0, 0), r, 180, 360);
draw(shift(xshift, yshift-r)*g);

A = (-r, -r);
B = (+r, -r);
g = reflect(A, B)*g;
draw(shift(xshift, yshift+r)*g, dashed);

label("$\mathbb{S}^{1}$", (xshift-r, 0.7*r));
label("$\mathbb{S}^{1}\times{I}$", (xshift-1.4*r, 0), fontsize(8pt));

label("$\mathbb{R}^{2}$", (0.8*r, 0.8*r));
label("$f[\mathbb{S}^{1}]$", (-0.7*r, 0.7*r), dpen+fontsize(8pt));
