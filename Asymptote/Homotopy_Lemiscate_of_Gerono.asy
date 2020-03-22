// Some boiler plate stuff.
import settings;
import graph;
texpreamble("\usepackage{amssymb}");
settings.render = 4;
outformat="pdf";

// Size of the output figure.
size(300);

pen cpen = deepblue+linewidth(1pt);
pen dpen = deepblue+linewidth(0.4);

int i;
int n = 10;

real dx = 0.001;
real EPS = 0.01;
real phi;
real r = 0.2;
real xscale = 1.2;
real yscale = 0.8;

pair O = (0, 0);
pair T = (0.5, 0);
pair Q_1 = (-0.5, 0.0);
pair Q_2 = (+0.5, 0.0);
pair AA, BB;

path p;

// Parametrization for the curve (x/a)^6+(y/b)^6=1.
pair f(real theta){
    real u = xscale*cbrt(cos(theta));
    real v = yscale*cbrt(sin(theta));
    return (u, v);
}

// Parametric equation for the lemiscate of Gerono.
pair g(real theta){
    return (cos(theta), sin(2*theta)/2);
}

real norm(pair Z){
    return sqrt(Z.x^2+Z.y^2);
}

pair Force(pair Z){
    pair R_1 = Z-Q_1;
    pair R_2 = Z-Q_2;
    pair out = R_1/(norm(R_1)^3)+R_2/(norm(R_2)^2);
    return out/norm(out);
}

p = graph(f, 0, 2pi, 300, operator ..);
draw(p, cpen);
p = graph(g, 0, 2pi, 300, operator ..);
draw(p, cpen+linewidth(2pt));
filldraw(shift(Q_1)*scale(r)*unitcircle, blue+opacity(0.4), cpen);
filldraw(shift(Q_2)*scale(r)*unitcircle, blue+opacity(0.4), cpen);

for (i=0; i<n; ++i){
    phi = 2*pi*i/n;
    AA = Q_1+r*expi(phi);
    BB = AA;
    p = AA--BB;
    while ((AA.x/xscale)^6+(AA.y/yscale)^6 < 1.0){
        BB = (AA+scale(dx)*Force(AA));
        p = p--BB;
        AA = BB;
        if (norm(AA) < EPS) break;
    }
    draw(p, dpen);
    draw(reflect(N, S)*p, dpen);
}

draw((0, yscale)--(0, -yscale), dpen);