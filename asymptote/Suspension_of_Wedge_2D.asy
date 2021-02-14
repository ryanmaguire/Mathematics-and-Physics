// Seting output format to "pdf".
import settings;
import _euclidean;
texpreamble("\usepackage{amssymb}");

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

// Solid pen and dashed pen.
pen spen = black+linewidth(0.4);
pen dpen = spen+linetype("4 4");

path g;
real r = 0.3;
real e = 0.15;

pair O = (0.0, 0.0);
pair A = (0.0, 1.0);
pair B = (0.0, -1.0);
pair C = (-r, 0);
pair D = (r, 0);

pair X = MidPoint2D(C, A);

draw(scale(1, e)*arc(C, r, 0, 180), dpen);
draw(scale(1, e)*arc(D, r, 0, 180), dpen);
draw(shift(X)*(scale(1, e)*arc(O, 0.5*r, 0, 180)), dpen);
draw(shift(-X)*(scale(1, e)*arc(O, 0.5*r, 0, 180)), dpen);
draw(shift((X.x, -X.y))*(scale(1, e)*arc(O, 0.5*r, 0, 180)), dpen);
draw(shift((-X.x, X.y))*(scale(1, e)*arc(O, 0.5*r, 0, 180)), dpen);

g = A--shift(-r, 0)*C--scale(1, e)*arc(C, r, 180, 360)--cycle;
axialshade(g, gray(0.5)+opacity(0.4), A, white+opacity(0.5), shift(0, -r)*C);

g = reflect(A, B)*g;
axialshade(g, gray(0.5)+opacity(0.4), A, white+opacity(0.5), shift(0, -r)*D);

g = B--shift(-r, 0)*C--scale(1, e)*arc(C, r, 180, 360)--cycle;
axialshade(g, gray(0.7)+opacity(0.4), B, gray(0.2)+opacity(0.4), C);

g = reflect(A, B)*g;
axialshade(g, gray(0.7)+opacity(0.4), B, gray(0.2)+opacity(0.4), D);

draw(scale(1, e)*arc(C, r, 180, 360), spen);
draw(scale(1, e)*arc(D, r, 180, 360), spen);
draw(shift(X)*(scale(1, e)*arc(O, 0.5*r, 180, 360)), spen);
draw(shift(-X)*(scale(1, e)*arc(O, 0.5*r, 180, 360)), spen);
draw(shift((X.x, -X.y))*(scale(1, e)*arc(O, 0.5*r, 180, 360)), spen);
draw(shift((-X.x, X.y))*(scale(1, e)*arc(O, 0.5*r, 180, 360)), spen);
draw(A--B, spen);
draw(A--shift(-r, 0)*C--B--shift(r, 0)*D--cycle);



