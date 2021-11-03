// Seting output format to "pdf".
import settings;
import custom_arrows;
texpreamble("\usepackage{amssymb}");
settings.outformat = "pdf";

// Size of the output.
size(256);

// Solid pen and dashed pen.
pen spen = black+linewidth(0.4);
pen dpen = spen+linetype("4 4");
pen dotf = red;
pen dotc = black+linewidth(0.2);

real r1 = 1;
real r2 = 1.2;
real e = 0.4;
real fsize = 9pt;

pair O = (0, 0);

filldraw(circle(O, r2), gray(0.4)+opacity(0.5), spen);
draw((scale(1, e)*arc(O, r2, 0, 180)), dpen);
filldraw(circle(O, r1), gray(0.5), spen);
draw((scale(1, e)*arc(O, r2, 180, 360)), spen);
draw((scale(1, e)*arc(O, r1, 180, 360)), spen);
draw((scale(1, e)*arc(O, r1, 0, 180)), dpen);

margin margins = TrueMargin(0.1cm, 0.1cm);

int i;
int n = 4;
real phi;
real arsize = 3bp;
pair A;

for (i=0; i<n; ++i){
    phi = 2*pi*i/n;
    A = scale(r1)*expi(phi);
    if ((i % 2) == 1) draw(A--O, spen, SharpArrow(arsize), margins);
    phi += pi/n;
    A = scale(1, e)*(scale(r1)*expi(phi));
    draw(A--O, spen, SharpArrow(arsize), margins);
}

draw((1.2*r2, 0.0)--(1.8*r2, 0), spen, SharpArrow(arsize));
filldraw(circle(shift(3*r2)*O, r2), gray(0.4)+opacity(0.5), spen);
draw((scale(1, e)*arc(shift(3*r2)*O, r2, 0, 180)), dpen);
draw((scale(1, e)*arc(shift(3*r2)*O, r2, 180, 360)), spen);

label("$\mathbb{S}^{2}\times{I}$", scale(1.3*r2)*expi(pi/4), fontsize(9pt));
label(
    "$\textrm{Cl}(\mathbb{B}^{3})$",
    shift(3*r2, 0)*(scale(1.3*r2)*expi(pi/4)), fontsize(9pt)
);
