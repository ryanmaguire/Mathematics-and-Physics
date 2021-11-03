// Seting output format to "pdf".
import settings;
import custom_arrows;
settings.outformat   = "pdf";

// Size of the output.
size(256);

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

// Solid pen and dashed pen.
pen spen = black+linewidth(0.4);
pen dpen = spen+linetype("4 4");

real arsize = 4bp;
path g;

g = xyzpoint(0.7, 0, 0).R--xyzpoint(0.7, 1, 0).R--
    xyzpoint(0.7, 1, 1).R--xyzpoint(0.7, 0, 1).R--cycle;
filldraw(g, gray(0.7)+opacity(0.5));

g = xyzpoint(0,   0, 0).R--xyzpoint(0.7, 0, 0).R--
    xyzpoint(0.7, 0, 1).R--xyzpoint(0,   0, 1).R--cycle;
filldraw(g, gray(0.3)+opacity(0.5));

g = xyzpoint(0.7, 0, 1).R--xyzpoint(0.7, 1, 1).R--
    xyzpoint(0,   1, 1).R--xyzpoint(0,   0, 1).R--cycle;
filldraw(g, gray(0.5)+opacity(0.5));


pair A = shift(3.0, 0.3)*(0, 0.3);
pair B = shift(3.0, 0.3)*(0.25, -0.3);
pair C = shift(3.0, 0.3)*(2.0, 0.8);
pair D = shift(3.0, 0.3)*(2.0, -0.8);

draw(A--D, dpen);
filldraw(A--B--C--cycle, gray(0.5)+opacity(0.5), spen);
filldraw(B--C--D--cycle, gray(0.6)+opacity(0.5), spen);
draw(A--B, spen+blue);
draw(C--D, spen+red);

draw((1.8, 0.3)--(2.6, 0.3), SharpArrow(arsize));

label("$X\times{Y}\times{I}$", (-0.3, 1.3), fontsize(9pt));
label("$X*{Y}$", (4.3, 1.3), fontsize(9pt));