// Settings and output format.
import settings;
import _custom_arrows;
settings.outformat="pdf";
settings.render=4;

// Size of the output.
size(100);

// Pen used to label functions.
pen fpen = fontsize(9pt);

// Arrow size and coordinates for labels.
real ar = 5bp;
pair A = (0.0,  0.0);
pair B = (1.0,  0.0);
pair C = (0.0, -1.0);

// Margins for the arrows to prevent overlap with labels.
real marg = 0.4cm;

// Draw the arrows.
sharp_arrow("$f$",         A--B, N,  arsize=ar, mstart=marg, mend=marg, fpen);
sharp_arrow("$\pi$",       A--C, W,  arsize=ar, mstart=marg, mend=marg, fpen);
sharp_arrow("$\tilde{f}$", C--B, SE, arsize=ar, mstart=marg, mend=marg, fpen);

// Add labels.
label("$A$", A);
label("$B$", B);
label("$C$", C);