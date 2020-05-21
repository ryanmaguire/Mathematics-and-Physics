// Seting output format to "pdf".
import settings;
import _euc_geo;
import _custom_arrows;
texpreamble("\usepackage{amssymb}");

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

// Solid pen and dashed pen.
pen spen = black+linewidth(0.4);
pen dpen = spen+linetype("4 4");

real r = 1;
real rdot = 0.03;
real e = 0.4;
real fsize = 9pt;
pair O = (0, 0);

draw(scale(1, e)*arc(O, r, 0, 180), dpen);
filldraw(circle(O, r), gray(0.5)+opacity(0.5), spen);
draw(scale(1, e)*arc(O, r, 180, 360), spen);
draw(circle(shift(-2*r)*O, r), spen);
filldraw(circle(shift(-r, 0)*O, rdot), black);
