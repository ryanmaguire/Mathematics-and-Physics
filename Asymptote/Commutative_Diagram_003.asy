import graph;
import settings;
outformat="pdf";
settings.render=4;

size(100, 100);

real arsize = 5bp;
pair A = (0.0,  0.0);
pair B = (2.0,  0.0);
pair C = (0.0, -2.0);
pair D = (2.0, -2.0);

margin ArrowMargins = TrueMargin(0.4cm, 0.4cm);

draw("$\alpha$", A -- B, arrow=Arrow(arsize), N,  margin=ArrowMargins);
draw("$\beta$",  B -- D, arrow=Arrow(arsize), E,  margin=ArrowMargins);
draw("$\gamma$", A -- C, arrow=Arrow(arsize), W,  margin=ArrowMargins);
draw("$\delta$", C -- D, arrow=Arrow(arsize), S,  margin=ArrowMargins);

label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);