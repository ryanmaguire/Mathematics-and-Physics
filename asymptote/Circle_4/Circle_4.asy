// Seting output format to "pdf".
import settings;
import graph;

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

pen cpen = deepblue;

pair MidPoint(pair A, pair B){return scale(0.5)*(A+B);}
real norm(pair A){return sqrt(A.x^2+A.y^2);}

pair FindCenter(pair A, pair B, pair C){
    pair U = MidPoint(A, B);
    pair V = MidPoint(B, C);

    real a =  (B.y-A.y)/(B.y-A.y+B.x-A.x);
    real b = -(B.x-A.x)/(B.y-A.y+B.x-A.x);
    real c =  (C.y-B.y)/(C.y-B.y+C.x-B.x);
    real d = -(C.x-B.x)/(C.y-B.y+C.x-B.x);
    real t0 = (c*(V.y-U.y)-d*(V.x-U.x))/(b*c-a*d);
    real t1 = (a*(V.y-U.y)-b*(V.x-U.x))/(b*c-a*d);
    return (U.x+t0*a, U.y+t0*b);
}

pair X0 = (-1.0, 0.0);
pair Y0 = ( 0.0, 1.0);
pair Z0 = ( 0.1, 0.0);

pair P = FindCenter(X0, Y0, Z0);

real R = norm(P-X0);
draw(circle(P, R), cpen);
dot(X0);
dot(Y0);
dot(Z0);

draw((-1.2, 0.0)--(0.2, 0.0));
draw((0.0, -0.2)--(0.0, 1.2));

filldraw(X0--Y0--Z0--cycle, red+opacity(0.5));
label("$-1$", (-1.02, -0.1));
label("$1$", ( 0.1,  1.0));
