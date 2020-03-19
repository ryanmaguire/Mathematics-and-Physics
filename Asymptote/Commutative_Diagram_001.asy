import graph;
import settings;
outformat="pdf";
settings.render=4;

size(100);

real arsize = 5bp;
pair A = (0.0,  0.0);
pair B = (0.0, -1.0);
pair C = (1.0,  0.0);

margin ArrowMargins = TrueMargin(0.4cm, 0.4cm);

draw("$f$", A -- B, arrow=Arrow(arsize), W,  margin=ArrowMargins);
draw("$h$", A -- C, arrow=Arrow(arsize), N,  margin=ArrowMargins);
draw("$g$", B -- C, arrow=Arrow(arsize), SE, margin=ArrowMargins);

label("$A$", A);
label("$B$", B);
label("$C$", C);