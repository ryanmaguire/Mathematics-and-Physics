// Function for mimicing 3D drawing using 2D coordinates.
struct xyzpoint{
    pair P, ProjX, ProjY, ProjZ;

    // Mimic 3D drawing with these.
    private pair O = (0.0, 0.0);
    private pair X = scale(sqrt(0.5))*(-1.0, -1.0);
    private pair Y = (1.0, 0.0);
    private pair Z = (0.0, 1.0);

    // Convert 3D coordinates to 2D.
    private pair three2two(real a, real b, real c){
        return  scale(a)*X + scale(b)*Y + scale(c)*Z;
    }

    // Functions for returning various projections of the given point.
    private pair xproj(real a, real b, real c){return scale(b)*Y+scale(c)*Z;}
    private pair yproj(real a, real b, real c){return scale(a)*X+scale(c)*Z;}
    private pair zproj(real a, real b, real c){return scale(a)*X+scale(b)*Y;}

    void operator init(real x, real y, real z){
        this.P = three2two(x, y, z);
        this.ProjX = xproj(x, y, z);
        this.ProjY = yproj(x, y, z);
        this.ProjZ = zproj(x, y, z);
    }
}

pair xyzO = xyzpoint(0, 0, 0).P;
pair xyzX = xyzpoint(1, 0, 0).P;
pair xyzY = xyzpoint(0, 1, 0).P;
pair xyzZ = xyzpoint(0, 0, 1).P;
