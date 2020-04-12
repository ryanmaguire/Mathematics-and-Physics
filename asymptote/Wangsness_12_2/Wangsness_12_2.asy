// Seting output format to "pdf".
import settings;
import graph;
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

// Size of the output figure.
size(128);

pen fpen = gray(0.7)+opacity(0.5);
pen apen = black+linewidth(1.0pt);
pen cpen = black+linewidth(0.5pt);
pen dpen = black+linewidth(0.3pt)+dashed;

pair O = (0.0, 0.0);
pair X = (-sqrt(0.5), -sqrt(0.5));
pair Y = (1.0, 0.0);
pair Z = (0.0, 1.0);
pair A = (1.0, 2.0);

real R = 1.4;
real thetar = 0.15;
real yscale = 0.5;
real escale = sqrt(2.0*yscale*yscale/(1.0+yscale*yscale));
real arsize = 5bp;
real fsize  = 7pt;
real fsize2 = 5pt;
path g;

margin margins = TrueMargin(0.0, 0.07cm);

pair xyzpoint(real x, real y, real z){
    return scale(x)*X+scale(y)*Y+scale(z)*Z;
}

pair Plane2Sphere(pair P){
    real u = 2.0*P.x;
    real v = 2.0*P.y;
    real w = 1.0+P.x^2+P.y^2;
    u /= w;
    v /= w;
    w = (w-2.0)/w;
    return xyzpoint(u, v, w);
}

pair Plane2Plane(pair P){
    real u = 2.0*P.x;
    real v = 2.0*P.y;
    real w = 1.0+P.x^2+P.y^2;
    u /= w;
    v /= w;
    return xyzpoint(u, v, 0.0);
}

pair XProj(pair U){
    real EPS = 0.01;
    real dx = 0.005;
    real u = U.x;
    real v = U.y;
    if (u < v){
        while (v-u>EPS) u += dx;
    }
    else {
        while (u-v>EPS) u -= dx;
    }
    return (u, v);
}

pair YProj(pair U){
    real EPS = 0.02;
    real dy = 0.01;
    real u = U.x;
    real v = U.y;
    if (v > 0){
        while (v>EPS){
            u -= dy;
            v -= dy;
        }
    }
    else {
        while (v<-EPS){
            u += dy;
            v += dy;
        }
    }
    return (u, v);
}

real AzAngle(pair U){
    real u = 2.0*U.x;
    real v = 2.0*U.y;
    real w = 1.0+U.x^2+U.y^2;
    u /= w;
    v /= w;
    real rho = sqrt(u*u+v*v);
    w = (w-2.0)/w;
    return 180*atan(rho/w)/pi;
}

pair PointOnSphere = Plane2Sphere(A);
pair PointOnPlane  = Plane2Plane(A);
real theta         = AzAngle(A);

draw(Label("$x$", position=1.0, SW), O--scale(R)*X, apen, SharpArrow(arsize));
draw(Label("$y$", position=1.0, E),  O--scale(R)*Y, apen, SharpArrow(arsize));
draw(Label("$z$", position=1.0, N),  O--scale(R)*Z, apen, SharpArrow(arsize));
draw(PointOnPlane--XProj(PointOnPlane), dpen);
draw(PointOnPlane--YProj(PointOnPlane), dpen);
draw(PointOnSphere--PointOnPlane, dpen);
draw(O--PointOnPlane, dpen);
draw(Label("$a$", position=0.7, W, fontsize(fsize2)),
     O--scale(escale)*(-X.x, X.y), cpen);
filldraw(circle(O, 1), fpen, cpen);

g = scale(1.0, yscale)*arc((0.0), 1.0, 180, 360);
draw(g, cpen);

arsize = 4bp;

draw(Z{X}..(scale(escale)*X){S}, cpen);
draw(Label("$\mathbf{r}$", position=0.4, fontsize(fsize)), O--PointOnSphere, N,
     cpen+blue, SharpArrow(StealthHead, arsize), margins);
draw(Label("$\mathbf{v}$", position=0.4, fontsize(fsize)),
     PointOnSphere--(PointOnSphere+(0.2, 0.3)), W,
     cpen+red, SharpArrow(StealthHead, arsize), margins);
filldraw(circle(PointOnSphere, 0.02), black);

draw(Label("$\theta$", position=1.7, N, fontsize(fsize2)),
     arc(O, thetar, 90, theta));

label("$Q$", (-0.5, 0.7), fontsize(fsize));
