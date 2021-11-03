// Some boiler plate stuff.
import settings;
import custom_arrows;
texpreamble("\usepackage{amssymb}");
settings.outformat="pdf";

defaultpen(fontsize(10pt));

// Size of the output figure.
size(128);

// Variable used for indexing.
int i;

// The number of spokes coming out of the circle.
int n = 8;

// Variable for drawing arrows.
path p;

// Inner and outer radii of the annulus.
real inner  = 0.25;
real outer  = 0.50;

// Variable used for looping over angles.
real phi;

// The radius of the central circle.
real center = (inner+outer)*0.5;

// Size of the arrow heads.
real arsize = 3bp;

// Margins used to give some space for the arrow heads.
margin margins = TrueMargin(0.0cm, 0.1cm);

// Draw the inner and outer radii.
draw(scale(inner)*unitcircle);
draw(scale(outer)*unitcircle);

// Draw the central circle with dashed lines.
draw(scale(center)*unitcircle, dashed);

// Loop over angles and draw arrows connecting inner and outer radii to center.
for(i=0; i<n; ++i){
    phi = 2*pi*i/n;
    p = inner*expi(phi)--center*expi(phi);
    draw(p, Arrow(arsize), margins);
    p = outer*expi(phi)--center*expi(phi);
    draw(p, Arrow(arsize), margins);
}

// Label the inner circle as S^2.
arsize = 5bp;
p = scale(1.1*outer)*expi(5*pi/16)--center*expi(5*pi/16);
draw(Label("$\mathbb{S}^{1}$", position=0.0), p, SharpArrow(arsize), margins);

// Label the entire space X.
label("$X$", scale(1.2*outer)*expi(7pi/4));