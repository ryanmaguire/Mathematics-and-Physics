// Seting output format to "pdf".
import settings;
import custom_arrows;
settings.outformat   = "pdf";

defaultpen(black+linewidth(0.5pt));

// Size of the output figure.
size(128);

pen dpen = black+linewidth(0.3pt);

int i;
real dx = 0.1;
int n = (int)(1.0/dx);
real r = 1.0;
real dotradius = 0.01;
real arsize = 5bp;
real xshift = 2.0;
real yshift = -1.5;
path g;
pair Z0, Z1;
margin m = TrueMargin(0.05cm, 0.02cm);

real max(pair Z){
    if (Z.x < Z.y)  return Z.y;
    else            return Z.x;
}

pair homeo(pair Z){
    real t = (Z.y-Z.x+max(Z))*0.5;
    return (1-t, t);
}

for(i=0; i<=n; ++i){
    draw((0, r)--(r, r)--(r, 0));
    r -= dx;
}

draw((1.2, 0.5)--(1.8, 0.5), SharpArrow(arsize));

r = 1.0;
for(i=0; i<=n; ++i){
    draw((xshift, r)--(xshift+r, 0));
    r -= dx;
}

xshift = 1.0;

r = 0.0;
dx = 0.2;
n = (int)(1.0/dx);
arsize = 2bp;

for(i=0; i<n; ++i){

    Z0 = (r, 1);
    Z1 = homeo(Z0);
    g = Z0--Z1;
    draw(shift(xshift, yshift)*g, dpen, SharpArrow(arsize), m);

    Z0 = (1, r);
    Z1 = homeo(Z0);
    g = Z0--Z1;
    draw(shift(xshift, yshift)*g, dpen, SharpArrow(arsize), m);

    r += dx;
}

Z0 = (1, 1);
Z1 = homeo(Z0);
g = Z0--Z1;
draw(shift(xshift, yshift)*g, dpen, SharpArrow(arsize), m);

g = (1, 0)--(1, 1)--(0, 1);
draw(shift(xshift, yshift)*g, blue);

g = (1, 0)--(0, 1);
draw(shift(xshift, yshift)*g, red);
