import graph;
import settings;
outformat="pdf";
settings.render=4;

size(100, 100);

pair A = (0.0,  0.0);
pair B = (2.0,  0.0);
pair C = (0.0, -2.0);
pair D = (2.0, -2.0);

margin ArrowMargins = TrueMargin(0.4cm, 0.4cm);

draw("$\alpha$", A -- B, arrow=Arrow(), N,  margin=ArrowMargins);
draw("$\beta$",  B -- D, arrow=Arrow(), E,  margin=ArrowMargins);
draw("$\gamma$", A -- C, arrow=Arrow(), W,  margin=ArrowMargins);
draw("$\delta$", C -- D, arrow=Arrow(), S,  margin=ArrowMargins);

label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);