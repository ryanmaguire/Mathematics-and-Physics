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
size(128);

// Default pen used for labels.
defaultpen(fontsize(9pt));

// Pen used to label functions.
pen fpen = fontsize(7pt);

// Mark coordinates for the points, and specify the arrow size.
real arsize = 5bp;
pair A = (0.0,  0.0);
pair B = (0.0, -1.0);
pair C = (0.0, -2.0);
pair D = (1.0, -1.0);

// Margins for the arrows to prevent overlap with labels.
margin margins = TrueMargin(0.4cm, 0.4cm);

// Draw the arrows.
draw("$f_{1}$", A--D, 2*NE, fpen, SharpArrow(arsize), margins);
draw("$f_{2}$", B--D, 2*S,  fpen, SharpArrow(arsize), margins);
draw("$f_{3}$", C--D, 2*SE, fpen, SharpArrow(arsize), margins);
draw("$g_{1}$", A--B, 2*W,  fpen, SharpArrow(arsize), margins);
draw("$g_{2}$", B--C, 2*W,  fpen, SharpArrow(arsize), margins);

// Label the points.
label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);
