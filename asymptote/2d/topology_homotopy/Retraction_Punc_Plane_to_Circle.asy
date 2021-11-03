// Some boiler plate stuff.
import settings;
import custom_arrows;
settings.outformat = "pdf";

// Needed for mathbb command.
texpreamble("\usepackage{amssymb}");

// Size of the output figure.
size(256);

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
real ir1 = 0.3;
real or1 = 0.9;

real ir2 = 1.1;
real or2 = 1.7;

// Radius of the image.
real R = 2.0;

// Shift for the second image.
real xshift = 3.2*R;

// Variable for looping over angles.
pair phi;

// The origin.
pair O = (0.0, 0.0);

// Pen for drawing axes and gray arrows.
pen dpen = black+linewidth(0.5pt);
pen gpen = gray(0.5)+linewidth(1pt);

// Size of the axes.
real ax = 1.8;

// Background for the plane.
radialshade(scale(R)*unitcircle, gpen, O, 0.0, white, O, R);

// Draw the x axos.
L = Label("$x$", position = 1.0, S);
draw(L, (-ax, 0.0)--(ax, 0.0), dpen, SharpArrow(arsize));
draw(L, (xshift-ax, 0.0)--(xshift+ax, 0.0), dpen, SharpArrow(arsize));

L = Label("$y$", position = 1.0, W);
draw(L, (0.0, -ax)--(0.0, ax), dpen, SharpArrow(arsize));
draw(L, (xshift, -ax)--(xshift, ax), dpen, SharpArrow(arsize));

for(i=0; i<n; ++i){
    phi = expi(2*pi*i/n+pi/n);
    g = scale(ir1)*phi--scale(or1)*phi;
    draw(g, gpen, SharpArrow(StealthHead, arsize));

    g = scale(or2)*phi--scale(ir2)*phi;
    draw(g, gpen, SharpArrow(StealthHead, arsize));
}

// Dot for the origin.
filldraw(circle(O, 0.1), white, black);

draw(unitcircle, dpen+dashed);

label("$\mathbb{R}^{2}\setminus\{(0,\,0)\}$", (R, R), fontsize(8pt));

draw((1.2*R, 0.0)--(2.0*R, 0.0), blue, SharpArrow(StealthHead, arsize));

draw(shift(xshift)*unitcircle, dpen);
label("$\mathbb{S}^{1}$", (xshift+0.5*R, 0.5*R), fontsize(8pt));