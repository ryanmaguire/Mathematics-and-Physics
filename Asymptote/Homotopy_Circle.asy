// Some boiler plate stuff.
import settings;
texpreamble("\usepackage{amssymb}");
settings.render = 4;
outformat="pdf";

// Size of the output figure.
size(150);

// Variable used for indexing.
int i;

// The number of spokes coming out of the circle.
int n = 8;

// Variable for drawing arrows.
path p;

// Inner and outer radii of the annulus.
real inner  = 0.50;
real outer  = 1.00;

// Variable used for looping over angles.
real phi;

// The radius of the central circle.
real center = (inner+outer)*0.5;

// Size of the arrow heads.
real arsize = 3bp;

// Margins used to give some space for the arrow heads.
margin ArrowMargin = TrueMargin(0.0cm, 0.1cm);

// Draw the inner and outer radii.
draw(scale(inner)*unitcircle);
draw(scale(outer)*unitcircle);

// Draw the central circle with dashed lines.
draw(scale(center)*unitcircle, dashed);

// Loop over angles and draw arrows connecting inner and outer radii to center.
for(i=0; i<n; ++i){
    phi = 2*pi*i/n;
    p = inner*expi(phi)--center*expi(phi);
    draw(p, Arrow(arsize), ArrowMargin);
    p = outer*expi(phi)--center*expi(phi);
    draw(p, Arrow(arsize), ArrowMargin);
}

// Label the inner circle as S^2.
arsize = 5bp;
p = 1.1*expi(pi/5)--center*expi(pi/5);
draw(Label("$\mathbb{S}^{1}$", position=0.0), p, Arrow(arsize), ArrowMargin);

// Label the entire space X.
label("$X$", (outer, -outer));