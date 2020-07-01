// Boilerplate stuff.
import settings;

if(!settings.multipleView)  settings.batchView=false;

settings.render=8;
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
settings.prc=false;
viewportmargin=(2, 2);

pair midpoint(pair A, pair B){return scale(0.5)*(A+B);}

// Default pen for drawing.
defaultpen(black+linewidth(0.4pt));
fontsize(7pt);

// Size of the output figure.
size(128);

real radius = 2.0;
real dotr   = 0.05;
pair A = (0, 0.0);
pair B = (radius, 0.0);
pair C = (0.5*radius, sqrt(1.5*radius));

draw(circle(A, radius));
draw(circle(B, radius));
filldraw(A--B--C--cycle, green);

filldraw(circle(A, dotr), black);
filldraw(circle(B, dotr), black);
filldraw(circle(C, dotr), black);
label("$A$", A, SW);
label("$B$", B, SE);
label("$C$", C, N);