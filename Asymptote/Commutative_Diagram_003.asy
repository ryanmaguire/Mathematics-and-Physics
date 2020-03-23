// Boilerplate stuff.
import settings;
settings.outformat="pdf";
settings.render=4;

// Size of the output
size(100);

// Pen used to label functions.
pen fpen = fontsize(9pt);

// Size of the arrows, and coordinates for the labels.
real arsize = 5bp;
pair A = (0.0,  0.0);
pair B = (2.0,  0.0);
pair C = (0.0, -2.0);
pair D = (2.0, -2.0);

// Margins for the arrows to prevent overlap with labels.
margin ArrowMargins = TrueMargin(0.4cm, 0.4cm);

// Draw the arrows.
draw("$\alpha$", A -- B, arrow=Arrow(arsize), N,  margin=ArrowMargins, fpen);
draw("$\beta$",  B -- D, arrow=Arrow(arsize), E,  margin=ArrowMargins, fpen);
draw("$\gamma$", A -- C, arrow=Arrow(arsize), W,  margin=ArrowMargins, fpen);
draw("$\delta$", C -- D, arrow=Arrow(arsize), S,  margin=ArrowMargins, fpen);

// Label the points.
label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);