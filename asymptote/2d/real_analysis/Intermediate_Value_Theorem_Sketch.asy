// Import necessary stuff, set format to PDF file.
import graph;
import settings;
outformat="pdf";

// Size of the output figure.
size(256, 256);

// Variable used for indexing.
int i;

// Number of samples. Make this a power of 2 since we are performing bisection.
int samples = 128;

// First and last x values to be plotted.
real start  = 0.05;
real end    = start+1.0;

// Min and max values for the x-axis.
real xmin   = -0.1;
real xmax   = 1.15;

// Min and max values for the y-axis.
real ymin   = -0.35;
real ymax   = 0.55;

// Height of the dots used to label the points in the bisection sequence.
real height = 0.4;

// Variables used during the computation.
real x0, x1, y, mid;

// Hectic, but continuous, function that is to be plotted.
real f(real x) {
    x = x-start;
    int i;
    real result = 0.0;
    for(i=1; i<9; ++i){
        result += sin((i*i*i*i)*x)/(2*i);
    }
    result *= x-0.5;
    return result-0.1;
};

// Plot the function.
path g=graph(f, start, end, n=samples);
draw(g, black);

// Perform the bisection method to compute the root of f.
for (i=0; i<6; ++i){
    if (i == 0){
        x0 = start;
        mid = x0;
    }
    else if (i == 1){
        x1 = end;
        mid = x1;
    }
    else mid = (x0+x1)/2;

    y = f(mid);
    if      (y<0)   x0 = mid;
    else if (y>0)   x1 = mid;
    else break;

    draw ((mid, height) -- (mid, y), dashed);
    dot((mid, y));
    label("$x_{" +string(i)+ "}$", (mid, height), N, fontsize(9pt));
}

// Plot the axes.
xaxis(Label("$x$"), Arrow, xmin=xmin, xmax=xmax);
yaxis(Label("$y$"), Arrow, ymin=ymin, ymax=ymax);
