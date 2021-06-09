// Seting output format to "pdf".
import settings;
import _custom_arrows;

if(settings.render < 0)    settings.render    = 4;
if(!settings.multipleView) settings.batchView = false;

settings.render      = 8;
settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Size of the output.
size(128);

// Pen for drawing.
pen dpen = black+linewidth(0.8pt);

// Font size for labels.
real fsize = 8pt;

// Some lengths.
real xlength = 4.0;
real ylength = 3.0;
real d       = 1.0;
real dx      = 0.3;
real rx      = 0.2;
real ry      = 0.3;

draw((0.0, ylength)--(0.0, 0.0)--(xlength, 0.0), dpen);
draw((d,   ylength)--(d,   0.0), dpen);

draw(ellipse((-dx, 0.5*ylength), rx, ry), dpen);
draw(ellipse((dx, 0.5*ylength), rx, ry),  dpen);
draw((-dx, 0.5*ylength+ry)--(dx, 0.5*ylength+ry), dpen);
draw((-dx, 0.5*ylength-ry)--(dx, 0.5*ylength-ry), dpen);

label("$x$", (xlength, 0.0), SW, fontsize(fsize));
label("$\Delta{a}$", (dx, 0.5*ylength), fontsize(fsize));
label("$d$", (0.5*d, 0.0), N, fontsize(fsize));
label("$\kappa_{e}$", (0.5*d, ylength), S, fontsize(fsize));

label("$\mathrm{Area}=A$", (0.5*xlength, 0.5*ylength), fontsize(fsize));