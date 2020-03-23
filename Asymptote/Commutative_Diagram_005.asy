// Boilerplate stuff.
import settings;
settings.outformat="pdf";
settings.render=4;

// Pen used to label functions.
pen fpen = fontsize(9pt);

size(400);

// Arrow size and coordinates for points.
real arsize = 3bp;
pair M  = (0.0,  0.0);
pair BO = (1.0, -1.0);
pair BG = (1.0,  0.0);
pair GO = (1.0,  1.0);

// Margin to prevent overlap between arrows and labels.
margin marg = TrueMargin(0.4cm, 0.4cm);

// Draw the arrows.
draw("$\varphi$",         M --BG, arrow=Arrow(arsize), N,  margin=marg, fpen);
draw("$\tilde{\varphi}$", M --BO, arrow=Arrow(arsize), SW, margin=marg, fpen);
draw("$f$",               BG--BO, arrow=Arrow(arsize), E,  margin=marg, fpen);

// Label points.
label("$M$",  M);
label("$BO$", BO);
label("$BG$", BG);

// Shift the labels by 2.
M  = shift(2.0, 0.0)*M;
BO = shift(2.0, 0.0)*BO;
BG = shift(2.0, 0.0)*BG;
GO = shift(2.0, 0.0)*GO;

// Draw arrows.
draw("$?$",               M --BG, arrow=Arrow(arsize), N,  margin=marg, fpen);
draw("$\tilde{\varphi}$", M --BO, arrow=Arrow(arsize), SW, margin=marg, fpen);
draw("$f$",               BG--BO, arrow=Arrow(arsize), E,  margin=marg, fpen);

// Label coordinates.
label("$M$",  M);
label("$BO$", BO);
label("$BG$", BG);

// Shift the labels right by 2 and down by 0.5.
M  = shift(2.0, -0.5)*M;
BO = shift(2.0, -0.5)*BO;
BG = shift(2.0, -0.5)*BG;
GO = shift(2.0, -0.5)*GO;

// Draw the arrows.
draw("$f_{1}$", M   -- GO, arrow=Arrow(arsize), NW, margin=marg, fpen);
draw("$f_{2}$", M   -- BG, arrow=Arrow(arsize), S,  margin=marg, fpen);
draw("$f_{3}$", M   -- BO, arrow=Arrow(arsize), SW, margin=marg, fpen);
draw("$g_{1}$", GO  -- BG, arrow=Arrow(arsize), E,  margin=marg, fpen);
draw("$g_{2}$", BG  -- BO, arrow=Arrow(arsize), E,  margin=marg, fpen);

// Label the labels.
label("$M$",   M);
label("$BO$",  BO);
label("$BG$",  BG);
label("$G/O$", GO);