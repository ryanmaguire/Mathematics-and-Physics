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

// Size of the output figure.
size(128);

// Thiner pen.
pen tpen = black+linewidth(0.2);

int i;
int n = 8;

real length = 1.0;
real dx = 2.0*length/n;
real rDot = 0.008;

pair A = (-length, 0.0);
pair B = ( length, 0.0);
pair C = (-0.5*length, -0.5);
pair D = ( 0.5*length, -0.5);
pair O = (0.0, -1.0);

pair point;

draw(A--B);
draw(C--D);

for(i=1; i<n; ++i){
    point = shift((i*dx, 0.0))*A;
    draw(O--point, tpen);
    filldraw(circle(point, rDot));
    point = shift((0.5*i*dx, 0.0))*C;
    filldraw(circle(point, rDot));
}

draw(O--A);
draw(O--B);
filldraw(circle(A, rDot));
filldraw(circle(B, rDot));
filldraw(circle(C, rDot));
filldraw(circle(D, rDot));
filldraw(circle(O, 2*rDot));

label("$O$", O, SE, fontsize(9pt));