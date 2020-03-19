import graph;
import settings;
outformat="pdf";
settings.render=4;

size(600, 100);

real arsize = 5bp;
pair M  = (0.0,  0.0);
pair BO = (1.0, -1.0);
pair BG = (1.0,  0.0);

margin ArrowMargins = TrueMargin(0.4cm, 0.4cm);

draw("$\varphi$",         M --BG, arrow=Arrow(arsize), N,  margin=ArrowMargins);
draw("$\tilde{\varphi}$", M --BO, arrow=Arrow(arsize), SW, margin=ArrowMargins);
draw("$f$",               BG--BO, arrow=Arrow(arsize), E,  margin=ArrowMargins);

label("$M$",  M);
label("$BO$", BO);
label("$BG$", BG);

M  = (2.0,  0.0);
BO = (3.0, -1.0);
BG = (3.0,  0.0);

draw("$?$",               M --BG, arrow=Arrow(arsize), N,  margin=ArrowMargins);
draw("$\tilde{\varphi}$", M --BO, arrow=Arrow(arsize), SW, margin=ArrowMargins);
draw("$f$",               BG--BO, arrow=Arrow(arsize), E,  margin=ArrowMargins);

label("$M$",  M);
label("$BO$", BO);
label("$BG$", BG);

M  = (4.0, -0.5);
BO = (5.0, -1.5);
BG = (5.0, -0.5);
pair GO = (5.0, 0.5);

draw("$f_{1}$", M   -- GO, arrow=Arrow(arsize), NW,  margin=ArrowMargins);
draw("$f_{2}$", M   -- BG, arrow=Arrow(arsize), S,   margin=ArrowMargins);
draw("$f_{3}$", M   -- BO, arrow=Arrow(arsize), SW,  margin=ArrowMargins);
draw("$g_{1}$", GO  -- BG, arrow=Arrow(arsize), E,   margin=ArrowMargins);
draw("$g_{2}$", BG  -- BO, arrow=Arrow(arsize), E,   margin=ArrowMargins);

label("$M$",   M);
label("$BO$",  BO);
label("$BG$",  BG);
label("$G/O$", GO);