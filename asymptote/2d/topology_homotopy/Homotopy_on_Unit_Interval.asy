// Seting output format to "pdf".
import settings;
import graph;
import custom_arrows;
settings.outformat = "pdf";

// Size of the output figure.
size(128);

// Pen for drawing.
pen cpen = black+linewidth(1pt);
pen dpen = black+linewidth(0.4pt)+linetype("4 4");

// Font size.
real fsize = 10pt;

// Size of the arrow head.
real arsize = 5bp;

// Function for returning the midpoint of two points.
pair midpoint(pair A, pair B){return scale(0.5)*(A+B);}

// Path for drawing.
path g;

// For labelling stuff.
Label L;

// Margins for paths.
margin margins = TrueMargin(0.4cm, 0.13cm);

// Set points for upper curve.
pair a0 = (2.5, 1.3);
pair b0 = (2.7, 1.4);
pair c0 = (2.9, 1.7);
pair d0 = (3.2, 1.8);
pair e0 = (3.4, 1.9);

// Set points for lower curve.
pair a1 = (2.8, 0.6);
pair b1 = (3.0, 0.6);
pair c1 = (3.3, 0.5);
pair d1 = (3.5, 0.9);
pair e1 = (3.7, 1.2);

// Points for the outer blob.
pair a2 = (3.0, 0.0);
pair b2 = (2.5, 0.4);
pair c2 = (2.0, 1.2);
pair d2 = (2.6, 2.1);
pair e2 = (4.2, 2.4);
pair f2 = (4.5, 2.0);
pair g2 = (4.0, 1.0);
pair h2 = (3.7, 0.4);

// Nodes labelling the domain and co-domain.
pair I = (0.0, 1.0);


label("$[0,1]$", I, fontsize(fsize));
label("$Y$", (4.0, 1.9), fontsize(fsize));

// Draw upper curve.
g = (a0){dir(15)}..(b0){dir(45)}..(c0){dir(50)}..(d0){dir(10)}..(e0){dir(45)};
draw(g, cpen);


// Draw lower curve.
g = (a1){dir(0)}..(b1){dir(-10)}..(c1){dir(-10)}..(d1){dir(80)}..(e1){dir(20)};
draw(g, cpen);

// Draw curve defining the blob.
g = a2{dir(170)}..(b2){dir(135)}..(c2){dir(95)}..(d2){dir(30)}..
    e2{dir(-30)}..(f2){dir(-80)}..(g2){dir(-120)}..(h2){dir(-120)}..cycle;

draw(g, cpen);

// Adjust font size.
real fsize = 8pt;

// Draw curves representing maps f and g.
g = I..{dir(-40)}c0;
L = Label("$f$", fontsize(fsize));
draw(L, g, N, SharpArrow(StealthHead, arsize), margins);

g = I..{dir(40)}c1;
L = Label("$g$", fontsize(fsize));
draw(L, g, S, SharpArrow(StealthHead, arsize), margins);

// Adjust arrow head size.
arsize = 4bp;

// Draw dashed lines connecting curves.
draw(a0--a1, dpen, SharpArrows(StealthHead, arsize));
draw(b0--b1, dpen, SharpArrows(StealthHead, arsize));
draw(c0--c1, dpen, SharpArrows(StealthHead, arsize));
draw(d0--d1, dpen, SharpArrows(StealthHead, arsize));
draw(e0--e1, dpen, SharpArrows(StealthHead, arsize));

filldraw(circle(midpoint(c0, c1), 0.2), white, nullpen);
label("$H$", midpoint(c0, c1), fontsize(fsize));