// Seting output format to "pdf".
import graph;
import custom_arrows;
import settings;
settings.outformat = "pdf";

// Size of the output figure.
size(256);

pen fpen = gray(0.7)+opacity(0.5);
pen apen = black+linewidth(1.0pt);
pen cpen = black+linewidth(0.5pt);
pen dpen = black+linewidth(0.3pt)+dashed;

pair O = (0.0, 0.0);
pair X = (-sqrt(0.5), -sqrt(0.5));
pair Y = (1.0, 0.0);
pair Z = (0.0, 1.0);

real R = 1.4;
real yscale = 0.5;
real escale = sqrt(2.0*yscale*yscale/(1.0+yscale*yscale));
real arsize = 5bp;
real fsize  = 8pt;

margin margins = TrueMargin(0.0, 0.07cm);

pair xyzpoint(real x, real y, real z){
    return scale(x)*X+scale(y)*Y+scale(z)*Z;
}

pair A = (0.8, 1.15);
pair B = xyzpoint(A.x, A.y, 0.0);

path g;

pair Plane2Sphere(pair P){
    real u = 2.0*P.x;
    real v = 2.0*P.y;
    real w = 1.0+P.x^2+P.y^2;
    u /= w;
    v /= w;
    w = (w-2.0)/w;
    return xyzpoint(u, v, w);
}

pair midpoint(pair U, pair V, real t){
    return scale(1.0-t)*U+scale(t)*V;
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

pair PointOnSphere = midpoint(Z, Plane2Sphere(A), 0.8);
pair PointOnPlane  = midpoint(O, B, 0.55);

draw(Z--PointOnSphere, cpen+blue);
draw(O--B, dpen);
draw(PointOnSphere--PointOnPlane, dpen);
draw(PointOnSphere--PointOnPlane, dpen);
draw(PointOnPlane--XProj(PointOnPlane), dpen);
draw(PointOnPlane--YProj(PointOnPlane), dpen);

draw(Label("$x$", position=1.0, SW), O--scale(0.8*R)*X, apen, SharpArrow(arsize));
draw(Label("$y$", position=1.0, E),  O--scale(R)*Y, apen, SharpArrow(arsize));
draw(Label("$z$", position=1.0, N),  O--scale(R)*Z, apen, SharpArrow(arsize));

g = arc((0.0, 0.0), 1.0, 0, 180)--
    scale(1.0, yscale)*arc((0.0), 1.0, 180, 360)--cycle;

filldraw(g, fpen, cpen);

arsize = 4bp;
draw(PointOnSphere--B, cpen+blue, SharpArrow(StealthHead, arsize), margins);

filldraw(circle(PointOnSphere, 0.02), black);
filldraw(circle(B, 0.02), black);
draw(Z{X}..(scale(escale)*X){S}, cpen);

draw(xyzpoint(A.x, 0.0, 0.0)--xyzpoint(A.x, A.y, 0.0), dpen);
draw(xyzpoint(0.0, A.y, 0.0)--xyzpoint(A.x, A.y, 0.0), dpen);

label("$(X,Y)$",   B,             SE, fontsize(fsize));
label("$(x,y,z)$", PointOnSphere, NE, fontsize(fsize));
