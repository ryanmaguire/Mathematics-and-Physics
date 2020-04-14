// Seting output format to "pdf".
import settings;
import graph;

if(settings.render < 0)    settings.render    = 8;
if(!settings.multipleView) settings.batchView = false;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Make sure _custom_arrows.asy is in your $PATH.
// This file is found in the asymptote/ folder of this project.
import _custom_arrows;

// Default pen for drawing.
defaultpen(black+linewidth(0.4pt));

// Size of the output figure.
size(128);

// Path for drawing stuff.
path g;

// // Pen for the function, axes, dashed lines, and filling.
pen fpen = deepblue+linewidth(0.5pt);
pen apen = black+linewidth(0.8pt);
pen dpen = linewidth(0.2pt)+linetype("8 8");

// Size of the arrow head.
real arsize = 5bp;

// Radius of the dots to be drawn.
real rbig   = 0.01;
real rsmall = 0.005;

// Variable used for indexing.
int i;
int n = 6;

// Number of samples. Make this a power of 2 since we are performing bisection.
int samples = 128;

// First and last x values to be plotted.
real start = 0.0;
real end   = 1.0;

// Min and max values for the x-axis.
real xmin = -0.1;
real xmax = 1.15;

// Min and max values for the y-axis.
real ymin = -0.1;
real ymax =  1.1;

// Continuous function to be plotted.
real f(real x) {return exp(-x*x)+1.3*x*x-0.7;};

// Variables used during the computation.
real x0, y0, xn, yn;

// Plot the axes.
g = (xmin, 0.0)--(xmax, 0.0);
draw(Label("$x$", position=1, fontsize(10pt)), g, S, apen, SharpArrow(arsize));

g = (0.0, ymin)--(0.0, ymax);
draw(Label("$y$", position=1, fontsize(10pt)), g, W, apen, SharpArrow(arsize));

// Add tick marks to the x axis.
for (i=1; i<=4*(int)xmax; ++i){
    if ((i % 4) == 0){
        draw((i/4, 0) -- (i/4, -0.05));
        label("$"+string((int)i/4)+"$", (i/4, -0.1), fontsize(7pt));
    }
    else draw((i/4, 0) -- (i/4, -0.025));
}

// Add tick marks to the y axis.
for (i=1; i<=4*(int)ymax; ++i){
    if ((i % 4) == 0){
        draw((0, i/4) -- (-0.05, i/4));
        label("$"+string((int)i/4)+"$", (-0.1, i/4), fontsize(7pt));
    }
    else draw((0, i/4) -- (-0.025, i/4));
}

// Plot the function.
g = graph(f, start, end, n=samples);
draw(g, fpen);

// Set the point about which continuity is being demonstrated.
x0 = 0.67;
y0 = f(x0);

// Draw lines from the axes to the point of interest.
draw((x0, 0)--(x0, y0)--(0, y0));

for (i=0; i<n; ++i){
    xn = x0-1/2^(1+i);
    yn = f(xn);
    draw((xn, 0)--(xn, yn)--(0, yn), dpen);
    filldraw(circle((xn, yn), rsmall), black);
}

// Label the y axis.
label("$y_{0}$", (-0.03, y0), W, fontsize(7pt));

// Label the x axis.
label("$x_{0}$", (x0, -0.03), S, fontsize(7pt));

// Place a dot at the point of interest.
filldraw(circle((x0, y0), rbig), black);

// Label the function.
x0 = 0.9;
y0 = f(x0);

label("$f$", (x0, y0), E, fontsize(9pt));