// Seting output format to "pdf".
import settings;
import graph;
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

defaultpen(fontsize(7pt));

// Size of the output figure.
size(128);

pen bpen = deepblue;
pen dpen = black;
pen lpen = deepgreen;

real R0 = 0.4;
real R1 = 0.6;
real R2 = 1.2;
real R3 = 1.5;
real fs = 6pt;

real xlength = 2.5;

pair O = (0.0, 0.0);

draw(circle(O, R0), bpen+linetype("4 4"));
draw(circle(O, R1), bpen);
draw(circle(O, R2), dpen);
draw(circle(O, R3), dpen);

draw((0.0,  R3)--(xlength,  R3));
draw((0.0, -R3)--(xlength, -R3));
draw((0.0,  R1)--(sqrt(R2*R2-R1*R1),  R1), bpen);
draw((0.0, -R1)--(sqrt(R2*R2-R1*R1), -R1), bpen);

draw(Label("$a$", position=0.4, fontsize(fs)), O--scale(R1)*expi(pi/4) , lpen);
draw(Label("$b$", position=0.7, fontsize(fs)), O--scale(R2)*expi(5pi/6), lpen);
draw(Label("$c$", position=0.5, fontsize(fs)), O--scale(R3)*expi(8pi/7), lpen);
