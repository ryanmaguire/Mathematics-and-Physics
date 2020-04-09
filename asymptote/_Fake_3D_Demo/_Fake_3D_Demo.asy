// Seting output format to "pdf".
import settings;
import _custom_arrows;
import graph;
settings.outformat="pdf";
settings.render=4;

// Size of output.
size(150);

// Various pens used throughout (axes, curves, perpendiculars).
pen apen = black+linewidth(0.8pt);
pen cpen = black+linewidth(0.4pt);
pen ppen = black+linewidth(0.2pt)+linetype("8 4");

// Paths for drawing.
path g;

// Mimic 3D drawing with these.
pair O = (0.0, 0.0);
pair X = scale(1/sqrt(2))*(-1.0, -1.0);
pair Y = (1.0, 0.0);
pair Z = (0.0, 1.0);

// Label for the axes.
Label L;

// Variable for indexing and angles.
int i;
real phi;

// Number of perpendiculars to drop.
int n = 8;

// Size of the arrow head.
real arsize = 5bp;

// Used for mimicing 3D drawing.
pair xyzpoint(real a, real b, real c){
    return scale(a)*X+scale(b)*Y+scale(c)*Z;
}

// 3D curve.
pair f0(real t){
    real xt = 0.4*cos(t);
    real yt = 0.4*sin(t);
    real zt = 0.4*cos(4.0*t);
    return xyzpoint(xt, yt, zt);
}

// Projection of 3D curve.
pair f1(real t){
    real xt = 0.4*cos(t);
    real yt = 0.4*sin(t);
    return xyzpoint(xt, yt, 0.0);
}

g = O--X;
L = Label("$x$", position=1.0, SW);
draw(L, g, apen, SharpArrow(StealthHead, arsize));

g = O--Y;
L = Label("$y$", position=1.0, E);
draw(L, g, apen, SharpArrow(StealthHead, arsize));

g = O--Z;
L = Label("$z$", position=1.0, N);
draw(L, g, apen, SharpArrow(StealthHead, arsize));

g = graph(f0, 0, 2pi, 400, operator ..);
draw(g, cpen);

g = graph(f1, 0, 2pi, 100, operator ..);
draw(g, cpen+dashed);

for (i=0; i<n; ++i){
    phi = 2*pi*i/n;
    g = f0(phi)--f1(phi);
    draw(g, ppen);
}