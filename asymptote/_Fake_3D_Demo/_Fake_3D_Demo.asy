// Boilerplate stuff.
import settings;
import graph;

// Make sure _custom_arrows.asy and _mimic_three.asy are in your ASYMPTOTE_DIR
// environment variable. These files are found in the asymptote/ folder.
import _custom_arrows;
import _mimic_three;

if(settings.render < 0)    settings.render    = 8;
if(!settings.multipleView) settings.batchView = false;

settings.outformat   = "pdf";
settings.inlineimage = true;
settings.embed       = true;
settings.toolbar     = false;
settings.prc         = false;

viewportmargin = (2, 2);

// Size of output.
size(128);

// Various pens used throughout (axes, curves, perpendiculars).
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

// Variable used for 3D-to-2D drawing.
xyzpoint xyzP;

// Variables for indexing and angles.
int i;
real phi;
real phi_start = 0.5*pi;
int i_start    = 100;
int i_end      = 500;
int i_samples  = i_end-i_start;
int n_perps    = 8;
int f_samples  = 20;

// 2D curve drawn using the fake 3D function xyzpoint.
xyzpoint f0(real t){
    real xt = 0.4*cos(t);
    real yt = 0.4*sin(t);
    real zt = 0.4*cos(4.0*t);
    return xyzpoint(xt, yt, zt);
}

// Function for the floor of f0.
pair floor(real t){return f0(t).ProjZ;}

// Pairs used to draw the curve and give it a gradient color.
pair A = f0(phi_start).P;
pair B;

// Draw the main curve.
for (i=i_start; i<=i_end; ++i){
    phi = 2*pi*i/i_samples;
    B = f0(phi).P;
    draw(A--B, cpen(phi));
    A = B;
}

// Draw the floor.
g = graph(floor, 0, 2pi, f_samples, operator ..);
draw(g, dpen);

// Drop dashed perpendicular lines at various points.
for (i=0; i<n_perps; ++i){
    phi = 2*pi*i/n_perps;
    xyzP = f0(phi);
    g = xyzP.P--xyzP.ProjZ;
    draw(g, dpen);
}

// Draw and label the axes.
L = Label("$x$", position=1.0, SW);
draw(L, xyzO--xyzX, apen, SharpArrow(StealthHead, arsize));

L = Label("$y$", position=1.0, E);
draw(L, xyzO--xyzY, apen, SharpArrow(StealthHead, arsize));

L = Label("$z$", position=1.0, N);
draw(L, xyzO--xyzZ, apen, SharpArrow(StealthHead, arsize));
