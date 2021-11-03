// Some boiler plate stuff.
import settings;
import graph;
outformat="pdf";

// Size of the output figure.
size(200);

// Pens used to draw lines and curves.
pen cpen = deepblue+linewidth(1pt);
pen dpen = deepblue+linewidth(0.4);

// Variable used for indexing.
int i;

// Number of steps between indices.
int step = 4;

// Starting index for looping over field lines.
int start = 4;

// Final index for field lines.
int n = 40;

// Variable used for computing Euler's method of solving differential equations.
real dx = 0.001;

// Variable used when looping over angles for drawing field lines.
real phi;

// The inner and outer radii of the two focii.
real r = 0.2;
real R = 0.3;

// Scale factors for the implicit curve (x/a)^6 + (y/a)^6 = 1.
real xscale = 1.2;
real yscale = 0.8;

// Center of the two point charges (the focii).
pair Q_1 = (xscale/2.0, 0);

// Variables used throughout.
pair AA, BB;
path p;

// Parametrization for the curve (x/a)^6+(y/b)^6=1.
pair f(real theta){return (xscale*cbrt(cos(theta)), yscale*cbrt(sin(theta)));}

// 2-Norm for two variables.
real norm(pair Z){return sqrt(Z.x^2+Z.y^2);}

// The sixth power of the six norm ||Z||_6 = (Z.x^6+Z.y^6)^(1/6)
real sixnorm(pair Z, real xscale, real yscale){
    return (Z.x/xscale)^6+(Z.y/yscale)^6;
}

// The electric force (in natural units) of two point charges.
pair Force(pair Z){
    pair R_1 = Z-Q_1;
    pair R_2 = Z+Q_1;
    pair out = R_1/(norm(R_1)^3)+R_2/(norm(R_2)^3);
    return out/norm(out);
}

// Draw the boundary.
p = graph(f, 0, 2pi, 300, operator ..);
draw(p, cpen);

// Draw the outer circle about the two charges, connect a line between them.
draw(shift(+Q_1)*scale(R)*unitcircle,        cpen+linewidth(2pt));
draw(shift(-Q_1)*scale(R)*unitcircle,        cpen+linewidth(2pt));
draw(shift(-R, 0)*(Q_1)--shift(R, 0)*(-Q_1), cpen+linewidth(2pt));

// Fill in the inner circles about the two focii.
filldraw(shift(+Q_1)*scale(r)*unitcircle, blue+opacity(0.4), cpen);
filldraw(shift(-Q_1)*scale(r)*unitcircle, blue+opacity(0.4), cpen);

// Loop over angles and perform Euler's method to draw field lines.
for (i=start; i<n; i += step){
    phi = 2*pi*i/n;
    AA = Q_1+r*expi(phi);
    BB = AA;
    p = AA--BB;
    while (sixnorm(AA, xscale, yscale) < 1.0){
        BB = (AA+scale(dx)*Force(AA));
        p = p--BB;
        AA = BB;
    }
    draw(p, dpen);
    draw(reflect(N, S)*p, dpen);
}

// Draw a vertical line through the origin as a field line.
draw((0, yscale)--(0, -yscale), dpen);