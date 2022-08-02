// This code uses an asymptote version of C code I had written for the
// NASA Cassini radio science team as a part of rss_ringoccs. Like this
// project, rss_ringoccs was released under the GNU GPL 3 license.
// https://github.com/NASA-Planetary-Science/rss_ringoccs

// Import necessary stuff, set format to PDF file.
import graph;
import custom_arrows;
import settings;
settings.outformat="pdf";

// Size of the output figure.
size(256);

// Variables used for indexing.
int i;

// Number of samples in the function..
int samples = 1000;

// The first and last values to be plotted.
real start =  0.005;
real end =  1.00;

// The start and end of the x axis.
real xmin = -0.20;
real xmax =  1.20;

// The start and end of the y axis.
real ymin = -1.10;
real ymax =  1.10;

// Size of the arrow heads.
real arsize = 5bp;

// Pen used for drawing functions.
pen db = deepblue;

real f(real x)
{
    return sin(1.0/x);
}

// Plot the function.
path g=graph(f, start, end, n=samples);
draw(g, db);

// Plot the axes.
label("$x$", (xmax, 0.0),         S, fontsize(9pt));
label("$y$", (0.0,  ymax),        W, fontsize(9pt));

// Draw the x axis for the first plot, loop over points to draw tick marks.
draw((xmin, 0)--(xmax, 0), SharpArrow(arsize));

for (i = 0; i <= 4*(int)xmax; ++i)
{
    if (((i % 4) == 0) && i != 0)
    {
        draw((i/4, 0) -- (i/4, -0.1));
        label("$"+string((int)i/4)+"$", (i/4, -0.2), fontsize(9pt));
    }
    else
        draw((i/4, 0) -- (i/4, -0.05));
}

// Draw the y axis for the first plot, loop over points to draw tick marks.
draw((0, ymin)--(0, ymax), SharpArrow(arsize));

for (i=0; i <= 2*(int)ymax; ++i)
{
    if (((i % 2) == 0) && i != 0)
    {
        draw((0, i/2) -- (-0.1, i/2));
        label("$"+string((int)i/2)+"$", (-0.2, i/2), fontsize(9pt));
    }
    else
        draw((0, i/2) -- (-0.05, i/2));
}

dot((0.0, 0.0));
