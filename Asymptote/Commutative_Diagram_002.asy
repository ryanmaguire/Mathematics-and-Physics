// Settings for the figure.
import settings;
settings.outformat="pdf";
settings.render=4;

// Output size.
size(100);

// Pen used to label functions.
pen fpen = fontsize(9pt);

// Mark coordinates for the points, and specify the arrow size.
real arsize = 5bp;
pair A = (0.0,  0.0);
pair B = (0.0, -1.0);
pair C = (0.0, -2.0);
pair D = (1.0, -1.0);

// Margin for the arrows to prevent overlap with labels.
margin ArrowMargins = TrueMargin(0.4cm, 0.4cm);

// Draw the arrows.
draw("$f_{1}$", A -- D, arrow=Arrow(arsize), NE,  margin=ArrowMargins, fpen);
draw("$f_{2}$", B -- D, arrow=Arrow(arsize), S,   margin=ArrowMargins, fpen);
draw("$f_{3}$", C -- D, arrow=Arrow(arsize), SE,  margin=ArrowMargins, fpen);
draw("$g_{1}$", A -- B, arrow=Arrow(arsize), W,   margin=ArrowMargins, fpen);
draw("$g_{1}$", B -- C, arrow=Arrow(arsize), W,   margin=ArrowMargins, fpen);

// Label the points.
label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);