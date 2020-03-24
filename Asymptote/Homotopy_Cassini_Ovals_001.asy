import CassiniOval;
import settings;
settings.render = 4;
settings.outformat = "pdf";

size(300);

pen cpen = deepblue+linewidth(1pt);
pen dpen = deepblue+linewidth(0.4);

pair A = (-2, 0);
pair B = (+2, 0);
pair AA, BB;

path p;

real r   = 0.5;
real dx  = 0.01;
real EPS = 0.01;
real a   = arclength(A--B)/2.0;
real phi;

AA = (B-(0.1, 0.0));

int i, j;
int n = 16;
int start = 3;
int end   = 10;
int step  = 1;

pair unitnorm(pair Z){
    real r = sqrt(Z.x^2+Z.y^2);
    if (r != 0) return (Z.x/r, Z.y/r);
    else return (0.0, 0.0);
}

real CassiniNorm(pair Z, real a){
    return ((Z.x-a)^2+Z.y^2)*((Z.x+a)^2+Z.y^2);
}

pair f(real x, real y, real a){
    pair out;
    out = (4*x*(x^2+y^2-a^2), 4*y*(x^2+y^2+a^2));
    return unitnorm(out);
}

filldraw(shift(+AA)*scale(r)*unitcircle, blue+opacity(0.4), cpen);
filldraw(shift(-AA)*scale(r)*unitcircle, blue+opacity(0.4), cpen);

for (i=0; i<n; ++i){
    phi = 2*pi*i/n;
    AA = (B-(0.1, 0.0))+r*expi(phi);
    BB = AA;
    p = AA--BB;
    while (CassiniNorm(BB, a) < end^2){
        BB = (AA+scale(dx)*f(AA.x, AA.y, a));
        p = p--BB;
        AA = BB;
        if (sqrt(AA.x^2+AA.y^2) < EPS) break;
    }
    draw(p, dpen);
    draw(reflect(N, S)*p, dpen);
}


CassiniOval co;

co = CassiniOval(A, B, 2*a);
draw(co.curve, cpen+linewidth(2pt));

co = CassiniOval(A, B, end);
draw(co.curve, cpen);

draw((0, sqrt(end-a^2))--(0, -sqrt(end-a^2)), dpen);