// Import necessary stuff, set format to PDF file.
import graph;
import settings;
import custom_arrows;
settings.outformat="pdf";

// Size of the output figure.
size(256);

// Color of the spaces.
pen dpen = deepblue;

// Lengths in the two directions.
real xlength = 9.0;
real ylength = 1.5;

// Height of the intervals.
real height = 0.8;

// Radius of the dots.
real r = 0.06;

// Variable for indexing.
int i;

// Number of unit intervals to draw.
int n = 3;

// Size of the arrow head.
real arsize = 5bp;

// Draw the top line.
draw((0, ylength)--(xlength, ylength), dpen, SharpArrows(arsize));

// Draw the bottom line.
draw((0, 0.0)--(xlength, 0.0), dpen, SharpArrows(arsize));

for(i=1; i<=n; ++i){
    draw((i, 0.0)--(i, height), dpen);
    draw((i, ylength)--(i, ylength+height), dpen);
    filldraw(shift(i, height)*scale(r)*unitcircle, white, dpen);
    filldraw(shift(i, ylength+height)*scale(r)*unitcircle, white, dpen);
}

draw(circle((i, 0.5*height), 0.5*height), dpen);
draw(circle((i, 0.5*height+ylength), 0.5*height), dpen);

i += 1;

draw((i, ylength)--(i, ylength+height), dpen);
filldraw(shift(i, ylength+height)*scale(r)*unitcircle, white, dpen);
draw(circle((i, 0.5*height), 0.5*height), dpen);

i += 1;

// Increment n so we may loop over the circles.
n = i+3;

for(; i<n; ++i){
    draw(circle((i, 0.5*height), 0.5*height), dpen);
    draw(circle((i, 0.5*height+ylength), 0.5*height), dpen);
}