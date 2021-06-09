// Seting output format to "pdf".
import settings;
texpreamble("\usepackage{amssymb}");

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
pen dpen = fpen+linetype("4 4");

// Set arrow size, and mark three points for A, B, and C.
real arsize = 5bp;
pair A = (0.0,  0.0);
pair B = (1.0,  0.5);
pair C = (1.0, -0.5);

// Margins for the arrows to prevent overlap with labels.
margin margins = TrueMargin(0.3cm, 0.3cm);

// Draw the arrows.
draw("$\alpha$", A--B, NW,  fpen, SharpArrow(arsize), margins);
draw("$\tilde{f}$", B--C, E, dpen, SharpArrow(arsize), margins);
draw("$f$", A--C, SW,  fpen, SharpArrow(arsize), margins);

// Label the points.
label("$X$", A);
label("$\mathcal{X}$", B);
label("$Y$", C);