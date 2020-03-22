// Some boiler plate stuff.
import settings;
texpreamble("\usepackage{amssymb}");
settings.render = 4;
outformat="pdf";

// Size of the output figure.
size(300);

int i;
int n = 8;
path p;

real inner  = 0.50;
real outer  = 1.00;
real center = 0.75;
real arsize = 5bp;

margin ArrowMargin = TrueMargin(0.0cm, 0.1cm);

draw(unitcircle);
draw(scale(0.75)*unitcircle, dashed);
draw(scale(0.50)*unitcircle);

for(i=0; i<n; ++i){
    p = inner*expi(2*pi*i/n)--center*expi(2*pi*i/n);
    draw(p, Arrow(arsize), ArrowMargin);
    p = outer*expi(2*pi*i/n)--center*expi(2*pi*i/n);
    draw(p, Arrow(arsize), ArrowMargin);
}

ArrowMargin = TrueMargin(0.1cm, 0.3cm);
p = 1.1*expi(pi/3)--center*expi(pi/3);
draw(Label("$\mathbb{S}^{1}$", position=0.0), p, Arrow(), ArrowMargin);

label("$X$", (1.0, -1.0));