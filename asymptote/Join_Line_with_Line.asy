// Seting output format to "pdf".
import settings;
import _mimic_three;
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
size(256);

// Solid pen and dashed pen.
pen spen = black+linewidth(0.4);
pen dpen = spen+linetype("4 4");

real arsize = 4bp;
path g;

g = xyzpoint(0.7, 0, 0).R--xyzpoint(0.7, 1, 0).R--
    xyzpoint(0.7, 1, 1).R--xyzpoint(0.7, 0, 1).R--cycle;
filldraw(g, gray(0.7)+opacity(0.5));

g = xyzpoint(0,   0, 0).R--xyzpoint(0.7, 0, 0).R--
    xyzpoint(0.7, 0, 1).R--xyzpoint(0,   0, 1).R--cycle;
filldraw(g, gray(0.3)+opacity(0.5));

g = xyzpoint(0.7, 0, 1).R--xyzpoint(0.7, 1, 1).R--
    xyzpoint(0,   1, 1).R--xyzpoint(0,   0, 1).R--cycle;
filldraw(g, gray(0.5)+opacity(0.5));


pair A = shift(3.0, 0.3)*(0, 0.3);
pair B = shift(3.0, 0.3)*(0.25, -0.3);
pair C = shift(3.0, 0.3)*(2.0, 0.8);
pair D = shift(3.0, 0.3)*(2.0, -0.8);

draw(A--D, dpen);
filldraw(A--B--C--cycle, gray(0.5)+opacity(0.5), spen);
filldraw(B--C--D--cycle, gray(0.6)+opacity(0.5), spen);
draw(A--B, spen+blue);
draw(C--D, spen+red);

draw((1.8, 0.3)--(2.6, 0.3), SharpArrow(arsize));

label("$X\times{Y}\times{I}$", (-0.3, 1.3), fontsize(9pt));
label("$X*{Y}$", (4.3, 1.3), fontsize(9pt));