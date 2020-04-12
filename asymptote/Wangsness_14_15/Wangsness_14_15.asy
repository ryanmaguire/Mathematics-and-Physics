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

pen lpen = linewidth(0.5pt)+deepblue;

real R1 = 1.0;
real dx = 0.5;
real R2 = R1+dx;
real arsize  = 5bp;
real barsize = 3bp;
real fsize   = 6pt;
Label L;

margin margins = TrueMargin(0.0, 0.02cm);

real theta  = 45;
real dtheta = 3;
real dl     = 0.06;

pair O = (0.0, 0.0);

draw("I", arc(O, R1, 0, 180),      N, MidSharpArrow(arsize));
draw("II", (-R1, 0.0)--(-R2, 0.0), S, MidSharpArrow(arsize));
draw("III", arc(O, R2, 180, 0), N,    MidSharpArrow(arsize));
draw("IV", (R2, 0.0)--(R1, 0.0), S,   MidSharpArrow(arsize));

draw("$a$", O--scale(R1)*expi(3pi/4), NE, lpen);
draw("$b$", O--scale(R2)*expi(6pi/7), S,  lpen);
draw("$\mathbf{R}$", O--scale(R1)*expi(pi*theta/180), NW);

L = Label("$\textrm{d}\ell$", fontsize(fsize));
draw(L, arc(O, R1+dl, theta-dtheta, theta+dtheta), NE, bar=Bars(barsize));

pair arrowend1 = scale(R1+dl)*expi(pi*(theta-dtheta)/180);
pair arrowend2 = scale(R1+dl)*expi(pi*(theta+dtheta)/180);
path arrow1 = ((scale(2)*arrowend1)-arrowend2)--arrowend1;
path arrow2 = ((scale(2)*arrowend2)-arrowend1)--arrowend2;
draw(arrow1, SharpArrow(), margins);
draw(arrow2, SharpArrow(), margins);

filldraw(circle(O, 0.02), black, black);
label("$q$", O, SE);
label("$I'$", scale(R2+dl)*expi(pi/4), NE);