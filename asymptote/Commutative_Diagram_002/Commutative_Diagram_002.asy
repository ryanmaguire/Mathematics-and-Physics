// Settings for the figure.
import settings;

// Make sure _custom_arrows.asy is in your $PATH.
// This file is found in the asymptote/ folder of this project.
import _custom_arrows;
settings.outformat = "pdf";
settings.render = 4;
settings.prc = false;

// Output size.
size(100, 200);

// Pen used to label functions.
pen fpen = fontsize(9pt);

// Mark coordinates for the points, and specify the arrow size.
real arsize = 5bp;
pair A = (0.0,  0.0);
pair B = (0.0, -1.0);
pair C = (0.0, -2.0);
pair D = (1.0, -1.0);

// Margins for the arrows to prevent overlap with labels.
margin margins = TrueMargin(0.4cm, 0.4cm);

// Draw the arrows.
draw("$f_{1}$", A--D, NE, fpen, SharpArrow(arsize), margins);
draw("$f_{2}$", B--D, S,  fpen, SharpArrow(arsize), margins);
draw("$f_{3}$", C--D, SE, fpen, SharpArrow(arsize), margins);
draw("$g_{1}$", A--B, W,  fpen, SharpArrow(arsize), margins);
draw("$g_{2}$", B--C, W,  fpen, SharpArrow(arsize), margins);

// Label the points.
label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);
