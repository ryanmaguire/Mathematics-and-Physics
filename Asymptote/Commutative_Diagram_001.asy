// Seting output format to "pdf".
import settings;
settings.outformat="pdf";
settings.render=4;

// Pen used to label functions.
pen fpen = fontsize(9pt);

// Size of the output figure.
size(100);

// Set arrow size, and mark three points for A, B, and C.
real arsize = 5bp;
pair A = (0.0,  0.0);
pair B = (0.0, -1.0);
pair C = (1.0,  0.0);

// Shrink the start and end points of the arrows.
margin ArrowMargins = TrueMargin(0.4cm, 0.4cm);

// Draw the arrows.
draw("$f$", A -- B, arrow=Arrow(arsize), W,  margin=ArrowMargins, fpen);
draw("$h$", A -- C, arrow=Arrow(arsize), N,  margin=ArrowMargins, fpen);
draw("$g$", B -- C, arrow=Arrow(arsize), SE, margin=ArrowMargins, fpen);

// Label the points.
label("$A$", A);
label("$B$", B);
label("$C$", C);