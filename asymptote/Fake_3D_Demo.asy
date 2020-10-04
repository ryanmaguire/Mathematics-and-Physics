// Boilerplate stuff.
import settings;

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
