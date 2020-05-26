// Some boiler plate stuff.
import settings;

if(!settings.multipleView)  settings.batchView = false;
if(settings.render < 0)     settings.render = 4;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

// Size of the output figure.
size(256);

// Paths for drawing.
path g;

// Mimic 3D drawing with these.
pair O = (0.0, 0.0);
pair X = (-0.3, -0.3);
pair Y = (1.0, 0.0);
pair Z = (0.0, 1.0);

// Used for shading.
pair A, B;

// The reverse of X, using for making things 3D.
pair RevX = (-X.x, X.y);

// Used for mimicing 3D drawing.
pair point(real a, real b, real c){
    return scale(a)*X+scale(b)*Y+scale(c)*Z;
}

// Use this function when the orientation flips.
pair rpoint(real a, real b, real c){
    return scale(a)*RevX+scale(b)*Y+scale(c)*Z;
}

pair midpoint(pair A, pair B){
    return scale(0.5)*(A+B);
}

// Shades of gray.
pen dgray = gray(0.2);
pen mgray = gray(0.5);
pen lgray = gray(0.75);
pen roof  = gray(0.65);
pen boxf  = gray(0.6);
pen boxs  = gray(0.45);
pen boxb  = gray(0.25);

real xl = 1.0;
real yl = 2.0;
real zl = 1.0;

real boxwidth = 0.4;

// Draw the outline of the house.
g = point(xl,  0.0, 2*zl)--
    point(xl,  0.0, 0.0)--
    rpoint(xl, yl,  0.0)--
    rpoint(xl, yl,  2*zl)--cycle;
draw(g);

// Draw the first floor.
g = point(0.0, 0.0, 0.0)--
    point(0.0, yl,  0.0)--
    rpoint(xl, yl,  0.0)--
    point(xl,  0.0, 0.0)--cycle;
filldraw(g, mgray);

// Draw the back wall.
g = point(0.0, 0.0, 2*zl)--
    point(0.0, 0.0, 0.0)--
    point(0.0, yl,  0.0)--
    point(0.0, yl,  2*zl)--cycle;
filldraw(g, lgray);

// Shade the left wall.
g = point(0.0, 0.0, 2*zl)--
    point(0.0, 0.0, 0.0)--
    point(xl,  0.0, 0.0)--
    point(xl,  0.0, 2*zl)--cycle;
filldraw(g, dgray);

// Now the right wall.
g = point(0.0, yl, 2*zl)--
    point(0.0, yl, 0.0)--
    rpoint(xl, yl, 0.0)--
    rpoint(xl, yl, 2*zl)--cycle;
filldraw(g, dgray);

// Fill in the floor.
g = point(0.0, 0.0, 0.0)--
    point(xl, 0.0, 0.0)--
    rpoint(xl, yl, 0.0)--
    point(0.0, yl, 0.0)--cycle;

// Add the first box.
g = point(boxwidth,  0.0,     2*zl)--
    point(boxwidth, 0.0,      zl)--
    point(boxwidth, boxwidth, zl)--
    point(boxwidth, boxwidth, 2*zl)--cycle;

A = midpoint(point(boxwidth, 0.0, zl),   point(boxwidth, boxwidth, zl));
B = midpoint(point(boxwidth, 0.0, 2*zl), point(boxwidth, boxwidth, 2*zl));
axialshade(g, 0.3*white+boxf+opacity(0.85), A, boxf, B);

g = point(0.0,      boxwidth, 2*zl)--
    point(boxwidth, boxwidth, 2*zl)--
    point(boxwidth, boxwidth, zl)--
    point(0.0,      boxwidth, zl)--cycle;
filldraw(g, boxs);

// Add the second box.
g = rpoint(xl-boxwidth, yl, zl)--
    rpoint(xl-boxwidth, yl-boxwidth, zl)--
    rpoint(xl-boxwidth, yl-boxwidth, 0.0)--
    rpoint(xl-boxwidth, yl, 0.0)--cycle;
filldraw(g, boxb);

g = rpoint(xl, yl,          zl)--
    rpoint(xl, yl,          0.0)--
    rpoint(xl, yl-boxwidth, 0.0)--
    rpoint(xl, yl-boxwidth, zl)--cycle;

A = midpoint(rpoint(xl, yl, 0.0), rpoint(xl, yl-boxwidth, 0.0));
B = midpoint(rpoint(xl, yl, zl), rpoint(xl, yl-boxwidth, zl));
axialshade(g, 0.3*white+boxf+opacity(0.85), A, boxf, B);

g = rpoint(xl,          yl-boxwidth, zl)--
    rpoint(xl-boxwidth, yl-boxwidth, zl)--
    rpoint(xl-boxwidth, yl-boxwidth, 0.0)--
    rpoint(xl,          yl-boxwidth, 0.0)--cycle;
filldraw(g, boxs);

// Draw the second floor.
g = point(boxwidth, 0.0, zl)--
    point(boxwidth, boxwidth, zl)--
    point(0.0, boxwidth, zl)--
    point(0.0, yl, zl)--
    rpoint(xl-boxwidth, yl, zl)--
    rpoint(xl-boxwidth, yl-boxwidth, zl)--
    rpoint(xl, yl-boxwidth, zl)--point(xl, 0.0, zl)--cycle;
filldraw(g, mgray);


// Draw the roof of the house.
// Draw the second floor.
g = point(boxwidth, 0.0, 2*zl)--
    point(boxwidth, boxwidth, 2*zl)--
    point(0.0, boxwidth, 2*zl)--
    point(0.0, yl, 2*zl)--
    rpoint(xl, yl, 2*zl)--
    rpoint(xl, yl, 2*zl)--point(xl, 0.0, 2*zl)--cycle;
filldraw(g, roof);