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
pen fpen = fontsize(8pt);

// Set arrow size, and mark three points for A, B, and C.
real arsize = 5bp;
pair A = (0.0,  0.0);
pair B = (0.0, -1.0);
pair C = (1.0,  0.0);

// Margins for the arrows to prevent overlap with labels.
margin margins = TrueMargin(0.3cm, 0.3cm);

// Draw the arrows.
draw("$f$", A--B, 2*W,  fpen, SharpArrow(arsize), margins);
draw("$g$", B--C, 2*SE, fpen, SharpArrow(arsize), margins);
draw("$h$", A--C, 2*N,  fpen, SharpArrow(arsize), margins);

// Label the points.
label("$A$", A);
label("$B$", B);
label("$C$", C);
