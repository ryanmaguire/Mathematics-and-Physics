// Seting output format to "pdf".
import settings;

// Needed for the use of mathbb and mathcal commands.
texpreamble("\usepackage{amssymb}");

// Make sure _custom_arrows.asy is in your $PATH.
// This file is found in the asymptote/ folder of this project.
import _custom_arrows;
settings.outformat = "pdf";
settings.render = 4;
settings.prc = false;

// Size of the output figure.
size(256);

// Size of the arrow head.
real arsize = 5bp;

// Used for drawing paths.
path g;

// Variables for shifting the graph.
real xshift = -8.0;
real yshift =  1.3;

// Pens used for filling and drawing.
pen fpen = red+0.3*white;
pen dpen = linewidth(0.5pt);

// Draw the coordinate axes for R^n.
draw((-0.5,  0.0)--(3.0, 0.0), dpen+0.5, SharpArrow(arsize));
draw(( 0.0, -0.5)--(0.0, 3.0), dpen+0.5, SharpArrow(arsize));

// Red blob for the image of U.
g = (0.5, 1.5){dir(30)} ..(1.2, 1.9){dir(0)}..
    (1.9, 1.4){dir(-90)}..(1.4, 0.2){dir(180)}..
    (0.4, 0.3){dir(150)}..cycle;
filldraw(g, fpen, dpen+linetype("8 4"));

// Labels for R^n and the map phi.
label("$\mathbb{R}^{n}$", (0.5, 3.0));
label("$\varphi[\mathcal{U}]$", (1.1, 1.0));

// Arrow representing the mapping phi.
g = (-3.6, 1.2){dir(30)}..{dir(-30)}(-1.0, 1.2);
draw("$\varphi$", g, SharpArrow(StealthHead, arsize));

// Draw the manifold X, shifted over to the left.
g = (0.0,  0.0){dir(90)}.. (1.0,  0.8){dir(0)}..
    (2.0,  0.8){dir(-30)}..(4.0,  0.0){dir(-90)}..
    (2.0, -1.5){dir(180)}..(0.0, -1.5){dir(150)}..cycle;

draw(shift(xshift, yshift)*g, dpen);

// Add a donut hole in the manifold.
g =  (0.5, -0.7){dir(-50)}..{dir(50)}(1.8, -0.7);
draw(shift(xshift, yshift)*g, dpen);

g = (0.6, -0.8){dir(50)}..{dir(-50)}(1.7, -0.8);
draw(shift(xshift, yshift)*g, dpen);

// Draw a cyan blob for U.
fpen = cyan;

g = (2.0, 0.0){dir(30)}.. (2.7,  0.5){dir(0)}..
    (3.5, 0.0){dir(-90)}..(3.2, -0.9){dir(180)}..
    (2.2, -0.8){dir(150)}..cycle;

filldraw(shift(xshift, yshift)*g, fpen, dpen+linetype("8 4"));

// Add some labels.
label("$\mathcal{U}$", shift(xshift, yshift)*(2.8, -0.2));
label("$X$", shift(xshift, yshift)*(1.0,  0.4));
