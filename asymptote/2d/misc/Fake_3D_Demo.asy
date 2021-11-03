// Boilerplate stuff.
import settings;
import custom_arrows;
settings.outformat = "pdf";

// Size of output.
size(128);

// Function for mimicing 3D drawing using 2D coordinates.
struct xyzpoint {
    pair P, R, ProjX, ProjY, ProjZ;

    // Mimic 3D drawing with these.
    private pair O = (0.0, 0.0);
    private pair X = scale(sqrt(0.5))*(-1.0, -1.0);
    private pair Y = (1.0, 0.0);
    private pair Z = (0.0, 1.0);

    // The reverse of X for flipped orientation.
    private pair RevX =  (-X.x, X.y);

    // Convert 3D coordinates to 2D.
    private pair three2two(real a, real b, real c){
        return  scale(a)*X + scale(b)*Y + scale(c)*Z;
    }

    // Use this function when the orientation flips.
    private pair revthree2two(real a, real b, real c){
        return scale(a)*RevX + scale(b)*Y + scale(c)*Z;
    }

    // Functions for returning various projections of the given point.
    private pair xproj(real a, real b, real c){return scale(b)*Y+scale(c)*Z;}
    private pair yproj(real a, real b, real c){return scale(a)*X+scale(c)*Z;}
    private pair zproj(real a, real b, real c){return scale(a)*X+scale(b)*Y;}

    void operator init(real x, real y, real z){
        this.P = three2two(x, y, z);
        this.R = revthree2two(x, y, z);
        this.ProjX = xproj(x, y, z);
        this.ProjY = yproj(x, y, z);
        this.ProjZ = zproj(x, y, z);
    }
}

pair xyzO = xyzpoint(0, 0, 0).P;
pair xyzX = xyzpoint(1, 0, 0).P;
pair xyzY = xyzpoint(0, 1, 0).P;
pair xyzZ = xyzpoint(0, 0, 1).P;

// Default pen used for drawing.
defaultpen(black+linewidth(0.1pt));

// Various pens used throughout (axes, curves, dashed-perpendiculars).
pen apen = black+linewidth(0.8pt);
pen dpen = black+linewidth(0.1pt)+linetype("8 8");
pen cpen(real phi){
    return (sin(phi/2)^2)*gray(0.6) + (cos(phi/2)^2)*black+linewidth(0.4pt);
}

// Size of the arrow head.
real arsize = 5bp;

// Path for drawing.
path g;

// Label for the axes.
Label L;

// Variables used for 3D-to-2D drawing.
xyzpoint A, B;

// Variable for indexing.
int i;

// Used for looping over angles.
real phi;

// Start and end index.
int i_start = 100;
int i_end   = 500;

// Use above variables to compute the number of samples.
int i_samples  = i_end-i_start;

// Number of perpendicular lines to draw.
int n_perps    = 8;

// 2D curve drawn using the fake 3D function xyzpoint.
xyzpoint f0(real t){
    real xt = 0.4*cos(t);
    real yt = 0.4*sin(t);
    real zt = 0.4*cos(4.0*t);
    return xyzpoint(xt, yt, zt);
}

// Starting point on the curve we're drawing.
A = f0(2*pi*i_start/i_samples);

// Draw the main curve.
for (i=i_start+1; i<=i_end; ++i){
    phi = 2*pi*i/i_samples;
    B = f0(phi);
    draw(A.P--B.P, cpen(phi));

    // Draw the projection of the curve in the z direction.
    draw(A.ProjZ--B.ProjZ);

    // Drop dashed perpendicular lines at various points.
    if ((n_perps*i/i_samples % 1) == 0.0) draw(B.P--B.ProjZ, dpen);

    // Reset A to the new point.
    A = B;
}

// Draw and label the axes.
L = Label("$x$", position=1.0, SW);
draw(L, xyzO--xyzX, apen, SharpArrow(StealthHead, arsize));

L = Label("$y$", position=1.0, E);
draw(L, xyzO--xyzY, apen, SharpArrow(StealthHead, arsize));

L = Label("$z$", position=1.0, N);
draw(L, xyzO--xyzZ, apen, SharpArrow(StealthHead, arsize));

