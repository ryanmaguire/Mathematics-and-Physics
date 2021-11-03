// Seting output format to "pdf".
import settings;
import graph;
import custom_arrows;
settings.outformat = "pdf";

defaultpen(black+linewidth(0.4pt)+fontsize(7pt));

// Size of the output figure.
size(128);

real arsize = 4bp;

pair O1 = (0.0, 1.0);
pair O2 = (1.0, 1.0);
pair A1 = (0.0, 2.0);
pair A2 = (1.0, 2.0);
pair B1 = (0.0, 0.0);
pair B2 = (1.0, 0.0);

draw("$a$", O1--A1, MidSharpArrow(arsize));
draw("$a$", O2--A2, MidSharpArrow(arsize));
draw("$b$", A1--A2, MidSharpArrow(arsize));
draw("$b$", O1--O2, MidSharpArrow(arsize));
draw("$b$", B1--B2, MidSharpArrow(arsize));
draw("$c$", O1--B1, MidSharpArrow(arsize));
draw("$c$", O2--B2, MidSharpArrow(arsize));