// Settings and output format.
import settings;

// Make sure _custom_arrows.asy is in your $PATH.
// This file is found in the asymptote/ folder of this project.
import _custom_arrows;
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
margin margins = TrueMargin(0.4cm, 0.4cm);

// Draw the arrows.
draw("$f$",         A--B, N,  fpen, SharpArrow(arsize), margins);
draw("$\pi$",       A--C, W,  fpen, SharpArrow(arsize), margins);
draw("$\tilde{f}$", C--B, SE, fpen, SharpArrow(arsize), margins);

// Add labels.
label("$A$", A);
label("$B$", B);
label("$C$", C);
