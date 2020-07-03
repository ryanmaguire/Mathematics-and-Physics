// Boilerplate stuff.
import settings;
import graph;

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
size(256);

real start = -0.2;
real end   =  1.3;

int samples = 3;

real rdot = 0.05;
real angle_length = 0.2;

pair A = (0.0, 1.0);
pair B = (0.0, 0.0);
pair C = (4.0, 0.2);

real rel_angle(pair O, pair X, pair Y){
    pair P = X-O;
    pair Q = Y-O;
    real dot_prod = P.x*Q.x+P.y*Q.y;
    real abs_prod = abs(P)*abs(Q);
    return acos(dot_prod/abs_prod);
}

real angle1 = rel_angle(A, B, C);
real angle2 = rel_angle(B, A, C);

pair f1(real t){return scale(1-t)*A+scale(t)*C;}
pair f2(real t){return scale(1-t)*B+scale(t)*C;}

path g=graph(f1, start, end, n=samples);
draw(g);
path g=graph(f2, start, end, n=samples);
draw(g);

draw(A--B);

draw(arc(A, angle_length, 270, 270+180*angle1/pi));
draw(arc(B, angle_length, 90,  90-180*angle2/pi));

filldraw(circle(A, rdot));
filldraw(circle(B, rdot));
filldraw(circle(C, rdot));
label("$A$", A, NE);
label("$B$", B, SE);
label("$C$", C, N);