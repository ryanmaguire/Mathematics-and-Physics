// Import necessary stuff, set format to PDF file.
import custom_arrows;
import graph;
import settings;
settings.outformat="pdf";

// Size of the output figure.
size(256, 256, IgnoreAspect);

// Pens used for drawing normal and dashed lines.
pen lpen = deepblue+linewidth(1pt);
pen dpen = deepblue+linewidth(0.5pt)+linetype("8 4");

// Size of the arrow head;
real arsize = 5bp;

// Margin for the arrows.
real armarg = 0.6cm;

// Start and end of the function in the x direction.
real start = 0.0;
real end   = 1.0;

// Variable for indexing.
int i;

// Number of dashed lines to draw.
int n = 10;

// Spacing between points.
real dx = 1.0/n;

// Variables for drawing lines.
real x, y0, y1;

// Bounds for the axes.
real xmin = 0.0;
real xmax = 1.2;
real ymin = 0.0;
real ymax = 3.2;

// Scale for the aspect ratio.
real aspect = xmax/ymax;

// Number of samples in the function.
int samples = 50;

// Label for the functions.
Label L;

// Position of the arrows;
position pos=0.5;

real H0(real x){return exp(x);}
real H1(real x){return x^3;}

// Plot the functions.
draw(graph(H0, start, end, n=samples, operator ..), lpen);
draw(graph(H1, start, end, n=samples, operator ..), lpen);

label("$x$", (xmax, 0.0),  S);
label("$y$", (0.0,  ymax), W);

for (i=1; i<=n; ++i){
    x  = i*dx;
    y0 = H0(x);
    y1 = H1(x);
    draw((x, y0)--(x, y1), p=dpen, MidSharpArrow(StealthHead, size=arsize));
}

// Draw the x axis for the first plot, loop over points to draw tick marks.
draw((xmin, 0)--(xmax, 0), SharpArrow(arsize));
for (i=0; i<=4*(int)xmax; ++i){
    if ((i % 4) == 0){
        draw((i/4, 0) -- (i/4, -0.1));
        label("$"+string((int)i/4)+"$", (i/4, -0.2), fontsize(9pt));
    }
    else draw((i/4, 0) -- (i/4, -0.05));
}

// Draw the y axis for the first plot, loop over points to draw tick marks.
draw((0, ymin)--(0, ymax), SharpArrow(arsize));
for (i=0; i<=2*(int)ymax; ++i){
    if ((i % 2) == 0){
        draw((0, i/2) -- (-0.1*aspect, i/2));
        label("$"+string((int)i/2)+"$", (-0.2*aspect, i/2), fontsize(9pt));
    }
    else draw((0, i/2) -- (-0.05*aspect, i/2));
}

label("$f(x)=\exp(x)$", (0.40, 2.0));
label("$g(x)=x^{3}$",   (1.00, 0.3));
label("$H(x,t)$",       (1.15, 1.80));