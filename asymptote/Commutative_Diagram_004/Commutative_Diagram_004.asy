// Seting output format to "pdf".
import settings;

// Make sure _custom_arrows.asy is in your $PATH.
// This file is found in the asymptote/ folder of this project.
import _custom_arrows;

if(settings.render < 0)    settings.render    = 8;
if(!settings.multipleView) settings.batchView = false;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Size of the output figure.
size(64);

// Default pen used for labels.
defaultpen(fontsize(9pt));

// Pen used to label functions.
pen fpen = fontsize(7pt);

// Arrow size and coordinates for labels.
real arsize = 5bp;
pair A = (0.0,  0.0);
pair B = (1.0,  0.0);
pair C = (0.0, -1.0);

// Margins for the arrows to prevent overlap with labels.
margin margins = TrueMargin(0.3cm, 0.3cm);

// Draw the arrows.
draw("$f$",         A--B, 2*N,  fpen, SharpArrow(arsize), margins);
draw("$\pi$",       A--C, 2*W,  fpen, SharpArrow(arsize), margins);
draw("$\tilde{f}$", C--B, 2*SE, fpen, SharpArrow(arsize), margins);

// Add labels.
label("$A$", A);
label("$B$", B);
label("$C$", C);
