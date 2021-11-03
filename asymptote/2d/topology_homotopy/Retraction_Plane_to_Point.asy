// Some boiler plate stuff.
import settings;
import custom_arrows;
settings.outformat = "pdf";

// Size of the output figure.
size(128);

// Size of the arrow head.
real arsize = 5bp;

// Font size for labels.
real fsize = 9pt;

// Label for the axes.
Label L;

// Variable for indexing.
int i;

// Number of arrows to dray.
int n = 4;

// Path for the arrows.
path g;

// Inner and outer radii of the arrows.
real ir = 0.5;
real or = 1.5;

// Radius of the image.
real R = 1.9;

// Variable for looping over angles.
pair phi;

// The origin.
pair O = (0.0, 0.0);

// Pen for drawing axes and gray arrows.
pen dpen = black+linewidth(0.5pt);
pen gpen = gray(0.5)+linewidth(1pt);

// Size of the axes.
real ax = 2.0;

// Background for the plane.
radialshade(scale(R)*unitcircle, gpen, O, 0.0, white, O, R);

// Draw the x axos.
L = Label("$x$", position = 1.0, S, fontsize(fsize));
draw(L, (-ax, 0.0)--(ax, 0.0), dpen, SharpArrow(arsize));

L = Label("$y$", position = 1.0, W, fontsize(fsize));
draw(L, (0.0, -ax)--(0.0, ax), dpen, SharpArrow(arsize));

// Set the arrow head to be larger for the gray arrows.
arsize = 7bp;

for(i=0; i<n; ++i){
    phi = expi(2*pi*i/n+pi/n);
    g = scale(or)*phi--scale(ir)*phi;
    draw(g, gpen, SharpArrow(StealthHead, arsize));
}

// Dot for the origin.
filldraw(circle(O, 0.1), black);