// Settings and output format.
import settings;
settings.outformat="pdf";
settings.render=4;

// Size of the output.
size(100);

// Pen used to label functions.
pen fpen = fontsize(9pt);

// Arrow size and coordinates for labels.
real arsize = 5bp;
pair A = (0.0,  0.0);
pair B = (1.0,  0.0);
pair C = (0.0, -1.0);

// Margins for the arrows to prevent overlap with labels.
margin ArrowMargins = TrueMargin(0.4cm, 0.4cm);

// Draw the arrows.
draw("$f$",         A -- B, arrow=Arrow(arsize), N,  margin=ArrowMargins, fpen);
draw("$\pi$",       A -- C, arrow=Arrow(arsize), W,  margin=ArrowMargins, fpen);
draw("$\tilde{f}$", C -- B, arrow=Arrow(arsize), SE, margin=ArrowMargins, fpen);

// Add labels.
label("$A$", A);
label("$B$", B);
label("$C$", C);