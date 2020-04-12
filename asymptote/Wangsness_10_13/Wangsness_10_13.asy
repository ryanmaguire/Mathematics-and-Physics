// Seting output format to "pdf".
import settings;
import _custom_arrows;

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
size(128);

// Pen for drawing.
pen dpen = red+0.5*white+linewidth(0.8pt)+linetype("4 4");
pen cpen = black+linewidth(0.8pt);

// Radius of dots.
real r = 0.03;

// Font size for labels.
real fsize = 8pt;

// Radii of the ellipse.
real rx = 0.22;
real ry = 0.15;

// Lengths of the sides of the cube.
real length = 2.0;

// Pairs for the points.
pair X = (sqrt(0.5), -sqrt(0.5));
pair Y = (1.0, 0.0);
pair Z = (0.0, 1.0);

pair xyzpoint(real x, real y, real z){
    return scale(x)*X+scale(y)*Y+scale(z)*Z;
}

pair O   = xyzpoint(0.0,    0.0,    0.0);
pair x0  = xyzpoint(length, 0.0,    0.0);
pair y0  = xyzpoint(0.0,    length, 0.0);
pair xy0 = xyzpoint(length, length, 0.0);
pair t   = xyzpoint(0.0,    0.0,    length);
pair x1  = xyzpoint(length, 0.0,    length);
pair y1  = xyzpoint(0.0,    length, length);
pair xy1 = xyzpoint(length, length, length);

pair center0 = xyzpoint(0.5*length, 0.5*length, 0.0);
pair center1 = xyzpoint(0.5*length, 0.5*length, length);

draw(O--x0,    dpen);
draw(O--y0,    dpen);
draw(x0--xy0,  dpen);
draw(y0--xy0,  dpen);
draw(x0--x1,   dpen);
draw(y0--y1,   dpen);
draw(xy0--xy1, dpen);
draw(O--t,     dpen);
draw(O--x0, dpen);
draw(O--x0, dpen);
draw(O--x0, dpen);
draw(t--x1,    dpen);
draw(t--y1,    dpen);
draw(x1--xy1,  dpen);
draw(y1--xy1,  dpen);

filldraw(circle(O,   r), black, black);
filldraw(circle(x0,  r), black, black);
filldraw(circle(y0,  r), black, black);
filldraw(circle(xy0, r), black, black);
filldraw(circle(t,   r), black, black);
filldraw(circle(x1,  r), black, black);
filldraw(circle(y1,  r), black, black);
filldraw(circle(xy1, r), black, black);

draw(ellipse(center0, rx, ry), cpen);
draw(ellipse(center1, rx, ry), cpen);

draw((center0-(rx, 0.0))--(center1-(rx, 0.0)), cpen);
draw((center0+(rx, 0.0))--(center1+(rx, 0.0)), cpen);

label("$A$", center1, fontsize(fsize));
label("$x$", x0, SW,  fontsize(fsize));
label("$y$", y0, E,   fontsize(fsize));
label("$t$", t,  W,   fontsize(fsize));