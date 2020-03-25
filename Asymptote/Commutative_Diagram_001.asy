// Seting output format to "pdf".
import settings;
import _custom_arrows;
settings.outformat="pdf";
settings.render=4;

// Pen used to label functions.
pen fpen = fontsize(9pt);

// Size of the output figure.
size(100);

// Set arrow size, and mark three points for A, B, and C.
real arsize = 5bp;
pair A = (0.0,  0.0);
pair B = (0.0, -1.0);
pair C = (1.0,  0.0);

// Shrink the start and end points of the arrows.
real armarge = 0.4cm;

// Draw the arrows.
sharp_arrow("$f$", A--B, arsize=arsize, mstart=armarge, mend=armarge, fpen);
sharp_arrow("$g$", B--C, arsize=arsize, mstart=armarge, mend=armarge, fpen);
sharp_arrow("$h$", A--C, arsize=arsize, mstart=armarge, mend=armarge, fpen);

// Label the points.
label("$A$", A);
label("$B$", B);
label("$C$", C);