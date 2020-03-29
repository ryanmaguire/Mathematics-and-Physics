// Boilerplate stuff.
import settings;

// Make sure _custom_arrows.asy is in your $PATH.
// This file is found in the asymptote/ folder of this project.
import _custom_arrows;
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
margin margins = TrueMargin(0.4cm, 0.4cm);

// Draw the arrows.
draw("$\alpha$", A--B, N, fpen, SharpArrow(arsize), margins);
draw("$\beta$",  B--D, E, fpen, SharpArrow(arsize), margins);
draw("$\gamma$", A--C, W, fpen, SharpArrow(arsize), margins);
draw("$\delta$", C--D, S, fpen, SharpArrow(arsize), margins);

// Label the points.
label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);
