// Settings for the figure.
import settings;
import _custom_arrows;
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
real marg = 0.4cm;

// Draw the arrows.
sharp_arrow("$f_{1}$", A--D, NE, arsize=arsize, mstart=marg, mend=marg, fpen);
sharp_arrow("$f_{2}$", B--D, S,  arsize=arsize, mstart=marg, mend=marg, fpen);
sharp_arrow("$f_{3}$", C--D, SE, arsize=arsize, mstart=marg, mend=marg, fpen);
sharp_arrow("$g_{1}$", A--B, W,  arsize=arsize, mstart=marg, mend=marg, fpen);
sharp_arrow("$g_{2}$", B--C, W,  arsize=arsize, mstart=marg, mend=marg, fpen);

// Label the points.
label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);