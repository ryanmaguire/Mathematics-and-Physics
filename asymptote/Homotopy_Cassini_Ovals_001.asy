// The Cassini functions are defined in CassiniOval.asy.
import _cassini_oval;

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

// Size of the output.
size(200);

// Pens for contours and directional lines (Flows).
pen cpen = deepblue+linewidth(1pt);
pen dpen = deepblue+linewidth(0.4);

// Coordinates for the first focii. The second focii is -A.
pair A = (2, 0);

// Variables used later for the Euler method of computing flows.
pair AA, BB;
path p;

// Increment step used in Euler's method.
real dx  = 0.01;

// Maximum distance from the origin flows are allowed to travel. The vector
// field is zero at the origin, hence Euler's method will loop infinitely.
real EPS = 0.01;

// Radius of the inner circle.
real r0 = 0.5;

// Variable used for looping over angles.
real phi;

// Used for indexing.
int i;

// The number of integral curves to be drawn.
int n = 16;

// The largest oval to be drawn.
int end = 10;

// Function to return the 2-norm of a vector (magnitude).
real norm(pair Z){
    return sqrt(Z.x^2+Z.y^2);
}

// Function to return the unit vector of an input vector.
pair unitnorm(pair Z){
    real magZ = norm(Z);
    if (magZ != 0) return (Z.x/magZ, Z.y/magZ);

    // Division by zero, returning zero vector.
    else return (0.0, 0.0);
}

// The value of the Cassini oval at (Z.x, Z.y) with parameter a.
real CassiniNorm(pair Z, real a){
    return ((Z.x-a)^2+Z.y^2)*((Z.x+a)^2+Z.y^2);
}

// The normalize gradient of the Cassini function. Used for computing flows.
pair f(real x, real y, real a){
    pair out;
    out = (4*x*(x^2+y^2-a^2), 4*y*(x^2+y^2+a^2));
    return unitnorm(out);
}

// Transform to reflect image across the perpendicular bisector of A and B.
transform T(pair Z0, pair Z1){
    pair RotZ0 = rotate(90, (Z0+Z1)/2)*Z0;
    pair RotZ1 = rotate(90, (Z0+Z1)/2)*Z1;
    return reflect(RotZ0, RotZ1);
}

// Parameter used in defining the Cassini ovals.
real a = norm(A);

// Approximate smallest oval by a circle centered at this point. If A and B
// have been changed from (-2, 0) and (2, 0), respectively, then this factor
// will need tweaking.
pair FakeA = A-(a/20)*unitnorm(A);

// Draw circles about the two focii.
filldraw(shift(+FakeA)*scale(r0)*unitcircle, blue+opacity(0.4), cpen);
filldraw(shift(-FakeA)*scale(r0)*unitcircle, blue+opacity(0.4), cpen);

// Use Euler's method to solve for integral curves of the gradient function f.
for (i=0; i<n; ++i){
    phi = 2*pi*i/n;
    AA = FakeA+r0*expi(phi);
    BB = AA;
    p = AA--BB;
    while (CassiniNorm(BB, a) < end^2){
        BB = (AA+scale(dx)*f(AA.x, AA.y, a));
        p = p--BB;
        AA = BB;
        if (norm(AA) < EPS) break;
    }
    draw(p, dpen);
    draw(T(A, -A)*p, dpen);
}

// Cassini Oval structure defined in CassiniOval.asy
CassiniOval co;

// Draw the central Cassini oval (Figure eight).
co = CassiniOval(A, -A, a^2);
draw(co.curve, cpen+linewidth(2pt));

// Draw the boundary (which is a different Cassini oval).
co = CassiniOval(A, -A, end);
draw(co.curve, cpen);

// The the bounding Cassini oval is connected, draw a bisecting line.
if (end-a^2>=0) draw((0, sqrt(end-a^2))--(0, -sqrt(end-a^2)), dpen);