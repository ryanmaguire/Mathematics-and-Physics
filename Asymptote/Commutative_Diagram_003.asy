// Boilerplate stuff.
import settings;
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
real smarg = 0.4cm;

// Draw the arrows.
sharp_arrow("$\alpha$", A--B, N, arsize=arsize, mstart=marg, mend=marg, fpen);
sharp_arrow("$\beta$",  B--D, E, arsize=arsize, mstart=marg, mend=marg, fpen);
sharp_arrow("$\gamma$", A--C, W, arsize=arsize, mstart=marg, mend=marg, fpen);
sharp_arrow("$\delta$", C--D, S, arsize=arsize, mstart=marg, mend=marg, fpen);

// Label the points.
label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);