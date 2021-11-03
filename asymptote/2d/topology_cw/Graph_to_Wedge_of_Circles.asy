// Seting output format to "pdf".
import settings;
import custom_arrows;

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

real r = 1.0;
real rdot = 0.03;
real arsize = 4bp;

pair A = scale(r)*expi(pi/2);
pair B = scale(r)*expi(7pi/6);
pair C = scale(r)*expi(11pi/6);
pair O = (0, 0);

draw(A--B--C--cycle);
draw(A--O, blue);
draw(B--O, blue);
draw(C--O, blue);
filldraw(circle(O, rdot), black);
filldraw(circle(A, rdot), black);
filldraw(circle(B, rdot), black);
filldraw(circle(C, rdot), black);

draw((1.2, 0.0)--(1.8, 0.0), SharpArrow(arsize));

r = 0.5;
O = (3.0, 0.0);
A = shift(3.0, 0.0)*(scale(r)*expi(pi/2));;
B = shift(3.0, 0.0)*(scale(r)*expi(7pi/6));;
C = shift(3.0, 0.0)*(scale(r)*expi(11pi/6));;

draw(circle(A, r), black);
draw(circle(B, r), white+2);
draw(circle(B, r), black);
draw(circle(C, r), white+2);
draw(circle(C, r), black);
draw(arc(A, r, 325, 335), white+2);
draw(arc(A, r, 260, 360), black);
draw(arc(B, r, 20, 40), black);
draw(arc(C, r, 110, 130), black);

filldraw(circle(O, rdot), blue, black+linewidth(0.2));
