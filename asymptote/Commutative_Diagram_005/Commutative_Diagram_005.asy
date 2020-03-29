// Boilerplate stuff.
import settings;

// Make sure _custom_arrows.asy is in your $PATH.
// This file is found in the asymptote/ folder of this project.
import _custom_arrows;
settings.outformat="pdf";
settings.render=4;

// Size of the output.
size(400);

// Pen used to label functions.
pen fpen = fontsize(9pt);

// Arrow size and coordinates for points.
real arsize = 5bp;
pair M  = (0.0,  0.0);
pair BO = (1.0, -1.0);
pair BG = (1.0,  0.0);
pair GO = (1.0,  1.0);

// Margins for the arrows to prevent overlap with labels.
margin margins = TrueMargin(0.4cm, 0.4cm);

// Draw the arrows.
draw("$f$",               BG--BO, E,  fpen, SharpArrow(arsize), margins);
draw("$\varphi$",         M --BG, N,  fpen, SharpArrow(arsize), margins);
draw("$\tilde{\varphi}$", M --BO, SW, fpen, SharpArrow(arsize), margins);

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
draw("$f$",               BG--BO, E,  fpen, SharpArrow(arsize), margins);
draw("$?$",               M --BG, N,  fpen, SharpArrow(arsize), margins);
draw("$\tilde{\varphi}$", M --BO, SW, fpen, SharpArrow(arsize), margins);

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
draw("$f_{1}$", M --GO, NW, fpen, SharpArrow(arsize), margins);
draw("$f_{2}$", M --BG, S,  fpen, SharpArrow(arsize), margins);
draw("$f_{3}$", M --BO, SW, fpen, SharpArrow(arsize), margins);
draw("$g_{1}$", GO--BG, E,  fpen, SharpArrow(arsize), margins);
draw("$g_{2}$", BG--BO, E,  fpen, SharpArrow(arsize), margins);

// Label the labels.
label("$M$",   M);
label("$BO$",  BO);
label("$BG$",  BG);
label("$G/O$", GO);
