// Seting output format to "pdf".
import settings;
import "../_custom_arrows.asy" as _custom_arrows;
settings.outformat="pdf";
settings.render=4;
settings.prc = false;

// Pen used to label functions.
pen fpen = fontsize(8pt);

// Size of the output figure.
size(100);

// Set arrow size, and mark three points for A, B, and C.
real arsize = 5bp;
pair A = (0.0,  0.0);
pair B = (0.0, -1.0);
pair C = (1.0,  0.0);

// Margins for the arrows to prevent overlap with labels.
margin margins = TrueMargin(0.4cm, 0.4cm);

// Draw the arrows.
draw("$f$", A--B, W,  fpen, SharpArrow(arsize), margins);
draw("$g$", B--C, SE, fpen, SharpArrow(arsize), margins);
draw("$h$", A--C, N,  fpen, SharpArrow(arsize), margins);

// Label the points.
label("$A$", A, fontsize(10pt));
label("$B$", B, fontsize(10pt));
label("$C$", C, fontsize(10pt));
