// Some boiler plate stuff.
import settings;

if(!settings.multipleView) settings.batchView = false;
if(settings.render < 0)    settings.render = 4;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Make sure _custom_arrows.asy is in your $PATH.
// This file is found in the asymptote/ folder of this project.
import _custom_arrows;

// Size of the output figure.
size(128);

// Size of the arrow head.
real arsize = 5bp;

// Label for the axes.
Label L;

// Variable for indexing.
int i;

// Number of arrows to dray.
int n = 4;

// Path for the arrows.
path g;

// Inner and outer radii of the arrows.
real ir = 0.7;
real or = 2.3;

// Radius of the image.
real R = 3.0;

// Variable for looping over angles.
pair phi;

// The origin.
pair O = (0.0, 0.0);

// Pen for drawing axes and gray arrows.
pen dpen = black+linewidth(0.5pt);
pen gpen = gray(0.5)+linewidth(1pt);

// Size of the axes.
real ax = 3.0;

// Background for the plane.
radialshade(scale(R)*unitcircle, gpen, O, 0.0, white, O, R);

// Draw the x axos.
L = Label("$x$", position = 1.0, S);
draw(L, (-ax, 0.0)--(ax, 0.0), dpen, SharpArrow(arsize));

L = Label("$y$", position = 1.0, W);
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