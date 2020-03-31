// Seting output format to "pdf".
import settings;
import graph;

// Make sure _custom_arrows.asy is in your $PATH.
// This file is found in the asymptote/ folder of this project.
import _custom_arrows;
settings.outformat = "pdf";
settings.render = 4;
settings.prc = false;

// Size of the output figure.
size(200);

// Path for drawing stuff.
path g;

// Color for the function.
pen fpen = deepblue;

// Pen for the axes.
pen apen = black+linewidth(1pt);

// Pen for dashed lines.
pen dpen = linewidth(0.3pt) + dashed;

// Size of the arrow head.
real arsize = 5bp;

// Variable used for indexing.
int i;

// Number of samples. Make this a power of 2 since we are performing bisection.
int samples = 128;

// First and last x values to be plotted.
real start  = 0.0;
real end    = 1.0;

// Min and max values for the x-axis.
real xmin   = -0.1;
real xmax   = 1.15;

// Min and max values for the y-axis.
real ymin   = -0.1;
real ymax   =  1.1;

// Continuous function to be plotted.
real f(real x) {return exp(-x*x)+1.3*x*x-0.7;};

// Variables used during the computation.
real x0, y0, xp, yp, xm, ym, eps, delta;

// Plot the axes.
g = (xmin, 0.0)--(xmax, 0.0);
draw(Label("$x$", position=1), g, S, apen, SharpArrow(arsize));
g = (0.0, ymin)--(0.0, ymax);
draw(Label("$y$", position=1), g, W, SharpArrow(arsize));

// Add tick marks to the x axis.
for (i=1; i<=4*(int)xmax; ++i){
    if ((i % 4) == 0){
        draw((i/4, 0) -- (i/4, -0.05));
        label("$"+string((int)i/4)+"$", (i/4, -0.1), fontsize(9pt));
    }
    else draw((i/4, 0) -- (i/4, -0.025));
}

// Add tick marks to the y axis.
for (i=1; i<=4*(int)ymax; ++i){
    if ((i % 4) == 0){
        draw((0, i/4) -- (-0.05, i/4));
        label("$"+string((int)i/4)+"$", (-0.1, i/4), fontsize(9pt));
    }
    else draw((0, i/4) -- (-0.025, i/4));
}

// Plot the function.
path g=graph(f, start, end, n=samples);
draw(g, fpen);

// Set the point about which continuity is being demonstrated.
x0  = 0.67;
y0  = f(x0);

// Set epsilon, and choose an adequate delta.
eps = 0.06;
delta = 0.04;

// Set the error range for the x and y axes.
xm = x0 - delta;
xp = x0 + delta;
yp = y0 + eps;
ym = y0 - eps;

// Draw lines from the axes to the point of interest.
draw((x0, 0)--(x0, y0));
draw((0, y0)--(x0, y0));

// Draw dashed lines indicated the range of error allowed.
draw((0, ym)--(xmax-0.1, ym), dpen);
draw((0, yp)--(xmax-0.1, yp), dpen);
draw((xm, 0)--(xm, ymax-0.1), dpen);
draw((xp, 0)--(xp, ymax-0.1), dpen);

// Fill in the box showing the function is continuous (No jumps).
g = (xm, ym) -- (xm, yp) -- (xp, yp) -- (xp, ym) -- cycle;
filldraw(g, gray(0.7)+opacity(0.5), nullpen);

// Label the y axis.
label("$y_{0}$", (0, y0), W, fontsize(9pt));
label("$y_{0}+\varepsilon$", (x0/4, yp), N, fontsize(7pt));
label("$y_{0}-\varepsilon$", (x0/4, ym), S, fontsize(7pt));

// Label the x axis.
label("$x_{0}$", (x0, 0), S, fontsize(9pt));
label("$x_{0}+\delta$", (xp, y0/4), E, fontsize(7pt));
label("$x_{0}-\delta$", (xm, y0/4), W, fontsize(7pt));

// Place a dot at the point of interest.
dot((x0, y0));

// Label the function.
x0 = 0.9;
y0 = f(x0);

label("$f$", (x0, y0), E);