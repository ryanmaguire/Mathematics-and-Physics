// Some boiler plate stuff.
import settings;
import graph;
settings.outformat="pdf";

// Size of the output figure.
size(200);

// Pens used for drawing contour and direction (gradient) lines.
pen cpen = deepblue+linewidth(1pt);
pen dpen = deepblue+linewidth(0.4);

// Variable used for indexing.
int i;

// Number of angles to be looped over.
int n = 10;

// Increment size used in Euler's method of solving ODEs.
real dx = 0.001;

// Maximum distance from the origin flows are allowed to travel. The vector
// field is zero at the origin, hence Euler's method will loop infinitely.
real EPS = 0.01;

// Variable used for looping over angles.
real phi;

// Radius of the circles draw about the focii.
real r = 0.2;

// Scale factors for stretching the image.
real xscale = 1.2;
real yscale = 0.8;

// Location of the first charge. Q_2 is located at -Q_1 for symmetry.
pair Q_1 = (0.5, 0.0);
pair AA, BB;

// Variable used for drawing lines.
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

// Compute the 2-norm (magnitude) of a given vector.
real norm(pair Z){
    return sqrt(Z.x^2+Z.y^2);
}

// Electric force from two charges at R_1 and R_2.
pair Force(pair Z){
    pair R_1 = Z-Q_1;
    pair R_2 = Z+Q_1;
    pair out = R_1/(norm(R_1)^3)+R_2/(norm(R_2)^3);
    return out/norm(out);
}

// Draw the lemniscate and the bounding figure.
p = graph(f, 0, 2pi, 300, operator ..);
draw(p, cpen);
p = graph(g, 0, 2pi, 300, operator ..);
draw(p, cpen+linewidth(2pt));

// Fill in two circles representing the holes.
filldraw(shift(+Q_1)*scale(r)*unitcircle, blue+opacity(0.4), cpen);
filldraw(shift(-Q_1)*scale(r)*unitcircle, blue+opacity(0.4), cpen);

// Loop over angles and use Euler's method to solve for integral curves.
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

// Draw one final curve down the y axis.
draw((0, yscale)--(0, -yscale), dpen);