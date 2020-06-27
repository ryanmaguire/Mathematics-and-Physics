// Seting output format to "pdf".
import settings;

if(settings.render < 0)    settings.render    = 8;
if(!settings.multipleView) settings.batchView = false;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Size of the output figure.
size(128);

// Default pen used for labels.
defaultpen(black+fontsize(9pt));
pen angle_pen = black+fontsize(7pt);

real x = 1.5;
real y = 1.0;
real scale_factor = 1.1;
real r = 0.02;
real square_r = 0.1;

path g;

pair A = (0.0, 0.0);
pair B = (x, 0.0);
pair C = scale(scale_factor)*(x, y);
pair D = (0.0, y);

g = A--B{N}..{(0.3,1)}C{(-1,-0.3)}..{W}D--cycle;
draw(g);

filldraw(circle(A, r));
filldraw(circle(B, r));
filldraw(circle(C, r));
filldraw(circle(D, r));

g = (A+(square_r, 0.0))--(A+(square_r, square_r))--(A+(0.0, square_r));
draw(g, angle_pen);

g = (B+(-square_r, 0.0))--(B+(-square_r, square_r))--(B+(0.0, square_r));
draw(g, angle_pen);

g = (D+(square_r, 0.0))--(D+(square_r, -square_r))--(D+(0.0, -square_r));
draw(g, angle_pen);