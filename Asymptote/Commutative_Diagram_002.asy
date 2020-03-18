import graph;
import settings;
outformat="pdf";
settings.render=4;

size(100, 135);

pair A = (0.0,  0.0);
pair B = (0.0, -1.0);
pair C = (0.0, -2.0);
pair D = (1.0, -1.0);

margin ArrowMargins = TrueMargin(0.4cm, 0.4cm);

draw("$f_{1}$", A -- D, arrow=Arrow(), NE,  margin=ArrowMargins);
draw("$f_{2}$", B -- D, arrow=Arrow(), S,   margin=ArrowMargins);
draw("$f_{3}$", C -- D, arrow=Arrow(), SE,  margin=ArrowMargins);
draw("$g_{1}$", A -- B, arrow=Arrow(), W,   margin=ArrowMargins);
draw("$g_{1}$", B -- C, arrow=Arrow(), W,   margin=ArrowMargins);

label("$A$", A);
label("$B$", B);
label("$C$", C);
label("$D$", D);