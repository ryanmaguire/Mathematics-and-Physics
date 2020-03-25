// Boilerplate stuff.
import settings;
import _custom_arrows;
settings.outformat="pdf";
settings.render=4;

// Pen used to label functions.
pen fpen = fontsize(9pt);

size(400);

// Arrow size and coordinates for points.
real ar =5bp;
pair M  = (0.0,  0.0);
pair BO = (1.0, -1.0);
pair BG = (1.0,  0.0);
pair GO = (1.0,  1.0);

// Margin to prevent overlap between arrows and labels.
real m = 0.5cm;

// Draw the arrows.
sharp_arrow("$f$",               BG--BO, arsize=ar, mstart=m, mend=m, fpen);
sharp_arrow("$\varphi$",         M --BG, arsize=ar, mstart=m, mend=m, fpen);
sharp_arrow("$\tilde{\varphi}$", M --BO, arsize=ar, mstart=m, mend=m, fpen);

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
sharp_arrow("$f$",               BG--BO, arsize=ar, mstart=m, mend=m, fpen);
sharp_arrow("$?$",               M --BG, arsize=ar, mstart=m, mend=m, fpen);
sharp_arrow("$\tilde{\varphi}$", M --BO, arsize=ar, mstart=m, mend=m, fpen);

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
sharp_arrow("$f_{1}$", M --GO, NW, arsize=ar, mstart=m, mend=m, fpen);
sharp_arrow("$f_{2}$", M --BG, S,  arsize=ar, mstart=m, mend=m, fpen);
sharp_arrow("$f_{3}$", M --BO, SW, arsize=ar, mstart=m, mend=m, fpen);
sharp_arrow("$g_{1}$", GO--BG, E,  arsize=ar, mstart=m, mend=m, fpen);
sharp_arrow("$g_{2}$", BG--BO, E,  arsize=ar, mstart=m, mend=m, fpen);

// Label the labels.
label("$M$",   M);
label("$BO$",  BO);
label("$BG$",  BG);
label("$G/O$", GO);